from django.contrib import admin

# Register your models here.
from .models import *

admin.site.register (Game)
admin.site.register (GamePlayer)
admin.site.register (GameScore)
admin.site.register (GameService)
admin.site.register (GameScoring)
