from django.urls import path

from .views import *
from django.views.generic.base import TemplateView


urlpatterns = [
    path ('', TemplateView.as_view(template_name='profile/home.html'), name='home'),
    path ('signup/', SignUpView.as_view(), name='signup'),
    path ('devices/', DevicesView, name='devices'),
    path ('devices/add/', AddDevice, name='devies-add')
]
