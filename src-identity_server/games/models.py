from django.db import models

from django.contrib.auth.models import User
from account.models import UserDevice

# 'Teams' Referential Table
'''
class TeamRef (models.Model):
    name = models.CharField (max_length=256, null=False, unique=True)
    color = models.PositiveIntegerField (null=False, unique=True)
    flag = models.CharField (max_length=256, null=False, unique=True)
'''
    
# Games!
class Game (models.Model):
    start_time = models.DateTimeField (null=False)
    end_time = models.DateTimeField (null=False)
    ready = models.BooleanField (null=False, default=False)

class GamePlayer (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    user = models.ForeignKey (User, on_delete=models.DO_NOTHING)
    team = models.BooleanField (null=False) # where 0 is defending, 1 is attacking
    device = models.ForeignKey (UserDevice, on_delete=models.DO_NOTHING)
    wg_pubkey = models.CharField (max_length=255, null=True)
    wg_config = models.CharField (max_length=255, null=True)

class GameScore (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    team = models.BooleanField (null=False) # where 0 is defending, 1 is attacking
    score = models.PositiveBigIntegerField (default=0)

class GameService (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    name = models.CharField (max_length=255, null=False, unique=True)
    type = models.CharField (max_length=255, null=True)

class GameScoring (models.Model):
    game = models.ForeignKey (Game, on_delete=models.CASCADE)
    service = models.ForeignKey (GameService, models.DO_NOTHING)
    #team = models.ForeignKey (TeamRef, on_delete=models.DO_NOTHING)
    #result = models.CharField (max_length=255, null=True) # Team's flag or nothing if not present
    result = models.BooleanField (null=True)
    polled = models.DateTimeField (null=False)
