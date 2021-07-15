#include "main.h"
#include "history.h"
#include "util.h"
#include "execute.h"
#include "overkill.h"
#include "signal_handlers.h"


void getcurdir(){                                              // stores the current dir to currdir
    if(getcwd(currdir,MA)==NULL){
        perror("");
        exit(0);
    }
    tilda_adder(currdir);
    return;
}

void getcommand(){                                              // fetches command from terminal
    size_t size_command = 100;

    command = (char *)malloc(size_command);
    if(command==NULL){
        fprintf(stderr,"Oops! Memory Error!\n");
    }
    int ctrld = getline(&command, &size_command, stdin);
    if(ctrld == -1){
        printf("\n");
        overkill();
        exit(0);
    }
}

void gethomedir(){                                                 // stores home dir to homedir
    if(getcwd(homedir,MA)==NULL){
        perror("");
        exit(0);
    }

    return;
}

void reference(){                                                 // prompt function
    char emotion[MA];
    if(latest_status==1){
        strcpy(emotion,"\e[0;92m:')");
    }
    else{
        strcpy(emotion,"\e[0;91m:'(");
    }
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);                                          //fetches username
    gethostname(hostname,MA);                                         //fetches hostname
    getcurdir();
    sprintf(reference,"%s \033[0;96m<%s@%s:\033[0;34m%s\033[0;96m> \033[0m",emotion,username,hostname,currdir);
    fprintf(stderr,"%s",reference);
    fprintf(stdout,reset);
}

int main(){
    setpgrp();
    starter();
    latest_status=1;                                               // latest exit_code initialised to 1(success)
    hisnum = 0;                                                    // total elements in historyarr initialised to 0
    jobtot=0;                                                      // total number of bg processes initialised to 0
    gethomedir();                                                  // assigns current directory as homedir
    strcpy(prevdir,homedir);
    loadhistory();                                                 //loads/checks for historyfile
    latest_fore_pid=-1;
    while(1){
        signal(SIGCHLD, sigchld_handler);                          // checks for any child termination signal
        signal(SIGINT,sigint_handler);                             // checks for sigint
        signal(SIGTSTP,sigtstp_handler);                           // checks for sigtstp
        reference();                                               // prompts
        getcommand();                                              // fetches command from terminal
        if(updatehistory()==0){                                    // writes to history
            continue;
        }
        latest_status=1;                                            // sets the exit_code to 1
        execute_command();                                          // parses and executes command
    }
}
