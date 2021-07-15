# C-Shell

## How to Use?

1. Run `https://github.com/naman-verma-IIITH/C-Shell.git` to download the shell.
2. Run `make` in the Shell directory to compile the C-Shell.
3. Run `./main` to execute the shell.

   ```shell
    $ git clone https://github.com/naman-verma-IIITH/C-Shell.git
    $ cd Wish
    $ make
    $ ./main
   ```

<br>

## Features

1. Various general purpose built-in commands are implemented as mentioned later.

2. A prompt for the next command displaying the `username`,`hostname` as well as the `present working directory`

3. Process management and job controlling with foreground and background processes and switching between them.

4. Signals like `SIGTSTP`, `SIGKILL`, `SIGINT` etc. are handled by the various processes in the well-known manner.

5. Piping and Redirection as provided by BASH.

6. Explicit display of `EXIT CODE` of previous command along with the prompt for the next command.

7. Command Chaining using `AND` and `OR` operators based on `EXIT CODES` of commands.

8. Implemented in a very user-friendly and interactive manner.

## Built-in Commands

1. `echo [string]` <br>
    * Implemented in echo.c
    * Takes a string argument and prints it back after removing extra spaces and puts a newline at the end. No arguments means null string.

2. `pwd` <br>
    * Implemented in execute.c
    * Prints the current working directory of the shell
    * Uses the `getcwd()` syscall

3. `cd [Location]` <br>
    * Implemented in cd.c
    * Takes a path to a directory as an input and makes it the current working directory. With no arguments, it makes `~` as the current working directory.
    * Uses the `chdir()` syscall

4. `ls [-l -a -al -la] [Directory]` <br>
    * Implemented in ls.c
    * Lists all the files and directories in the mentioned directory/directories. If no parameters are passed, lists the contents of current directory.
    * The `-l` flag lists the contents in a more descriptive way by providing some information about each item.
    * The `-a` flag is used to include the hidden files and folders in the listing.
    * Uses the `readdir()` syscall.

5. `pinfo [Process ID]` <br>
    * Implemented in pinfo.c
    * Takes a process ID as input and provides information about the process.
    * With no arguments it provides information about the shell process running.
    * Uses the `/proc/pid/status` and `proc/pid/exec` files to fetch the required information.

6. `history [number]` <br>
    * Implemented in history.c
    * Takes a `number` as an input and lists the last number of valid/invalid commands executed. Continuas repetitions are avoided.
    * With no arguments it prints the last `10` such commands.

7. `nightswatch -n [seconds] [interrupts|newborn]` <br>
    * Implemented in nightswatch.c
    * Interrupts prints the total number of keyboard interrupts.
    * Newborn prints the Process ID of newest process.
    * Commands are executed every `seconds` secs interval.
    * Press <kbd>q</kbd> ` + ` <kbd>Enter</kbd> to stop the execution.

8. `quit`
    * Implemented in quit.c
    * Quits the C Shell.
    * This will kill all background and foreground processes running on the Shell before quiting.

9. `setenv [var] [value]`
    * Implemented in the execute.c
    * Creates and assigns value to the environment variables.
    * It sets a `value` to a `var` in environment.
    * A missing `value` argument is treated as `NULL`
    * Uses the `setenv()` function.

10. `unsetenv [var]`
    * Implemented in the execute.c
    * It deletes any current currently assigned environment variable
    * Uses the `unsetenv()` function.

11. `jobs`
    * Implemented in jobs.c
    * It lists all the background processes along with their `pid`,`status` and the `jid(Job ID)`

12. `kjob [jid] [signal]`
    * Implemented in kjob.c
    * Sends a `signal` to process with Job ID as `jid`
    * Uses the `kill()` syscall.

13. `overkill`
    * Implemented in overkill.c
    * Terminates all background processes.

14. `fg [jid]`
    * Implemented in fg.c
    * Continues a suspended background process identified by Job ID `jid` as a foreground process.

15. `bg [jid]`
    * Implemented in bg.c
    * Continues a suspended background process identified by Job ID `jid` as a background process.

## Syntactical Details

1. Any command with `&` as the last argument will be treated as a background process. Any such process with a terminal control will be suspended automatically, and the shell/terminal will return a prompt immediately. For e.g,

   ```shell
    $ vim &
    $ ls . dir1 &
   ```

