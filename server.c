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

void signalHandler(int signum) {
    // Handle the signal here
    printf("Signal %d received.\n", signum);

    // You can add more logic here based on the received signal
}

int main (int argc, char **argv)
{
    pid_t pid;
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sa.sa_flags = 0;

    pid = getpid();
    // if (pid == -1)
    //     return (1);

    print_pid(pid);
   
    if (sigaction(SIGUSR1, &sa, NULL) == 1)
        printf ("sending 1");
    else if (sigaction(SIGUSR2, &sa, NULL) == 0)
        printf ("sending 0");
    while (1)
    {
        sleep(1);// ???
    }
    return(0);
}