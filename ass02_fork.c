/* From a parent process (A) create a child process (B). 
The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). 
All these processes should run concurrently for 5 seconds and cleaned up properly upon termination. */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// parent A -> child B -> child C
int main()
{
    int i, pidb, sb, pidc, sc, pidd, sd;

    // parent a
    pidb = fork();
    if(pidb == 0) { 
        // child b
        pidc = fork();
        if(pidc == 0) {
            // child c
            pidd = fork();
            if(pidd == 0) { 
                //child d         
                for(i=1; i<=5; i++) {
                    printf("Child D: %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
                    sleep(1);
                }
            _exit(0);
            }
            //child c
            for(i=1; i<=5; i++) {
                printf("Child C: %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
                sleep(1);
            }
            
            waitpid(pidd, &sd, 0);
            printf("Child D exit status: %d\n", WEXITSTATUS(sc));
            _exit(0);
            //child b
            for(i=1; i<=5; i++) {
                printf("Child B: %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
                sleep(1);
            }
            waitpid(pidc, &sc, 0);
            printf("Child C exit status: %d\n", WEXITSTATUS(sc));
            _exit(0);
        }
    }


    // parent a
    for(i=1; i<=5; i++) {
        printf("Child A: %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
        sleep(1);
    }
    waitpid(pidb, &sb, 0);

    return 0;
}