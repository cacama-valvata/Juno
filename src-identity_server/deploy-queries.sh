# Quick Start to set up the IAM database
# For player client testing so far

# Intended usage: `sudo ./as_root.sh`
# If unable to execute, verify `chmod +x ./sa_root.sh`

apt install mysql-server

mysql -u root -proot -e "source create_tables.sql; show tables;"

