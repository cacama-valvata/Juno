from django.urls import path

from .views import *
from django.views.generic.base import TemplateView
from django.contrib.auth.decorators import login_required


urlpatterns = [
    path ('', login_required(ProfilePage), name='account-home'),
    # path ('<slug:username>', a function, name='account-other-profile'),
    path ('settings/', login_required(Settings), name='account-settings'),
    path ('signup/', SignUpView.as_view(), name='account-signup'),
    path ('devices/', login_required(DevicesView), name='account-devices'),
    path ('devices/add/', login_required(AddDevice), name='account-devices-add'),
    path ('devices/set-default/', login_required(SetDefaultKey), name='account-devices-setdefault'),
    path ('devices/delete/', login_required(DeleteKey), name='account-delete-device'),
]
