#include "main.h"
#include "util.h"

void overkill(){
    for(ll i=0;i<jobtot;i++){
        if(jobstat[i]==-1)continue;
        kill(jobindex[i], SIGKILL);
    }
}