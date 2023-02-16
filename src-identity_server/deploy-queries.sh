# Quick Start to set up the IAM database
# For player client testing so far

# If unable to execute, verify `chmod +x ./sa_root.sh`
# Need a SQL server first? Try:
#	sudo apt install mysql-server-8.0

HOST='localhost'

# Creating the database
mysql -u root -proot -e "source create_tables.sql; show tables;"

# Inserting fake users
mysql -u root -proot -e "source insert_fakeusers.sql;"

# Print out fake users to verification
#	Note: won't show the full SSH keys for brevity
mysql -u root -proot -e "source show_fakeusers.sql;"

# To delete everything and re-deploy, run:
#	mysql -u -h $HOST -proot -e "drop database Juno;"
