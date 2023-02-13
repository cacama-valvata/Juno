from django.db import models

from django.contrib.auth.models import User

# 'Teams' Referential Table
class TeamRef (models.Model):
    name = models.CharField (max_length=256, editable=False, null=False, unique=True)
    color = models.PositiveIntegerField (editable=False, null=False, unique=True)
    flag = models.CharField (max_length=256, editable=False, null=False, unique=True)

# Games!
class Game (models.Model):
    start_time = models.DateTimeField (null=False)
    end_time = models.DateTimeField (null=False)
    ready = models.BooleanField (null=False)

class GamePlayer (models.Model):
    game_id = models.ForeignKey (Game, on_delete=models.CASCADE)
    user_id = models.ForeignKey (User, on_delete=models.CASCADE)
    team_id = models.ForeignKey (TeamRef, on_delete=models.CASCADE)
    wg_pubkey = models.CharField (max_length=255)

class GameScore (models.Model):
    game_id = models.ForeignKey (Game, on_delete=models.CASCADE)
    team_id = models.ForeignKey (TeamRef, on_delete=models.CASCADE)
    score = models.PositiveBigIntegerField (default=0)

class GameService (models.Model):
    game_id = models.ForeignKey (Game, on_delete=models.CASCADE)
    name = models.CharField (max_length=255, null=False, unique=True)
    type = models.CharField (max_length=255)

class GameScoring (models.Model):
    game_id = models.ForeignKey (Game, on_delete=models.CASCADE)
    service_id = models.ForeignKey (GameService, on_delete=models.CASCADE)
    team_id = models.ForeignKey (TeamRef, on_delete=models.CASCADE)
    result = models.CharField (max_length=255) # Team's flag or nothing if not present
    polled = models.DateTimeField (null=False)
