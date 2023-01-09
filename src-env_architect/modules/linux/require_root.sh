# 
# Versions:
#
# Dependencies: none
#

if [[ $USER != "root" ]]; then
    echo "User is not root."
    return 1
fi
