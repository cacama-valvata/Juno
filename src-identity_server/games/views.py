from django.shortcuts import render
from django.http import HttpResponseRedirect, HttpResponseNotFound, Http404
from django.urls import reverse_lazy
from django.utils import timezone
from datetime import timedelta
from django.db import IntegrityError

from .models import *
from .forms import *

# Helper function
def getjoinedgames (request):
    if request.user.is_authenticated:
        games = GamePlayer.objects.filter (user=request.user).values_list ('game', flat=True)
    else:
        games = []
    return games

def GamesIndex (request):
    now = timezone.now()
    current_games = Game.objects.filter (end_time__gte=now)
    open_games = current_games.filter (start_time__gte=now)
    current_games = current_games.filter (start_time__lt=now)

    if request.user.is_authenticated:
        return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "joined_games": getjoinedgames(request), "add_form": AddGameForm (request.user), "join_form": JoinGameForm (request.user)})
    else:
        return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games})

def GameInfo (request, game_id):
    try:
        game = Game.objects.get (id=game_id)
    except Game.DoesNotExist:
        raise Http404

    players = GamePlayer.objects.filter (game=game).values ('game', 'user', 'user__username')

    n = 5

    scores_per_service = []

    services = GameService.objects.filter (game=game)
    for service in services:
        scores = GameScoring.objects.filter (game=game, service=service).order_by ('-polled').values ('service', 'result', 'polled', 'service__name')[0:n]
        scores_per_service.append (scores)

    #servicelabels = services.values ('name')
    timelabels = []
    try:
        for score in scores_per_service[0]:
            # TODO: hover tooltips with full datetime
            timelabels.append (score['polled'].time) # the queryset is a dict now???
        extracols = scores_per_service[0].count
    # There is not one service
    except IndexError as e:
        for i in range(n):
            timelabels.append ("-")
        extracols = 0 - n

    return render (request, "games/game.html", {"game": game, "players": players, "timelabels": timelabels, "scores_per_service": scores_per_service, "extra_cols": range(extracols)})

def AddGame (request):
    if request.method == 'POST':
        form = AddGameForm (request.user, request.POST)
        if form.is_valid():
            start_datetime = form.cleaned_data['start_time']
            # TODO: drop down for SSH key to use with the game

            datetime_rightnow = timezone.now()
            if start_datetime > datetime_rightnow:
                end_datetime = start_datetime + timedelta (hours=2)

                new_game = Game (start_time=start_datetime, end_time=end_datetime)
                new_game.save()

                key = form.cleaned_data['key']
                joingame = GamePlayer (game=new_game, user=request.user, team=False, device=key)
                joingame.save()

                return HttpResponseRedirect (reverse_lazy ('games-info', kwargs={'game_id': new_game.pk}))
            
            else:
                form.errors['start_time'] = ["Starting time must be in the future."]
    else:
        form = AddGameForm(request.user)

    now = timezone.now()
    current_games = Game.objects.filter (end_time__gte=now)
    open_games = current_games.filter (start_time__gte=now)
    current_games = current_games.filter (start_time__lt=now)
    return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "joined_games": getjoinedgames(request.user), "add_form": form, "join_form": JoinGameForm (request.user)})

def JoinGame (request, game_id):
    if request.method == 'POST':
        form = JoinGameForm (request.user, request.POST)
        if form.is_valid():
            # Very cool: Django's form validation also works on ModelChoiceFields
            key = form.cleaned_data['key']
            game = Game.objects.filter (id=game_id).first()
            
            players = GamePlayer.objects.filter (game=game).values_list ('user', flat=True)
            # prohibit multiple joins to a game
            if request.user.pk not in players:
                joingame = GamePlayer (game=game, user=request.user, team=False, device=key)
                try:
                    joingame.save()
                except IntegrityError as e:
                    form.errors["key"] = ["Game does not exist."]
                else:
                    return HttpResponseRedirect (reverse_lazy ('games-info', kwargs={'game_id': game_id}))
            else:
                form.errors['key'] = ["You are already joined to the game."]
    else:
        form = JoinGameForm (request.user)

    now = timezone.now()
    current_games = Game.objects.filter (end_time__gte=now)
    open_games = current_games.filter (start_time__gte=now)
    current_games = current_games.filter (start_time__lt=now)
    return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "joined_games": getjoinedgames(request.user), "add_form": AddGameForm(request.user), "join_form": form})

            