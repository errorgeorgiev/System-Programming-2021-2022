#include <fcntl.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

// works ls sort

int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        errx(1, "Invalid arguments");
    }

    int pfd[2];
    if (pipe(pfd) < 0)
    {
        errx(2, "Pipe error");
    }
    pid_t p = fork();
    if (p < 0)
    {
        errx(3, "First fork error");
    }
    if (p == 0)
    {
        close(1);
        dup(pfd[1]);
        close(pfd[0]);
        close(pfd[1]);
        execlp(argv[1], argv[1], NULL);
    }
    else
    {
        close(0);
        dup(pfd[0]);
        close(pfd[0]);
        close(pfd[1]);
        execlp(argv[2], argv[2], NULL);
    }
    return 0;
}