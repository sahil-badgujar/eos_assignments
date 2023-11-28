/* From one parent create 5 child processes. 
Each child should run for 5 seconds and print count along with its pid. 
Parent should wait for all child processes to complete and clean all of them. 
Hint: use loop to fork() multiple child processes. */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
// one parent and three child processes.
void fun(int max){
    int i;
    for(i=1; i<=max; i++) {
            printf("[%d] fun : %d\n", getpid(), i);
            sleep(1);
    }
}


int main()
{
    int i, max=5, pid[5], status, ret;
    for(i=0; i<5; i++) {
        pid[i] = fork();
        if(pid[i] == 0)
        {
            fun(10);
            _exit(1);
        }
    }
    
    fun(5);

    for(i=0; i<5; i++) {
        ret = waitpid(-1, &status, 0);
        printf("Child [%d] exit status: %d\n", ret, WEXITSTATUS(status));
    }
    return 0;
}
