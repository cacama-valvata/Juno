# run as root - sudo su

cd authfile
make
cp ./authfile /opt/Juno/authfile
chmod 755 /opt/Juno/authfile
cd ..

apt install mysql-server-8.0
mysql -u root -e "use mysql; alter user 'root'@'localhost' identified with mysql_native_password by 'root';"

cd ../src-identity_server/
./deploy-queries.sh
cd ../src-player_client/

read $pre $pub $suf < juno_guest.pub

mysql -u root -proot -e "use Juno; update devices set ssh_prefix = '$pre', ssh_pubkey = '$pub', ssh_suffix = '$suf' where userid = 3;"

sed -i 's/AuthorizedKeysCommand \/bin\/bash -c "\/opt\/Juno\/keygrep.sh %k/AuthorizedKeysCommand \/opt\/Juno\/authfile %k/g' /etc/ssh/sshd_config
