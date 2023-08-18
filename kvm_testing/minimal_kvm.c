#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <sys/mman.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>

#define RAM_SIZE 0x10000

int main() {
	// opening kvm to use api and checking version
	int kvm_fd = open("/dev/kvm", O_RDWR);
	int version = ioctl(kvm_fd, KVM_GET_API_VERSION, 0);
	printf("KVM version: %d\n", version);
	// creating vm
	int vm_fd = ioctl(kvm_fd, KVM_CREATE_VM, 0);
	
	// creating vm memory
	void *mem = mmap(NULL, RAM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
	struct kvm_userspace_memory_region region;
	memset(&region, 0, sizeof(region));
	region.slot = 0;
	region.guest_phys_addr = 0;
	region.memory_size = RAM_SIZE;
	region.userspace_addr = (uintptr_t)mem;

	ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &region);

	// creating vcpu
	int vcpu_fd = ioctl(vm_fd, KVM_CREATE_VCPU, 0);

	// loading in the binary image
	int bin_fd = open("guest", O_RDONLY);
	if (bin_fd < 0) {
		fprintf(stderr, "can not open binary file: %d\n", errno);
		return 1;
	}
	char *p = (char *)mem;
	int r;
	for (;;) {
		r = read(bin_fd, p, 4096);
		if (r <= 0) {
			break;
		}
		p += r;
	}
	close(bin_fd);

	struct kvm_sregs sregs;
	ioctl(vcpu_fd, KVM_GET_SREGS, &sregs);
	// init selector and base to 0
	sregs.cs.selector = sregs.cs.base = sregs.ss.selector = sregs.ss.base = sregs.ds.selector = sregs.ds.base = sregs.es.selector = sregs.es.base = sregs.fs.selector = sregs.fs.base = sregs.gs.selector = 0;
	// save special registers
	ioctl(vcpu_fd, KVM_SET_SREGS, &sregs);

	// init and save normal registers
	struct kvm_regs regs;
	regs.rflags = 2;
	regs.rip = 0;
	ioctl (vcpu_fd, KVM_SET_REGS, &regs);

	// running the vm
	// sets pointer to the run state then loops running the vm until interrupted through I/O or other operations
	int runsz = ioctl(kvm_fd, KVM_GET_VCPU_MMAP_SIZE, 0);
	struct kvm_run *run = (struct kvm_run *) mmap(NULL, runsz, PROT_READ | PROT_WRITE, MAP_SHARED, vcpu_fd, 0);

	for (;;) {
		ioctl(vcpu_fd, KVM_RUN, 0);
		switch (run->exit_reason) {
			case KVM_EXIT_IO:
				printf("IO port: %x, data: %x\n", run->io.port, *(int *)((char *)(run) + run->io.data_offset));
				break;
			case KVM_EXIT_SHUTDOWN:
				return 0;
		}
	}
}
