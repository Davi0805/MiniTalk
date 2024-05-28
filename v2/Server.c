/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:58:15 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/05/28 18:17:24 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "./ft_printf/ft_printf.h"

void	bin_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c <<= 1;
}

void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static int	pid;
	static int	bit_index;
	static char	c;

	pid = info->si_pid;
	bin_to_char(signum, &c);
	if (++bit_index == 8)
	{
		bit_index = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		ft_printf("%c", c);
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = handle_sigusr;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
