from django.urls import path

from . import views
from .views import SignUpView
from django.views.generic.base import TemplateView

urlpatterns = [
    path ('', TemplateView.as_view(template_name='profile/home.html'), name='home'),
    path ('signup/', SignUpView.as_view(), name='signup'),
    path ('devices/', views.devices, name='devices'),
]
