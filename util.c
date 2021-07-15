#include "main.h"

void tilda_adder(char *path){                                      // adds tilda to path
    ll lenHome = strlen(homedir);
    ll lenPath = strlen(path);

    if(lenHome > lenPath) return;
    for(ll i=0;i<lenHome;i++){
        if(homedir[i]!=path[i]) return;
    }

    char address[MA];
    strcpy(address,"~");
    strcat(address,path+lenHome);
    strcpy(path,address);
}

void tilda_remover(char *path){                                     // removes tilda from path to get absolute path
    if(path[0]=='~'){
        char *address;
        address = malloc(100*sizeof(char));
        strcpy(address,homedir);
        strcat(address,path+1);
        strcpy(path,address);
    }
}

void tokenizer(char *token[],char *str,char *delim, ll *total){     // tokenises str into token by delim
    token[0] = strtok(str,delim);
    ll index = 0;
    while(token[index]!=NULL){
        token[++index] = strtok(NULL,delim);
    }
    *total = index;
}

void starter(){
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);                                          //fetches username
    gethostname(hostname,MA);                                         //fetches hostname
    username[0] = (char)toupper(username[0]);
    fprintf(stderr,clear);
    fprintf(stderr,HRED);
    fprintf(stderr,"\nHello %s! Nice to meet you! \n",username);
    fprintf(stderr,"I am Wish, your new shell.\n\n");
    fprintf(stderr,reset);
}