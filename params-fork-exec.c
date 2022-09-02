// Да се напише програма, която получава 2 параметъра - имена на файлове. Стартира командата tee, като пренасочва стандартния и вход
// от първия файл, а стандартния изход за грешки във втория файл. Накрая извежда кода и на завършване на стандартния изход за грешки,
// като преди това го пренасочва във файл tee_errors.

#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
// works
int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        errx(1, "Invalid arguments");
    }
    int fd1, fd2, fd3;
    pid_t p = fork();
    if (p < 0)
    {
        errx(2, "Error in fork");
    }
    else if (p == 0) // child
    {
        fd1 = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd1 < 0)
        {
            errx(3, "Error opening file");
        }
        fd2 = open(argv[2], O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd2 < 0)
        {
            errx(3, "Error opening file");
        }
        // close(0);
        // close(2);
        dup2(fd1, 0);
        dup2(fd2, 2);
        close(fd1);
        close(fd2);
        execlp("tee", "tee", NULL);
    }
    else // parent
    {
        int status;
        wait(&status);
        fd3 = open("tee_errors", O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd3 < 0)
        {
            errx(3, "Error opening file");
        }
        // close(2);
        dup2(fd3, 2);
        close(fd3);
        char str[10];
        sprintf(str, "%d", status);
        write(2, str, sizeof(str));
    }
    return 0;
}