-- Juno
USE Juno;

-- Fake Users with SSH keys
--	- for the purpose of testing the player client SSH authentication

-- 'hybrid-swansea'

INSERT INTO users (username) VALUES ('hybrid-swansea');

INSERT INTO devices (keyname, ssh_prefix, ssh_pubkey, ssh_suffix, userid)
VALUES ( 'hybrids key', 'ssh-rsa', 'AAAAB3NzaC1yc2EAAAADAQABAAABgQDV6pvDAafe6Emu305YWzxuEWgWq6ypPpMftmHVtu5al9+VzLSFFph2J5hqUL06M8W7+5b1a+UXxdns7hUIHYEh2WPxJkPf4xPXyEG3bXeoTXyt4YZ3i+PagmvcYLg4pwUJl2y5A1/ipamdZTqoPNtycIDt62+pPEjBUL7QnE3YPIP6Fzh76SQcPHS46t7MDzSahBkAvaTMErCfYfyFgIrWgcWbVY+pM+JPyfNpAQs/XkYxXtctzieasPqkOlLc/Y2XKeB6SiXZiiOuu8zHTNfuAd1OO1yZ0Bp0+Bph/ZlsLmrPVsEzgw0yzOn+Mz9zMng1flQHQqxA2kLzI8lk8/HbIf9byKzIJebRdsOBJEnY+/xyEO8wxx5bgs3MshtDe9lNyKraaEgS/+c87Q4p1v6tUZdXSRPTSjyeczYxRVAMFU0NVo+WZvnG0KIHx5wMUX46tBiQFlW+gdhs1EC1wdkcC8K9zxZuK9685duhRbZp0DMgWsSC6wJi8mAUhYAT8Es=', 'hybrid-swansea@junotest', (SELECT userid FROM users WHERE username = 'hybrid-swansea') );

-- 'ltj-bukem'

INSERT INTO users (username) VALUES ('ltj-bukem');


INSERT INTO devices (keyname, ssh_prefix, ssh_pubkey, ssh_suffix, userid)
VALUES ( 'bukems key', 'ssh-rsa', 'AAAAB3NzaC1yc2EAAAADAQABAAABgQC6ZO16nNJyD6c19cRoMohkLAXbFCI2zQhzTkG4sOrd5rIWLnadECiB92HGu7OrmAT5IvY286gF84fURvTA7p+6iGceDWzjZVtA+CYoKlr3J+G7P+sNbahX9vfL/pGcC9IdSAzsZrrCr2adJLjJAJlEtYyfURF4W3GjE4Yal5iMcBzmK8Ki5T/1bosRtZ9jpk0r8vhGrb+isxyssyUxEXL0HSJR+Z3Qe13xUNdFWUOk9vZ1EUpcq3Kpb0uJCnaskgb6pDkOyWAzyZlQ3+R2qL9S8hYyzGCxql9qHHaPQ+S6Y++Dh5KsZMXCRtOcqN7iDpZNwK4EtVFc9qMpkg8BGnu7gEE1A7X9tmmYljYPm+YUEbECAE/KwxVYo3h4X0vs37jnnVjGxgYCCFJrGAyVlYLzUYq30uTLVhEJd50zhQNvQcVsLrhHtKaOvebQXUO8Wm9FtDuuwdKFPWythkEs7hDVNuVV6Ct2sYO6NDvhgskOxH/Yz3z7GKMqn/MoAIymd6E=', 'ltj-bukem@junotest', (SELECT userid FROM users WHERE username = 'ltj-bukem') );

-- 'lemon8'

INSERT INTO users (username) VALUES ('lemon8');

INSERT INTO devices (keyname, ssh_prefix, ssh_pubkey, ssh_suffix, userid)
VALUES ( 'lemons key', 'ssh-rsa', 'AAAAB3NzaC1yc2EAAAADAQABAAABgQC1fKpZZPujnSYHQS+tDIOtjcXjzD9TgzPBkLE3KrXcEi/3XejarmzFSspiD3X+tbWoL+HL6GlYGMwsi+V4gGglHfsJjfY/VdKKIDmzBWOxuR4AJsOlSDBsBAgYY4XlChk9qFS7QeECYPTV+pSKzA12AP3hC34ueC/ZF/pkKI7V9poqVVku8TbOvbAD1Un91gUtfSRAMSTap4TA7xdXs/6wCzSrl3ttdZ+agiHMouRihFWBppxW1Rl1BKVuQOn8kxsdjNNFr78loT4bX5vxYdgQk2YrQ9m1eenTD+GdP2/GjulQmdJNpzabDDA48MtTH9UOdK5V+M4DBcvEPkKh/68dN4TdtoAHCGszg9R+C+eZdgkpaeGErFNpeI4mMvYaPJNHo0ogz0VzDW1XithvjmADAcrOqLHV90BJVeJeNU4YiUoQ0JIkVGsQwCABJ386kfrCIHSRLR0op3nvur3/u3m1v7dclxUJXKfGsJVd0ZOv77Vw9a8Q5Z94jwXXPwKzZ/0=', 'lemon8@junotest', (SELECT userid FROM users WHERE username = 'lemon8') );


select * from 
