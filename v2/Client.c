#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "./ft_printf/ft_printf.h"

void string_to_bits(const char *str, int pid) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {
        char ch = str[i];
        int j = 7;
        while (j >= 0) {
            if ((ch >> j) & 1) {
                kill(pid, SIGUSR1);
            } else {
                kill(pid, SIGUSR2);
            }
            j--;
            usleep(1000);
        }
        i++;
    }
    while (j < 4)
    {
        kill(pid, SIGUSR2);
        usleep(1000);
        j++;
    }
        while (j > 2)
    {
        kill(pid, SIGUSR1);
        usleep(1000);
        kill(pid, SIGUSR2);
        j--;
    }
}

/* void sendbits(pid_t pid, const char *bits)
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
    //printf("Sinal enviado!");
    return ;
} */

void handle_sigusr1(int sig) {
    ft_printf("Erro");
}

void handle_sigusr2(int sig) {
    ft_printf("Mensagem recebida");
}

int main(int ac, char **av) {
    struct sigaction sa;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_handler = handle_sigusr2;
    sigaction(SIGUSR2, &sa, NULL);
    
    if (ac != 3)
        ft_printf("Numero de argumetos insuficiente!\n./Client <PID> <Mensagem>");
    int pid;
    pid = atoi(av[1]);
    //ft_printf("PID: %d\n", pid);
    string_to_bits(av[2], pid);
//    sendbits(pid, bits);

    return 0;
}
