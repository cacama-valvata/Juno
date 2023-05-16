from django.urls import path

from .views import *
from django.views.generic.base import TemplateView


urlpatterns = [
    path ('', set_timezone, name='set_timezone'),
]