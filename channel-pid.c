// Напишете програма на C, която извежда информация за процесите, в които е стартиран редактор vi, във файла подаден като
// аргумент в командния ред при стартиране. Прехвърля получения файл в директория /procinfo.

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define ERROR 2

int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        err(1, "Invalid arguments");
    }
    int pfd[2];
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        err(2, "Cannot open file");
    }
    pid_t p1 = fork();
    if (p1 < 0)
    {
        err(3, "First fork error ");
    }
    if (p1 == 0)
    {
        if (pipe(pfd) < 0)
        {
            err(4, "Pipe error");
        }
        pid_t p2 = fork();
        if (p2 < 0)
        {
            err(3, "Second fork error");
        }
        if (p2 == 0)
        {
            dup2(pfd[WRITE], WRITE);
            close(pfd[WRITE]);
            close(pfd[READ]);
            close(fd);
            execlp("ps", "ps", "aux", NULL);
        }
        int status1;
        wait(&status1);
        dup2(pfd[READ], READ);
        close(pfd[WRITE]);
        close(pfd[READ]);
        dup2(fd, WRITE);
        close(fd);
        execlp("grep", "grep", "vi", NULL);
    }
    int status2;
    wait(&status2);
    close(fd);
    execlp("mv", "mv", argv[1], "/Users/errorgeorgiev/Desktop", NULL);
    return 0;
}