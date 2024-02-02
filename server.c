#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// static void ft_putnbr(pid_t pid)
// {
//     char idx[10] = "0123456789";
//     if (pid > 9)
//         ft_putnbr(pid / 10);
//     write (1, &idx[pid % 10], 1);
// }

// static void print_pid(pid_t pid)
// {
//     write (1, "The PID is : ", 13);
//     ft_putnbr(pid);
//     write (1, "\n", 1);
// }

void	ft_handler(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i = i | (1 << bit);
	bit++;
	if (bit == 8)
	{
		printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	
	pid = getpid();
    struct sigaction sa;
    sa.sa_handler = ft_handler;
    sa.sa_flags = 0;
	printf("PID -> %d\n", pid);
	printf("Waiting for a message...\n");
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause ();
	}
	return (0);
}