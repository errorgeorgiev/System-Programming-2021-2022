#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
    nachalo predi vsichko
    golqmo dete
    krai
    golqm roditel
    malko dete
    krai
    maluk roditel
    krai
*/
int main(int argc, char *argv[])
{
    int status;
    printf("begin\n");
    if (fork()) // parent
    {
        wait(&status);
        printf("first parent\n");
        if (fork() == 0) // child
        {
            printf("second child\n");
            exit(0);
        }
        else // parent
        {
            wait(&status);
            printf("second parent\n");
            exit(0);
        }
    }
    else // child
    {
        printf("first child\n");
        exit(0);
    }
    printf("end\n");
}