from django import forms
from account.models import UserDevice

class AddGameForm (forms.Form):
    start_time = forms.DateTimeField (widget=forms.TextInput(attrs={'type': 'datetime-local'}))
    key = forms.ModelChoiceField (queryset=None)
    redteam = forms.BooleanField (label="Team", widget=forms.RadioSelect(choices=[(False, 'Blue Team'), (True, 'Red Team')]))
    
    def __init__ (self, user, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # should be caught by views.py. double protection
        if user.is_authenticated:
            self.fields['key'].queryset = UserDevice.objects.filter (user=user)

class JoinGameForm (forms.Form):
    key = forms.ModelChoiceField (queryset=None)
    redteam = forms.BooleanField (label="Team", widget=forms.RadioSelect(choices=[(False, 'Blue Team'), (True, 'Red Team')]))
    
    def __init__ (self, user, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # should be caught by views.py. double protection
        if user.is_authenticated:
            self.fields['key'].queryset = UserDevice.objects.filter (user=user)
