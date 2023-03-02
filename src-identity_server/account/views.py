from django.shortcuts import render
from django.http import *

from django.contrib.auth.forms import UserCreationForm
from django.urls import reverse_lazy
from django.views import generic

from .models import *
from .forms import *

class SignUpView(generic.CreateView):
    form_class = UserCreationForm
    success_url = reverse_lazy("login")
    template_name = "profile/signup.html"

def DevicesView (request):
    thisuser_devices = UserDevice.objects.filter (user=request.user)
    return render (request, "profile/devices.html", {"devices": thisuser_devices, "form": AddDeviceForm()})

def AddDevice (request):
    if request.method != 'POST':
        return HttpResponseBadRequest()
    
    form = AddDeviceForm (request.POST)
    if not form.is_valid():
        return HttpResponseBadRequest()
    
    keyname = form.cleaned_data['keyname']
    ssh_key = form.cleaned_data['ssh_key'].strip().split(' ')
    if len(ssh_key) != 3:
        return HttpResponseBadRequest()
    
    ssh_prefix = ssh_key[0]
    ssh_pubkey = ssh_key[1]
    ssh_suffix = ssh_key[2]

    new_device = UserDevice (user=request.user, keyname=keyname, ssh_prefix=ssh_prefix, ssh_pubkey=ssh_pubkey, ssh_suffix=ssh_suffix)
    new_device.save()

    return HttpResponseRedirect("/profile/devices/")
