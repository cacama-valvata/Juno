# Quick Start to set up the IAM database
# For player client testing so far

# If unable to execute, verify `chmod +x ./deploy-queries.sh`
# Need a SQL server first? Try:
#	sudo apt install mysql-server-8.0

HOST='localhost'
USER='root'
PASS='root'

# Creating the database
mysql -u $USER -h $HOST -p$PASS -e "create database Juno;"

# Instantiate tables and fake user data
mysql -u $USER -h $HOST -p$PASS -e "use Juno; source stuff.sql;"

# Show tables (verification)
mysql -u $USER -h $HOST -p$PASS -e "use Juno; show tables; select * from auth_user; select * from account_userdevice;"

# To delete everything to re-deploy, run:
#	mysql -u -h $HOST -proot -e "drop database Juno;"
