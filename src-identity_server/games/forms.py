from django import forms
from account.models import UserDevice

class AddGameForm (forms.Form):
    start_time = forms.DateTimeField (widget=forms.TextInput(attrs={'type': 'datetime-local'}))
    #TODO: key = forms.ModelChoiceField ()

class JoinGameForm (forms.Form):
    key = forms.ModelChoiceField (queryset=None)
    
    def __init__ (self, user, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.fields['key'].queryset = UserDevice.objects.filter (user=user)
