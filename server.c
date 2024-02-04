#include "minitalk.h"

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static int	c;
	
	(void)context;
	if (signal == SIGUSR1)
		c = c | (1 << bit);
	bit++;
	if (bit == 8)
	{		
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	struct sigaction sa;
	int	pid;
	
	pid = getpid();
    if (argc != 1)
	{
		ft_putendl_fd("\033[31mWrong format, no arguments here\033[0m", STDERR_FILENO);
		ft_putendl_fd("Try: ./server", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	sa.sa_sigaction = ft_handler;
    sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	ft_putstr_fd("PID -> ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	write(1, "\n", 1);
	ft_putendl_fd("\033[32mWaiting for a message...\033[0m", STDOUT_FILENO);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		error_sigaction();
	while(1)
		pause();
	return (0);
}