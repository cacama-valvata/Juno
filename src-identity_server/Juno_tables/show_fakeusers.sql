-- Use Juno

use Juno;

-- Show tables for users and devices; verifies the insertion worked

select * from users;
select keyname, ssh_prefix, ssh_suffix, userid, last_seen from devices;
