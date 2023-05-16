from backports import zoneinfo
from django.utils import timezone

class TimezoneMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        try:
            # retrieve both session and cookie values
            try:
                tzname_sess = request.session['django_timezone']
            except KeyError as e:
                tzname_sess = ""
            tzname_cookie = request.COOKIES.get ("django_timezone")

            # if session value has timezone, it has been set manually
            # otherwise, use cookie value
            if tzname_sess != "":
                timezone.activate (zoneinfo.ZoneInfo (tzname_sess))
            else:
                timezone.activate (zoneinfo.ZoneInfo (tzname_cookie))
        except Exception as e:
            timezone.deactivate ()

        return self.get_response(request)
