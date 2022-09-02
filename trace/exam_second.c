#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// we pass from the console who>date
int main(int argc, char *argv[])
{
    int fd, j, nb1, status;
    char buff[5];
    if (fork()) // parent
    {
        wait(&status);
        execlp("wc", "wc", "-c", "fileF.txt", 0);
    }
    else // child
    {
        j = dup(1);
        if ((fd = open(argv[1], O_RDWR)) == -1)
        {
            printf("error open file\n");
            exit(1);
        }
        nb1 = read(0, buff, 4);
        write(j, buff, nb1);
        if (fork()) // parent
        {
            wait(&status);
            close(1);
            dup(fd);
            nb1 = read(fd, buff, 5);
            write(1, buff, nb1);
        }
        // child
        write(j, buff, 3);
        write(1, "\n", 1);
        close(fd);
        close(j);
        exit(0);
        return 0;
    }
}
