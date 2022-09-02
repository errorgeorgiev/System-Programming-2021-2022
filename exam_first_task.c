#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <err.h>
#include <sys/stat.h>

// exam-task-1

int main(const int argc, const char *argv[])
{
    int code;
    if (argc != 4)
    {
        int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
        if (fd < 0)
        {
            err(1, "Cannot open file");
        }
        if (write(fd, "Invalid args", 12) < 0)
        {
            err(2, "Cannot write");
        }
        errx(2, "Invalid arguments");
    }
    pid_t p1 = fork();
    if (p1 < 0)
    {
        err(3, "Cannot fork");
    }
    else if (p1 == 0)
    { // child
        execlp("cp", "cp", argv[2], "/Users/errorgeorgiev/Desktop/f1", NULL);
    }
    wait(&p1);
    int fd1 = open(argv[3], O_RDONLY);
    if (fd1 < 0)
    {
        err(1, "Cannot open file");
    }
    struct stat st;
    if (fstat(fd1, &st) == -1)
    {
        err(4, "Fstat error");
    }
    char *buffer = (char *)malloc((st.st_size - 1) * sizeof(char));
    read(fd1, buffer, st.st_size);
    pid_t p2 = fork();
    if (p2 < 0)
    {
        err(3, "Fork error");
    }
    if (p2 == 0)
    {
        int code = execlp(buffer, buffer, NULL);
    }
    wait(&p2);
    pid_t p3 = fork();
    if (p3 < 0)
    {
        err(3, "Fork error");
    }
    else if (p3 == 0)
    {
        printf("Code of execution %d\n", code);
        exit(1);
    }
    wait(&p3);
    execlp("date", "date", NULL);
}