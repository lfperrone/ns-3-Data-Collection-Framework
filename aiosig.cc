#include <stdio.h>
#include <signal.h>

static void
terminate_handler(int signo)
{
    printf("SIGUSR1 caught\n");
}

int
main(int argc, char **argv)
{
    struct sigaction  action;

    // set up a handler for SIGUSR1
    action.sa_handler = terminate_handler;
    sigemptyset(&(action.sa_mask));
    action.sa_flags = 0;
    sigaction(SIGUSR1, &action, NULL);

		for (;;);

    return 0;
}

