from django import forms

class AddGameForm (forms.Form):
    start_time = forms.DateTimeField (widget=forms.TextInput(attrs={'type': 'datetime-local'}))
    #TODO: key = forms.ModelChoiceField ()

class JoinGameForm (forms.Form):
    key = forms.CharField ()
