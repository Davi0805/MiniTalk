/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:58:10 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/05/28 18:15:41 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "./ft_printf/ft_printf.h"

void	string_to_bits(const char *str, int pid)
{
	int		i;
	int		j;
	char	ch;

	ch = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ch = str[i];
		j = 7;
		while (j-- >= 0)
		{
			if ((ch >> j) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(250);
		}
		i++;
	}
	endofstring(pid);
}

void	endofstring(int pid)
{
	int	j;

	j = 0;
	while (j++ < 4)
	{
		kill(pid, SIGUSR2);
		usleep(250);
	}
	while (j-- > 2)
	{
		kill(pid, SIGUSR1);
		usleep(250);
		kill(pid, SIGUSR2);
	}
}

void	handle_sigusr1(int sig)
{
	ft_printf("Erro");
}

void	handle_sigusr2(int sig)
{
	ft_printf("Mensagem recebida");
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_handler = handle_sigusr1;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sa.sa_handler = handle_sigusr2;
	sigaction(SIGUSR2, &sa, NULL);
	if (ac != 3)
		ft_printf("Numero de argumetos insuficiente!\n");
	pid = atoi(av[1]);
	string_to_bits(av[2], pid);
	return (0);
}
