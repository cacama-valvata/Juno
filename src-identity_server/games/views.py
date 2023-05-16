from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.utils import timezone
from datetime import timedelta

from .models import *
from .forms import *


def GamesIndex (request):
    now = timezone.now()
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
    if request.method == 'POST':
        form = AddGameForm (request.POST)
        if form.is_valid():
            start_datetime = form.cleaned_data['start_time']
            # TODO: drop down for SSH key to use with the game

            datetime_rightnow = timezone.now()
            if start_datetime > datetime_rightnow:
                end_datetime = start_datetime + timedelta (hours=2)

                new_game = Game (start_time=start_datetime, end_time=end_datetime)
                new_game.save()

                return HttpResponseRedirect ('/games/')
            
            else:
                form.errors['start_time'] = ["Starting time must be in the future."]
    else:
        form = AddGameForm()

    now = timezone.datetime.now()
    current_games = Game.objects.filter (end_time__gte=now)
    open_games = current_games.filter (start_time__gte=now)
    current_games = current_games.filter (start_time__lt=now)
    return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "add_form": form, "join_form": JoinGameForm ()})

def JoinGame (request):
    pass
