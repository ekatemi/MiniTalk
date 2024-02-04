#include "minitalk.h"

void	ft_send_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(100);
	}
}

void	ft_confirm(int sig)
{
	if (sig == SIGUSR2)
		ft_putendl_fd("\033[32mMessage received!\033[0m", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	i = 0;
	struct sigaction sa;
    sa.sa_handler = ft_confirm;
    sa.sa_flags = 0;

    // Set up the signal handler for SIGUSR1
    if (sigaction(SIGUSR2, &sa, NULL) == -1) 
        error_sigaction();
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (kill(pid, 0) != 0)
			{
				ft_putendl_fd("\033[31mWrong pid\033[0m", STDERR_FILENO);
				return (0);
			}
		while (argv[2][i])
        {
			ft_send_bits(pid, argv[2][i]);
			i++;
        }
		ft_send_bits(pid, '\0');
	}
	else
	{
		ft_putendl_fd("Error: wrong format.", STDERR_FILENO);
		ft_putendl_fd("Try: ./client <PID> \"MESSAGE\"", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (0);
}