from django.shortcuts import render
from django.http import *

from django.contrib.auth.forms import UserCreationForm
from django.urls import reverse_lazy
from django.views import generic
from django.db import IntegrityError

from .models import *
from .forms import *

class SignUpView(generic.CreateView):
    form_class = UserCreationForm
    success_url = reverse_lazy("login")
    template_name = "profile/signup.html"

def DevicesView (request):
    thisuser_devices = UserDevice.objects.filter (user=request.user)
    return render (request, "profile/devices.html", {"devices": thisuser_devices, "form": AddDeviceForm(), "setdefaultform": SetDefaultForm (request.user)})


def AddDevice (request):
    if request.method == 'POST':
        form = AddDeviceForm (request.POST)
        if form.is_valid():
            keyname = form.cleaned_data['keyname']
            ssh_key = form.cleaned_data['ssh_key'].strip().split(' ')
            default = form.cleaned_data['default']

            # ssh-rsa AAAAA..... user@host
            # user@host is actually an optional 'comment' in OpenSSH
            if len (ssh_key) >= 2:
                ssh_prefix = ssh_key[0]
                ssh_pubkey = ssh_key[1]
                ssh_suffix = ssh_key[2] if len(ssh_key) > 2 else "N/A"

                all_keys = UserDevice.objects.filter (user=request.user)
                if all_keys.count() == 0:
                    default = True

                new_device = UserDevice (user=request.user, keyname=keyname, ssh_prefix=ssh_prefix, ssh_pubkey=ssh_pubkey, ssh_suffix=ssh_suffix, default=default)
                # Prevent duplicate keys
                try:
                    new_device.save()
                except IntegrityError:
                    # TODO: better error display than this would require jquery and client-js
                    form.errors["ssh_key"] = ["Duplicate SSH key. Please generate a new one."]
                else:
                    if default:
                        for k in all_keys:
                            if k == new_device:
                                k.default = True
                            else:
                                k.default = False
                            k.save()
                    return HttpResponseRedirect (reverse_lazy ('account-devices'))

            else:
                form.errors["ssh_key"] = ["SSH keys require at least a key type and public key data."]
    else:
        form = AddDeviceForm()
    
    thisuser_devices = UserDevice.objects.filter (user=request.user)
    return render (request, "profile/devices.html", {"devices": thisuser_devices, "form": form})


def SetDefaultKey (request):
    if request.method == 'POST':
        form = SetDefaultForm (request.user, request.POST)
        if form.is_valid():
            key = form.cleaned_data['keys']
            all_keys = UserDevice.objects.filter (user=request.user)
            for k in all_keys:
                if k == key:
                    k.default = True
                else:
                    k.default = False
                k.save()
        # TODO: error display?
            
    return HttpResponseRedirect (reverse_lazy ('account-devices'))


def ProfilePage (request):
    your_score = UserScore.objects.filter (user=request.user).first()
    your_place = 1 + UserScore.objects.filter (score__gt=your_score.score).count()
    your_devices = UserDevice.objects.filter (user=request.user)

    place_suffix = ""
    if your_place % 10 == 1:
        place_suffix = "st"
    elif your_place % 10 == 2:
        place_suffix = "nd"
    elif your_place % 10 == 3:
        place_suffix = "rd"
    else:
        place_suffix = "th"

    return render (request, "profile/home.html", {"your_score": your_score.score, "your_place": your_place, "place_suffix": place_suffix, "your_devices": your_devices})

def Settings (request):
    return render (request, "profile/settings.html")
