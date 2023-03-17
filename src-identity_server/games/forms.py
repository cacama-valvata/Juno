from django import forms

class AddGameForm (forms.Form):
    start_time = forms.DateTimeField ()
    #key = forms.ModelChoiceField ()

class JoinGameForm (forms.Form):
    key = forms.CharField ()
