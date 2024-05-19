#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigusr1(int sig) {
    printf("1");
}

void handle_sigusr2(int sig) {
    printf("0");
}

int main(int ac, char **av) {
    struct sigaction sa;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_handler = handle_sigusr2;
    sigaction(SIGUSR2, &sa, NULL);
    
    (void)ac;
    pid_t pid;
    pid = atoi(av[1]);
    printf("PID: %d\n", pid);

    while (1) {
        kill(pid, SIGUSR1);
    }
    return 0;
}
