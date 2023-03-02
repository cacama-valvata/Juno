from django import forms

class AddDeviceForm(forms.Form):
    keyname = forms.CharField(label='Key Name', max_length=200)
    ssh_key = forms.CharField (label='SSH Key', max_length=1058)
