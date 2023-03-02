from django.shortcuts import render
from django.http import HttpResponse

from account.models import UserScore

def Leaderboard (request):
    n = 50
    top_scores = UserScore.objects.order_by ("-score").values ('id','score','user__username')[0:n]
    return render (request, "leaderboard/index.html", {"top_scores": top_scores})
