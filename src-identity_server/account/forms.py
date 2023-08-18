from django import forms
from .models import UserDevice

class AddDeviceForm(forms.Form):
    keyname = forms.CharField(label='Key Name', max_length=200)
    ssh_key = forms.CharField (label='SSH Key', max_length=1058)
    default = forms.BooleanField (label='Default Key', widget=forms.CheckboxInput, required=False)

class SetDefaultForm (forms.Form):
    keys = forms.ModelChoiceField (queryset=None)

    def __init__ (self, user, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # should be caught by views.py. double protection
        if user.is_authenticated:
            self.fields['keys'].queryset = UserDevice.objects.filter (user=user)
            self.fields['keys'].widget.attrs={'id': 'makedefault-selector'}

class DeleteDeviceForm (forms.Form):
    keys = forms.ModelChoiceField (queryset=None)

    def __init__ (self, user, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # should be caught by views.py. double protection
        if user.is_authenticated:
            self.fields['keys'].queryset = UserDevice.objects.filter (user=user)
