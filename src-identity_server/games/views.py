from django.shortcuts import render
from django.http import HttpResponseRedirect, Http404
from django.urls import reverse_lazy
from django.utils import timezone
from datetime import timedelta
from django.db import IntegrityError

from .models import *
from .forms import *

# HELPER FUNCTIONS
def getjoinedgames (user):
    if user.is_authenticated:
        games = GamePlayer.objects.filter (user=user).values_list ('game', flat=True)
    else:
        games = []
    return games

def get_games ():
    now = timezone.now()
    current_games = Game.objects.filter  (end_time__gte=now)
    open_games = current_games.filter (start_time__gte=now)
    current_games = current_games.filter (start_time__lt=now)

    return current_games, open_games

def get_gameplayers (game):
    players = GamePlayer.objects.filter (game=game)
    blueteam = players.filter (redteam=False).values ('game', 'user', 'user__username')
    redteam = players.filter (redteam=True).values ('game', 'user', 'user__username')
    return blueteam,redteam


# VIEWS

def GamesIndex (request):
    current_games, open_games = get_games()

    if request.user.is_authenticated:
        return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "joined_games": getjoinedgames(request.user), "add_form": AddGameForm (request.user), "join_form": JoinGameForm (request.user)})
    else:
        return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games})


# login required
def AddGame (request):
    joingame_form = JoinGameForm (request.user)

    if request.method == 'POST':
        addgame_form = AddGameForm (request.user, request.POST)
        
        if addgame_form.is_valid():
            # Very cool: Django's form validation also works on ModelChoiceFields
            start_datetime = addgame_form.cleaned_data['start_time']
            key = addgame_form.cleaned_data['key']
            redteam = addgame_form.cleaned_data['redteam']

            if start_datetime > timezone.now():
                end_datetime = start_datetime + timedelta (hours=2)
                # TODO: allow variable game times

                new_game = Game (start_time=start_datetime, end_time=end_datetime)
                new_game.save()

                joingame = GamePlayer (game=new_game, user=request.user, redteam=redteam, device=key)
                joingame.save()
                
                return HttpResponseRedirect (reverse_lazy ('games-info', kwargs={'game_id': new_game.pk}))
            
            else:
                addgame_form.errors['start_time'] = ["Starting time must be in the future."]
    else:
        addgame_form = AddGameForm(request.user)

    current_games, open_games = get_games()
    return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "joined_games": getjoinedgames(request.user), "add_form": addgame_form, "join_form": joingame_form})


# login required
def JoinGame (request, game_id):
    addgame_form = AddGameForm (request.user)

    if request.method == 'POST':
        joingame_form = JoinGameForm (request.user, request.POST)

        if joingame_form.is_valid():
            # Very cool: Django's form validation also works on ModelChoiceFields
            key = joingame_form.cleaned_data['key']
            redteam = joingame_form.cleaned_data['redteam']

            try:
                game = Game.objects.get (id=game_id)
            except Game.DoesNotExist:
                raise Http404
            
            if game.start_time > timezone.now():
                players = GamePlayer.objects.filter (game=game).values_list ('user', flat=True)
                # prohibit multiple joins to a game
                if request.user.pk not in players:
                    joingame = GamePlayer (game=game, user=request.user, redteam=redteam, device=key)
                    joingame.save()

                    return HttpResponseRedirect (reverse_lazy ('games-info', kwargs={'game_id': game_id}))
                else:
                    joingame_form.errors['key'] = ["You are already joined to the game."]
            else:
                addgame_form.errors['key'] = ["Sorry, you cannot join a game that has already started."]
    else:
        joingame_form = JoinGameForm (request.user)

    current_games, open_games = get_games()
    return render (request, "games/index.html", {"curr_games": current_games, "open_games": open_games, "joined_games": getjoinedgames(request.user), "add_form": addgame_form, "join_form": joingame_form})


# login-required
def LeaveGame (request, game_id):
    if request.method == 'POST':
        game = GamePlayer.objects.filter (game=game_id, user=request.user)
        if game.count() > 0:
            game.delete()
            return HttpResponseRedirect (reverse_lazy ('games-index'))
        
    return HttpResponseRedirect (reverse_lazy ('games-info', kwargs={'game_id': game_id}))


def GameInfo (request, game_id):
    try:
        game = Game.objects.get (id=game_id)
    except Game.DoesNotExist:
        raise Http404

    blueteam, redteam = get_gameplayers (game)

    in_game = False
    curr_gameplayer = GamePlayer.objects.filter (game=game, user=request.user)
    if curr_gameplayer.count() > 0:
        in_game = True

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

    return render (request, "games/game.html", {"game": game, "blue_team": blueteam, "red_team": redteam, "timelabels": timelabels, "scores_per_service": scores_per_service, "extra_cols": range(extracols), "in_game": in_game})
            
