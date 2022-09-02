// Да се напише програма, която получава като параметри на командния ред 2 команди, като първата е без параметри.
// Изпълнява ги едновременно. Чака приключването на всяка една от тях и извежда кода на завършване.

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     err(1, "Invalid arguments");
    // }
    int pid1, pid2;
    pid_t p1 = fork();
    if (p1 < 0) // error
    {
        err(2, "First fork error");
    }
    if (p1 > 0) // parent
    {
        pid_t p2 = fork();
        if (p2 < 0) // error
        {
            err(2, "Second fork error");
        }
        if (p2 > 0) // parent
        {
            int status1, status2;
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            printf("Return code 1: %d\nReturn code 2: %d\n", status1, status2);
            exit(0);
        } // child
        execlp(argv[1], argv[1], NULL);
        exit(1);
    } // child
    execvp(argv[2], &argv[2]);
    exit(1);
}