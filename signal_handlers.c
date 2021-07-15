#include "main.h"

void sigchld_handler(int signum)      // child process terminated
{
    pid_t pid;
    int   status;
    pid = waitpid(-1, &status, WNOHANG);
    if(pid!=-1){
        for(ll i=0;i<jobtot;i++){
            if((ll)pid==jobindex[i] && jobstat[i]!=-1){         // check if its a background process(IGNORE IF -1)
                jobstat[i]=-1;
                fprintf(stderr," Process %s with process ID [%lld] stopped with exit status %d\n",jobarr[i],(ll)pid,status); // throw a message
                reference();
                break;
            }
        }
    }
}

void sigint_handler(int signum)
{
    signal(signum,SIG_IGN); // simply ignore as its shell
    latest_status=0;        // make the exit_code failure!
}

void sigtstp_handler(int signum)
{
    signal(signum,SIG_IGN); // simply ignore as its shell
    latest_status=0;        // make the exit_code failure!
}