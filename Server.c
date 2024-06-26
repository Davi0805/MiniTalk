#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>

//int index = 0;

void    handle_sigusr1(int sig)
{
    //bits[index] = '1';
    //index++;
    printf("1");
}

void    handle_sigusr2(int sig)
{
    //bits[index] = '0';
    //index++;
    printf("0");
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    sa.sa_handler = handle_sigusr2;
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    pid_t pid;
    //char bits[1024];

    pid = getpid();
    printf("PID: %d\n", pid);
    while(1)
    {
        pause();
    }
    return 0;
}