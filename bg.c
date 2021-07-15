#include "main.h"

void bg(ll n, char *commarg[]){
    if(n>2){
        fprintf(stderr,"bg : too many arguments!\n");
        latest_status=0;
        return;
    }
    else if(n<=1){
        fprintf(stderr,"bg : too few arguments!\n");
        latest_status=0;
        return;
    }
    else{
        ll index = atoi(commarg[1]);
        if(index > jobtot || index < 1 || jobindex[index-1]==-1){
            fprintf(stderr,"bg : Invalid process!\n");
            latest_status=0;
            return;
        }
        pid_t child_pid = jobindex[index-1];
        if(kill(child_pid,SIGCONT)<0){              // sends SIGCONT
            perror("bg ");
            latest_status=0;
            return;
        }
        return;
    }
}