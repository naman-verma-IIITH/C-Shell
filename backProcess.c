#include "main.h"

void backProcess(ll n, char *commarg[]){
    ll forkReturn = fork();
    // setpgid(0,0);                                        // same thing can be done using
    if(forkReturn<0){
        fprintf(stderr,"Oops! Unable to fork!\n");
        latest_status=0;
        return;
    }
    if(forkReturn==0){                                                // background/child process
        setpgrp();                                              // setting process ID to process grp ID;
        commarg[n-1]=NULL;
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        pid_t pid = getpid();
        ll ret = execvp(commarg[0],commarg);                          // executes executable files
        if(ret<0){
            fprintf(stderr,"Oops! Invalid command!\n");
            latest_status=0;
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else{
        ll len = strlen(commarg[0]);                                   // parent process
        jobindex[jobtot]=forkReturn;                                   // push created child to jobs
        jobarr[jobtot] = malloc(len * sizeof(char));
        if(command==NULL){
            fprintf(stderr,"Oops! Memory Error!\n");
            latest_status=0;
        }
        strcpy(jobarr[jobtot],commarg[0]);
        jobstat[jobtot]=1;
        jobtot++;
        fprintf(stderr,"[%lld] started %s\n",jobindex[jobtot-1],jobarr[jobtot-1]);
        return;
    }
}