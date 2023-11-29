// 1. Input signal number and a process id from user.
// Send given signal to the given process using kill() syscall.

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main()
{
    int sig, pid;
    printf("Enter Signal Number :");
    scanf("%d", &sig);

    printf("Enter the process id: ");
    scanf("%d",&pid);

    int ret = kill(pid, sig);
    return 0;
}