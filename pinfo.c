#include "main.h"
#include "util.h"

void pinfo(ll n, char *commarg[]){                                      // pinfo
    if(n>2){
        fprintf(stderr,"pinfo : too many arguments!\n");
        latest_status=0;
        return;
    }
    pid_t pid;
    if(n==1) pid = getpid();
    else pid = atoi(commarg[1]);

    if(pid==0){
        fprintf(stderr,"Not a valid process ID!\n");
        latest_status=0;
        return;
    }
    char procfile[1000];
    char execfile[1000];
    sprintf(procfile, "/proc/%d/stat", pid);
    sprintf(execfile, "/proc/%d/exe", pid);

    char status;
    ll memory;
    FILE  *procfd = fopen(procfile, "r");
    if(procfd == NULL){
        fprintf(stderr,"Process with ID %d does not exist!\n",(int)pid);
        latest_status=0;
        return;
    }
    else{
        fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &memory);
        fclose(procfd);
        printf("PID -- %d\n", pid);
        printf("Process Status -- %c\n", status);
        printf("Memory -- %lld\n", memory);
    }
    char procadd[MA];
    int len = readlink(execfile, procadd, sizeof(procadd));
    if(len<0){
        fprintf(stderr,"No path for executable related to the process ID %d found!\n",(int)pid);
    }
    else{
        procadd[len] = '\0';

        tilda_adder(procadd);
        printf("Executable Path --  %s\n", procadd);
    }
}