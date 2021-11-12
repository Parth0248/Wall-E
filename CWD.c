#include "main.h"

void CWD(char user[buf], char host[buf]){
    // gets name of user
    getlogin_r(user, buf);

    // gets name of host
    gethostname(host, buf);
    
    // concatenates host and user info
    strcat(user,"@");
    strcat(user,host);
    strcat(user,":");
}


