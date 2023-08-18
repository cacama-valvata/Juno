from django.urls import path
from django.views.generic.base import TemplateView

from .views import Leaderboard

urlpatterns = [
    path ('', Leaderboard, name='index')
]