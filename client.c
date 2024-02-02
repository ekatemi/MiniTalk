///send signal converting every char in binary and sending bit by bit
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	res = res * sign;
	return (res);
}

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

int	main(int argc, char **argv)
{
	int	pid;
	//int	i;

	//i = 0;
    int j = 0;
	if (argc >= 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[j])
        {
           int i = 0;
           while (argv[j][i])
           {
			    ft_send_bits(pid, argv[2][i]);
			    i++;
		    } 
            j++;
        }
		
		ft_send_bits(pid, '\n');
	}
	else
	{
		printf("Error: wrong format.\n");
		printf("Try: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	return (0);
}