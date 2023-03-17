from django.shortcuts import render
from django.http import HttpResponse
import datetime

from .models import *
from .forms import *


def GamesIndex (request):
    now = datetime.datetime.now()
    current_games = Game.objects.filter (end_time__gte=now)
    open_games = current_games.filter (start_time__gte=now)
    current_games = current_games.filter (start_time__lt=now)

    return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "add_form": AddGameForm (), "join_form": JoinGameForm ()})

def GameInfo (request, game_id):
    game = Game.objects.filter (id=game_id).first()
    players = GamePlayer.objects.filter (game=game).values ('game', 'user', 'user__username')

    n = 5

    scores_per_service = []

    services = GameService.objects.filter (game=game)
    for service in services:
        scores = GameScoring.objects.filter (game=game, service=service).order_by ('-polled').values ('service', 'result', 'polled', 'service__name')[0:n]
        scores_per_service.append (scores)

    #servicelabels = services.values ('name')
    timelabels = []
    for score in scores_per_service[0]:
        # TODO: hover tooltips with full datetime
        timelabels.append (score['polled'].time) # the queryset is a dict now???

    return render (request, "games/game.html", {"game": game, "players": players, "timelabels": timelabels, "scores_per_service": scores_per_service, "extra_cols": range(n - scores_per_service[0].count())})

def AddGame (request):
    pass

def JoinGame (request):
    pass
