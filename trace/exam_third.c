#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// ff should be empty file
// what is will be written in ff file
// what will be written to stdout
// ./a.out ff ABC

int main(int argc, char *argv[])
{
    int fd, fd1, i, k, status;
    k = dup(1);
    if ((fd1 = open(argv[2], O_RDWR)) == -1)
    {
        printf("\n Cannot open \n");
        exit(1);
    }
    if (fork()) // parent
    {
        wait(&status);
        for (i = 0; i <= 4; i++)
        {
            write(1, "ok!!!\n", 3);
            execlp("head", "head", "-5c", "ABC", NULL);
            if (fork() == 0) // child
            {
                write(1, "ok1!\n", 5);
            }
            else // parent
            {
                write(1, "ok2!\n", 5);
            }
        }
    }
    else // child
    {
        close(1);
        if ((fd = open(argv[1], O_RDWR)) == -1)
        {
            printf("\n Cannot open \n");
            exit(1);
        }
        write(fd1, "ok3!\n", 5);
        write(1, "ok4!\n", 5);
    }
    write(1, "ok5!\n", 5);
    write(k, "ok6!\n", 5);
    execlp("cat", "cat", "ABC", NULL);
    execlp("wc", "wc", "-c", "ff", NULL);
}
