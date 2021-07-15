#include "main.h"
#include "util.h"

void jobs(ll n, char *commarg[]){
    if(n>1){
        printf("too many arguments!\n");
        latest_status=0;
    }
    else{
        for(ll i=0;i<jobtot;i++){
            if(jobstat[i]==-1)continue;

            char procfile[1000];
            sprintf(procfile, "/proc/%lld/stat", jobindex[i]);
            char status;
            FILE  *procfd = fopen(procfile, "r");
            if(procfd==NULL) continue;
            fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
            fclose(procfd);

            if(status=='T'){
                printf("Stopped ");
            }
            else{
                printf("Running ");
            }
            printf("[%lld] ",i+1);
            printf("%s [%lld]\n",jobarr[i],jobindex[i]);
        }
    }
}