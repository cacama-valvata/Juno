from django.shortcuts import redirect, render

# Prepare a map of common locations to timezone choices you wish to offer.
common_timezones = {
    'London': 'Europe/London',
    'Paris': 'Europe/Paris',
    'New York': 'America/New_York',
    'Clear': ''
}

def set_timezone(request):
    if request.method == 'POST':
        request.session['django_timezone'] = request.POST['timezone']
        return redirect('/')
    else:
        try:
            current_zone = request.session['django_timezone']
        except KeyError as e:
            current_zone = "not set"
        return render(request, 'timezone.html', {'timezones': common_timezones, 'current_zone': current_zone})