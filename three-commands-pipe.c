#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// works ./a.out ls sort head
// three commands pipe

int main(const int argc, const char *argv[])
{
    if (argc != 4)
    {
        errx(1, "Invalid arguments");
    }
    int pfd1[2];
    if (pipe(pfd1) < 0)
    {
        errx(2, "Invalid first pipe");
    }
    pid_t p1 = fork();
    if (p1 < 0)
    {
        errx(3, "Invalid first fork");
    }
    if (p1 == 0)
    {
        close(1);
        dup(pfd1[1]);
        close(pfd1[0]);
        close(pfd1[1]);
        execlp(argv[1], argv[1], NULL);
    }
    int pfd2[2];
    if (pipe(pfd2) < 0)
    {
        errx(2, "Invalid second pipe");
    }
    pid_t p2 = fork();
    if (p2 < 0)
    {
        errx(3, "Invalid second fork");
    }
    if (p2 == 0)
    {
        close(1);
        dup(pfd2[1]);
        close(pfd2[0]);
        close(pfd2[1]);
        execlp(argv[1], argv[1], NULL);
    }

    int status2;
    wait(&status2);
    close(0);
    dup2(pfd1[0], 0);
    close(pfd1[0]);
    close(pfd1[1]);
    execlp(argv[3], argv[3], NULL);

    return 0;
}