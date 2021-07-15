#include "main.h"

void loadhistory(){                           // initial call to detect/read/create historytext.file
    char HISTORYFILE[MA];
    sprintf(HISTORYFILE,"%s/historyfile.txt",homedir);
    FILE * hf =  fopen(HISTORYFILE,"r");
    if(hf){
        int pos;
        ll i = 0;
        while ((i<20) && fgets(historyarr[i], MA, hf)!= NULL){
            i++;
        }
        hisnum = i;
        for(;i<20;i++) strcpy(historyarr[i],"");
        fclose(hf);
    }
    else{
        FILE * hf = fopen(HISTORYFILE,"w");
        fclose(hf);
    }
}

int updatehistory(){                           // updates history after every command
    char HISTORYFILE[MA];
    sprintf(HISTORYFILE,"%s/historyfile.txt",homedir);
    if(strcmp(command,"\n")==0 || strcmp(command,"")==0) return 0;
    if(strcmp(command,historyarr[0])==0) return 1;
    ll len = strlen(command);
    ll f=0;
    for(ll i=0;i<len;i++){
        if(command[i]!=' ' && command[i]!='\t' && command[i]!='\n'){
            f=1;
        }
    }
    if(f==0) return 0;
    if(hisnum<20) hisnum++;
    for(ll i=18; i>=0; i--){
        strcpy(historyarr[i+1],historyarr[i]);
    }
    strcpy(historyarr[0],command);
    FILE * hf = fopen(HISTORYFILE,"w");
    if(hf){
        for(ll i=0;i<hisnum;i++){
            fprintf(hf,"%s",historyarr[i]);
        }
        fclose(hf);
    }
    return 1;
}

void history(ll n, char *commarg[]){           // history function
    ll total=0;
    if(n==1){
        total=10;
    }
    else{
        if(strlen(commarg[1])>2){
            printf("Put a number between 1 to 20!\n");
            latest_status=0;
            return;
        }
        if(strlen(commarg[1])==1){
            total = commarg[1][0]-'0';
        }
        else total = (commarg[1][0]-'0')*10 + (commarg[1][1]-'0');
    }
    if(total>20 || total<1)
    {
        printf("Put a number between 1 to 20!\n");
        latest_status=0;
        return;
    }
    if(total > hisnum){
        total=hisnum;
    }
    ll iter=total;
    for(ll i=total-1;i>=0;i--){
        if(strcmp(historyarr[i],"")!=0){
            printf(" %lld.\t%s",iter,historyarr[i]);
            iter--;
        }
    }
}
