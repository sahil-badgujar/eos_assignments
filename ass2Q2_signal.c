/* 2. Improve your shell program so that
 it should not be terminated due to SIGINT (ctrl+C). */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<string.h>

void sigint_handler(int sig){
    printf("Signal Caught: %d \n", sig);
}

int main()
{
    char *ptr, cmd[512], *args[32];
    int i, ret, err, s;
    i = 1;
    signal(SIGINT, sigint_handler);
    while(1)
    {
        printf("Running : %d\n", i++);
        sleep(1);
    }

    while(1){
        printf("cmd> ");
        gets(cmd);

        i = 0;
        ptr = strtok(cmd, " ");
        args[i] = ptr;
        i++;
        do{
            ptr = strtok(NULL, " ");
            args[i] = ptr;
            i++;
        }while(ptr != NULL);

        if(strcmp(args[0], "exit") == 0)
            _exit(0);
        
        else if(strcmp(args[0], "cd") == 0)
            chdir(args[1]);
        
        else{
            ret = fork();
            if(ret == 0)
            {
                err = execvp(args[0], args);
                if(err < 0)
                {
                    perror("Bad Command");
                    _exit(1);
                }
            }
            else
                waitpid(-1, &s, 0);
        }
    }
    return 0;
}
