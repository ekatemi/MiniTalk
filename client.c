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

void send_bin(pid_t pid, char c)
{
    int bit;

    bit = 7;
    printf("Sending character: %c (ASCII: %d, Binary: ", c, c);
    //ASCII 0 - 127 char in dec
    //127 is 01111111
    // 1       0000 0001
    // 1 << 6  0100 0000
    // 1 << 5  0010 0000
    // 1 << 4  0001 0000
    // 1 << 3  0000 1000
    // 1 << 2  0000 0100
    // 1 << 1  0000 0010
    // 1 << 0  0000 0001

    while (--bit >= 0)
    {
        printf("%d", (c & (1 << bit)) ? 1 : 0);
        if (c & (1 << bit))
        {
            //bit set 1 SIGUSR1 = 30, SIGUSR2 = 31
            kill(pid, SIGUSR1);
        }
        else
            //bit set 0
            kill(pid, SIGUSR2);
    }
    printf(")\n");

}

int main(int argc, char **argv)
{
    char *str;
    //pid is 32-bit signed integer
    pid_t pid;

    if (argc < 3)
    {
        write(1, "Enter PID number and the message\n", 33);
    }
    else if (argc == 3)
    {
        pid = ft_atoi(argv[1]);
        str = argv[2];
        while (*str)
        {
            send_bin(pid, *str);
            str++;
        }
        printf("Sending null character (ASCII: %d, Binary: 00000000)\n", '\0');
        send_bin(pid, '\0');
    }
    return (0);
}