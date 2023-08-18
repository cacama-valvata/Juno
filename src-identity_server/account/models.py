from django.db import models
from django.contrib.auth.models import User

from django.db.models.signals import post_save

# User Scores
class UserScore (models.Model):
    user = models.OneToOneField (User, on_delete=models.CASCADE)
    score = models.PositiveBigIntegerField (default=0)

    def __str__ (self):
        return str (self.score)

# Allow auto-creation of score data at the same time as user creation
def autocreate_user_score (sender, instance, created, **kwargs):
    if created:
        UserScore.objects.create (user=instance)

post_save.connect (autocreate_user_score, sender=User)
    
# User 'Devices' - SSH keys on Client VMs
class UserDevice (models.Model):
    user = models.ForeignKey (User, on_delete=models.CASCADE)
    keyname = models.CharField (max_length=200, null=False)
    ssh_prefix = models.CharField (max_length=64, null=False)
    ssh_pubkey = models.CharField (max_length=600, null=False, unique=True)
    ssh_suffix = models.CharField (max_length=256, null=True)
    last_seen = models.DateTimeField (null=True)
    default = models.BooleanField (default=False)

    def __str__ (self):
        return self.keyname
