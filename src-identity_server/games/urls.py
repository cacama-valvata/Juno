from django.urls import path
from django.views.generic.base import TemplateView

from . import views

urlpatterns = [
    path ('', TemplateView.as_view(template_name='games/index.html'), name='gamesindex'),
    path ('<int:game_id>/', TemplateView.as_view(template_name='games/game.html'))
]