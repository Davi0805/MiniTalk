#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
    bits[i * 8] = '\0';
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
            erro = kill(pid, SIGUSR2);

        if (erro == -1)
            printf("erro");
        i++;
        usleep(1000);
    }
    printf("Sinal enviado!");
    return ;
}

void handle_sigusr1(int sig) {
    printf("1");
}

void handle_sigusr2(int sig) {
    printf("0");
}

int main(int ac, char **av) {
/*     struct sigaction sa;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_handler = handle_sigusr2;
    sigaction(SIGUSR2, &sa, NULL);
     */
    (void)ac;
    pid_t pid;
    char bits[8 * (strlen(av[2]) + 1)];
    pid = atoi(av[1]);
    printf("PID: %d\n", pid);
    string_to_bits(av[2], bits);
    printf("%s\n", bits);
    sendbits(pid, bits);

    return 0;
}
