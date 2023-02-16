# run as root - sudo su

apt install openssh-server

ssh-keygen -f juno_guest

useradd -m -s /bin/bash guest

mkdir /home/guest/.ssh
touch /home/guest/.ssh/authorized_keys
chown -R /home/guest/.ssh guest

cat "command= \"login appuser\" $(cat juno_guest.pub)" > /home/guest/.ssh/authorized_keys
