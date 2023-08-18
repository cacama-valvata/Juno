from django.urls import path

from .views import *
from django.contrib.auth.decorators import login_required


urlpatterns = [
    path ('', GamesIndex, name='games-index'),
    path ('add/', login_required(AddGame), name='games-add'),
    path ('<int:game_id>/', GameInfo, name='games-info'),
    path ('<int:game_id>/join/', login_required(JoinGame), name='games-join'),
    path ('<int:game_id>/leave/', login_required(LeaveGame), name='games-leave'),
]