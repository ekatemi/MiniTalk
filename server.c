#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void ft_putnbr(pid_t pid)
{
    char idx[10] = "0123456789";
    if (pid > 9)
        ft_putnbr(pid / 10);
    write (1, &idx[pid % 10], 1);
}

static void print_pid(pid_t pid)
{
    write (1, "The PID is : ", 13);
    ft_putnbr(pid);
}

void	ft_handler(int signal)
{
	static int	bit;
	static int	i;
    i = 0;

	if (signal == SIGUSR1)
    {
        i = (i << 1) | 1;
    }
    else if (signal == SIGUSR2)
    {
        i = (i << 1) | 0;
    }
	bit++;
    
	if (bit == 8)
	{
		write(1, &i, 1);
		bit = 0;
		i = 0;
	}
}

int main ()
{
    pid_t pid;
    struct sigaction sa;
    sa.sa_handler = ft_handler;
    sa.sa_flags = 0;

    pid = getpid();
    // if (pid == -1)
    //     return (1);

    print_pid(pid);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    // if (sigaction(SIGUSR1, &sa, NULL) == 1)
    //     printf ("sending 1");
    // else if (sigaction(SIGUSR2, &sa, NULL) == 0)
    //     printf ("sending 0");
    while (1)
    {
        sleep(1);// ???
    }
    return(0);
}