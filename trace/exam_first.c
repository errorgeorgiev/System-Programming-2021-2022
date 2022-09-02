#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int status;
    int a = 1000;
    printf("\nStoinossta na a = %d", a);
    if (fork()) // parent
    {
        a /= 2;
        printf("\nStoinossta na a = %d", a);
    }
    else // child
    {
        if (fork()) // parent
        {
            a *= 2;
            printf("\nStoinossta na a = %d", a);
            if (execlp("ls", "ls", "-l", 0) == -1)
            {
                a = a + 2;
                printf("\nStoinossta na a = %d", a);
            }
        }
        else // child
        {
            a += 2;
            printf("\nStoinossta na a = %d", a);
        }
    }
    a++;
    printf("\nStoinossta na a = %d", a);
    return 0;
}
