#include "main.h"

void foreProcess(ll n,char *commarg[]){

    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);

    ll forkReturn = fork();
     // any signal passed will be taken by the child process alone (as process groups are different)

    if(forkReturn<0){
        fprintf(stderr,"Oops! Unable to fork!\n");
        latest_status=0;
        return;
    }
    if(forkReturn==0){                                // foreground/child process
        setpgrp(); 
        commarg[n]=NULL;
        tcsetpgrp(STDIN_FILENO,getpgid(0));
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        ll ret = execvp(commarg[0],commarg);
        if(ret<0){
            fprintf(stderr,"Oops! Invalid command!\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else{                                              // parent process
        latest_fore_pid = forkReturn;
        strcpy(latest_fore_process_name,commarg[0]);
        int status;
        waitpid(forkReturn,&status,WUNTRACED);   // waits for child process(fg)[ Here we use this status recieved ] ==> The status is sent back even if the child is stopped by ctrlZ (even if not killed)
        tcsetpgrp(STDIN_FILENO,getpgid(0));
        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);


        if(WIFSTOPPED(status)){   // if child is stopped(not killed) by ctrl-z, we can check that by this macro! I have sent you a photo in whatsapp about other such macros!
            ll len = strlen(latest_fore_process_name);
            jobindex[jobtot]=forkReturn;                // push created child to jobs as its suspended in background!
            jobarr[jobtot] = malloc(len * sizeof(char));
            if(command==NULL){
                fprintf(stderr,"Oops! Memory Error!\n");
                latest_status=0;
            }
            strcpy(jobarr[jobtot],latest_fore_process_name);
            jobstat[jobtot]=1;
            jobtot++;
            fprintf(stderr," Process %s with process ID [%lld] suspended\n",latest_fore_process_name,latest_fore_pid);
            latest_fore_pid=-1;
            latest_status = 0;
            return;
        }
        if(WEXITSTATUS(status)==EXIT_SUCCESS) latest_status=1; // if it is exited succesfully or by CtrlC
        else{
            latest_status=0;
        }
        latest_fore_pid=-1;
        return;
    }
}