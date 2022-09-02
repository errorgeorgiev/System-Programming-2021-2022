#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sys/wait.h>

// trying out read/write commands and their values
// trying to read a file symbol by symbol and printing it in cli

// works
int main(const int argc, const char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    char buff[20];
    if (fd < 0)
    {
        errx(1, "Cannot open file");
    }
    int number;
    while ((number = read(fd, buff, 20)) != 0)
    {
        printf("Number: %d\n", number); // read return the number of characters in the file, new line is +1 character
        for (int i = 0; i < number; i++)
        {
            printf("%c", buff[i]);
        }
    }
}