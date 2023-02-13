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
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    user = models.ForeignKey (User, on_delete=models.DO_NOTHING)
    team = models.ForeignKey (TeamRef, on_delete=models.DO_NOTHING)
    wg_pubkey = models.CharField (max_length=255, null=True)

class GameScore (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    team = models.ForeignKey (TeamRef, on_delete=models.DO_NOTHING)
    score = models.PositiveBigIntegerField (default=0)

class GameService (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    name = models.CharField (max_length=255, null=False, unique=True)
    type = models.CharField (max_length=255, null=True)

class GameScoring (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    service = models.ForeignKey (GameService, models.DO_NOTHING)
    team = models.ForeignKey (TeamRef, on_delete=models.DO_NOTHING)
    result = models.CharField (max_length=255, null=True) # Team's flag or nothing if not present
    polled = models.DateTimeField (null=False)
