# Have python3, pip, and pyvenv installed

DATABASE_USER= juno
DATABASE_PW= 8Py9KJE57cxfmg86ARTz
DATABASE_NAME= Juno

python -m venv ./venv/
source ./venv/bin/activate
pip install -r requirements.txt

docker run -d --name juno_mysql -e MYSQL_RANDOM_ROOT_PASSWORD=yes -e MYSQL_USER=$(DATABASE_USER) -e MYSQL_PASSWORD=$(DATABASE_PW) -e MYSQL_DATABASE=$(DATABASE_NAME) -p 3306:3306 mysql:latest

touch JunoIAM/mysql.creds
touch JunoIAM/django.creds

# 127.0.0.1 instead of localhost to avoid systemd socket
echo "$(DATABASE_USER) \
$(DATABASE_PW) \
127.0.0.1" > JunoIAM/mysql.creds

python manage.py makemigrations
python manage.py migrate
# TODO: turn off debug mode and add allowed host. This shouldn't be running without a proxy server in front of it anyways
python manage.py runserver

