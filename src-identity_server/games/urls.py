from django.urls import path

from .views import *
from django.views.generic.base import TemplateView
from django.contrib.auth.decorators import login_required


urlpatterns = [
    path ('', GamesIndex, name='games-index'),
    path ('<int:game_id>/', GameInfo, name='game-info'),
    path ('add/', login_required(AddGame), name='game-add'),
    path ('join/', login_required(JoinGame), name='game-join'),
]