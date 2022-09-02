#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <err.h>

#define YES 1
#define NO 0
#define MAXLINE 80
#define MAXARG 10

char *arg[MAXARG], com[MAXLINE];

// command interpreter
int input_l()
{
    int i, j, nbyt, word;

    word = NO;
    j = 0;
    i = 0;
    while ((nbyt = read(0, &com[j], 1)) != 0)
    {
        if (com[j] == ' ')
        {
            if (word == YES)
            {
                word = NO;
                com[j++] = '\0';
            }
        }
        else if (com[j] != '\n')
        {
            if (word == NO)
            {
                word = YES;
                arg[i++] = &com[j];
            }
            ++j;
        }
        else if (com[j] == '\n')
        {
            if (word == YES)
                com[j] = '\0';
            arg[i] = NULL;
            if (strcmp(arg[0], "logout") == 0)
                exit(0);
            else
                return (i);
        }
    }
    if (nbyt == 0)
        exit(0);
    return 0;
}

int main(void)
{
    int input, pid;

    if (write(1, "terminal>", 9) != 9)
    {
        err(1, "Write failed\n");
    }
    while ((input = input_l()) >= 0)
    {
        if (input)
        {
            if ((pid = fork()) < 0)
            {
                err(2, "Cannot fork\n");
            }
            else
            {
                if (pid != 0)
                    wait(&pid);
                else
                {
                    if (execvp(arg[0], arg) < 0)
                    {
                        err(3, "Cannot exec\n");
                    }
                    // write(1,"cannot exec ",12);
                    if (write(1, arg[0], 10) != 10)
                    {
                        err(1, "Write failed\n");
                    }
                    exit(0);
                }
            }
        }
        if (write(1, "terminal>", 9) != 9)
        {
            err(1, "Write failed\n");
        }
    }
    exit(0);
}