2. <kbd>|</kbd> is used for piping. For e.g,

   ```shell
    $ ls | wc
    $ ls | sort
   ```

3. <kbd><</kbd> is used for input redirection. <kbd>></kbd> and <kbd>>></kbd> are used for output redirection as overwrite and append respectively. For e.g,

   ```shell
    $ ls > file.txt
    $ sort < file.txt > sortedfile.txt
    $ ls | wc >> sortedfile.txt
   ```

4. Commands are chained based on `EXIT CODES` by using `@` as the `AND` and `$` as the `OR` symbol.For e.g,

   ```shell
    $ mkdir newdir @ cd newdir $ rm -rf newdir
   ```

4. Multiple `;` separated instructions, each having multiple commands piped to each other with redirections to and from files can be executed along with chaining. For e.g,

   ```shell
    $ ls > file1.txt @ ls $ cd .. ; sort < file1.txt | cat | wc ; ls | wc;
   ```

5. <kbd>^</kbd> `+` <kbd>C</kbd> can be used to send a `SIGINT` signal to a foreground process to terminate it. The shell will however ignore this signal.

6. <kbd>^</kbd> `+` <kbd>Z</kbd> can be used to send a `SIGTSTP` signal to a foreground process to suspend it. The shell however will ignore this signal. The shell will however ignore the signal.

7. <kbd>^</kbd> `+` <kbd>D</kbd> can be used to terminate the shell by passing a `EOF` character to the prompt.

8. Any non-built-in command executable will be searched for in the `PATH`

9. Based on the `EXIT CODE` of the last instruction, the prompt will appear with the `SHELL_EMOTI` as `:')` representing `success` or `:'(` representing `failure`.

## Filewise break-up

* `main.c` It contains the `main()` . The shell execution starts here.
* `history.c` Every command is appended to the `historyfile.txt` for future reference.
* `execute.c` Commands are parsed. Functions for redirection, piping, chaining and execution are implemented
* `signal_handlers.c` Signal handlers for `SIGCHLD`, `SIGINT`, `SIGTSTP` are implemented.
* `util.c` This file contains all Utility functions such as, `tokenizer()`, `tilda_remover()` etc.
* `backProcess.c` Execution of background processes is implemented.
* `foreProcess.c` Execution of external foreground processes is implemented.
* `others` Files like `cd.c`, `ls.c` etc are used to implement corresponding built-in commands.

## Implementation Details

### The UI and the Prompt

* The shell gives a prompt by using `reference()` as  ```<username@hostname:$PWD>``` and waits for any instruction to be given by the user. The

* The `home directory` or `~` is the directory where the executable of the shell resides.

### Input Parsing, Piping and Redirection

* The shell accepts instructions and is capable of executing a set of long number of semi-colon-separated commands. It parses the command by separating based on `;`'s.

* Then the `piper()` function parses `|` as a pipe for each set of piped commands. The `pipe()` syscall is used to implement the piping.

* The `<`, `>` and `>>` separates the `core_command`, `input_file` and `output_file` in the `redirector()` function. The `dup2()` syscall is used to attach the input and output files to the cin and cout descriptors.

* The `core_command` is then separated into arguments by `space`.

### History Tracking

* The shell keeps a track of all user executed commands in a file named `historyfile.txt`. This file is auto-generated in the first session of the shell.

* The `updatehistory()` updates the history file before execution of each command.

### Command Execution

* The `command_handler()` handles the core_command either by calling a built-in command handling function or the `foreProcess()` and `backProcess()` for any external executable and background running of process respectively.

* For executing any external executable as a foreground process, a `fork()` syscall is executed to create a child process and the `execvp()` executes the required executable in the child process while the shell waits for its termination or suspension.

* The `&` argument at the end of a command indicates a background process. The same approach as above is used, however, the shell doesn't wait for the process execution. The shell keeps a track of all such background processes along with their status and process ID.

## To be done

1. Command history and <kbd>up</kbd> /  <kbd>Down</kbd> arrow command-recall across sessions
2. <kbd>tab</kbd> completion
3. Aliasing
<br>
 <i>and many more ...</i>
