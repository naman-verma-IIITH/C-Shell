#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "colors.h"
#include "ctype.h"

#define ll long long int
#define MA 100000


char homedir[MA];
char currdir[MA];
char prevdir[MA];

char *command;

char historyarr[20][100];
ll hisnum;

ll jobtot;
ll jobindex[MA];
char *jobarr[MA];
ll jobstat[MA];

ll latest_fore_pid;
char latest_fore_process_name[MA];

int latest_status;


void getcurdir();
void getcommand();
void gethomedir();
void reference();