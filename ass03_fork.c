#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret, count = 0, status;
    printf("Process Started..!\n");
    while(1) {
        ret = fork();
        if(ret == -1)
            break;
        else if(ret == 0) {
            // child process
            sleep(10);
            _exit(0);
        }
        else {
            // parent process
            count++;
        }
    }
    // TODO cleanup all child processes

    while(waitpid(-1, &status, 0) > 0)
    ;
    printf("max child count: %d\n", count);
    
    printf("Process Completed..!\n");
    return 0;
}