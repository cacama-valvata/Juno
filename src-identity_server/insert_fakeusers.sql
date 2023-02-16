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
VALUES ( 'lemons key', 'ssh-rsa', 'AAAAB3NzaC1yc2EAAAADAQABAAABgQCT5h3mgwZQkogttDoixTYtk5KHumbCs3BXAp2c27VYZhjPOSdDR5GYWGm0U+w6TnHein74XSEIPozypSP7yfOJK8Cr1tsuR1ptJfOX6c0bg1eNbiiNVwP6d5Zz6suiDK6KI03x4DJkTE/doaA9g/2LuiZIYNoXk9diPMwxB+lJdVLPFBaxcTJg9Pu/nT1sq72rhBEbR6wAClnqqRjQI7U/vr+0EGqwXHo+ocXhBunThgzCgLR5QzOIPJqNO7HBoOyrfu/wco+SrYnckT2hiQDvTLMQ95jmRLKMa+I7VQavG6yku09F3C23cEa4KpGXZ+9Z9HUYuVZK3isS3S7oLMLCpVIm9qpnhqcjp6frgt3SXGTsFexvFB7rJyoBH7Nuio25ow16pfcPSbdqGI7dy2+Anf15+/p6GY3/QkaAwIfJl+eEpbPk587M7FNpYNNvBW1BMgtySW+Vc74zg7FoF19vZEuP3BJqgrNtr3CTakdLwx0X6d7iwh698xypsKKG6jE=', 'carter@DESKTOP-ARPPV1D', (SELECT userid FROM users WHERE username = 'lemon8') );


select * from 
