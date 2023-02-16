# run as root - sudo su

cd playershell
make
mkdir /opt/Juno
cp ./playshell /opt/Juno/playshell
chmod 755 /opt/Juno/playshell
cd ..

cp keygrep.sh /opt/Juno/keygrep.sh
chmod 755 /opt/Juno/keygrep.sh

usermod -s /opt/Juno/playshell guest

sed -i 's/#AuthorizedKeysCommand none/AuthorizedKeysCommand \/bin\/bash -c "\/opt\/Juno\/keygrep.sh %k/g' /etc/ssh/sshd_config
sed -i 's/#AuthorizedKeysCommandUser nobody/AuthorizedKeysCommmandUser root/g' /etc/ssh/sshd_config
