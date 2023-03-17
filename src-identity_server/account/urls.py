from django.urls import path

from .views import *
from django.views.generic.base import TemplateView
from django.contrib.auth.decorators import login_required


urlpatterns = [
    path ('', login_required(ProfilePage), name='home'),
    path ('settings/', login_required(Settings), name='settings'),
    path ('signup/', SignUpView.as_view(), name='signup'),
    path ('devices/', login_required(DevicesView), name='devices'),
    path ('devices/add/', login_required(AddDevice), name='devices-add'),
]
