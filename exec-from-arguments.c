#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <err.h>

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        errx(1, "Enter 4 arguments!");
    }
    pid_t p1 = fork();
    if (p1 < 0)
    {
        err(2, "First fork failed!");
    }
    else if (p1 == 0)
    {
        if (execlp("ls", "ls", "-l", "/Users/errorgeorgiev/Desktop", NULL) < 0)
        {
            err(3, "Execlp failed!");
        }
    }
    pid_t p2 = fork();
    if (p2 < 0)
    {
        err(2, "Second fork failed!");
    }
    else if (p2 == 0)
    {
        if (execlp("cp", "cp", argv[1], "/Users/errorgeorgiev/Desktop/f1", NULL) < 0)
        {
            err(3, "Execlp failed!");
        }
    }
    pid_t p3 = fork();
    if (p3 < 0)
    {
        err(2, "Third fork failed!");
    }
    else if (p3 == 0)
    {
        if (execlp(argv[2], argv[2], argv[3], argv[4], NULL) < 0)
        {
            err(3, "Execlp failed!");
        }
    }
    wait(&p3);
    pid_t ppid = getpid();
    printf("Father pid: %u\n", ppid);
    printf("First child pid: %u\n", p1);
    printf("Second child pid: %u\n", p2);

    exit(0);
}