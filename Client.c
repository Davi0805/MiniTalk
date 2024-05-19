#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <string.h>

void string_to_bits(const char *str, char *bits) {
    int i = 0;
    while (str[i] != '\0') {
        char ch = str[i];
        int j = 7;
        while (j >= 0) {
            if ((ch >> j) & 1) {
                bits[i * 8 + (7 - j)] = '1';
            } else {
                bits[i * 8 + (7 - j)] = '0';
            }
            j--;
        }
        i++;
    }
    bits[i * 8] = '\0'; // Adiciona o terminador nulo
}

void sendbits(pid_t pid, const char *bits)
{
    int i;
    int erro;

    i = 0;
    while (bits[i] != '\0')
    {
        if (bits[i] == '1')
            erro = kill(pid, SIGUSR1);
        else
            erro =kill(pid, SIGUSR2);

        if (erro == -1)
            printf("erro");
        i++;
        usleep(1000);
    }
    
}

void handle_sigusr1(int sig) {
    printf("1");
}

void handle_sigusr2(int sig) {
    printf("0");
}

int main(int argc, char *argv[])
{
    struct sigaction sa;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_handler = handle_sigusr2;
    sigaction(SIGUSR2, &sa, NULL);

    pid_t pid;
    char *message;
    char bits[8 * strlen(argv[2]) + 1];

    pid = atoi(argv[1]);
    message = argv[2];
    printf("PID: %d\n", pid);
    string_to_bits(argv[2], bits);
    sendbits(pid, bits);
}