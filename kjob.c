#include "main.h"
#include "util.h"

void kjob(ll n, char * commarg[]){
    if(n>3){
        fprintf(stderr,"kjob : too many arguments!\n");
        latest_status=0;
    }
    else if(n<3){
        fprintf(stderr,"kjob : too few arguments!\n");
        latest_status=0;
    }
    else{
        ll index = atoi(commarg[1]);
        pid_t pid = jobindex[index-1];
        ll sig = atoi(commarg[2]);
        if(index>jobtot){
            fprintf(stderr,"kjob : invalid process!\n");
            latest_status=0;
            return;
        }
        if(kill(pid,sig)<0){
            perror("kjob ");
            latest_status=0;
        }
    }
}