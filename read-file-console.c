// Да се напише програма, която чете последователно по един символ от файл, чието име е
// подадено като първи параметър и по един символ от стандартния вход. Добавя прочетените символи, премахвайки символите
// 0,1,2,3,4,5,6,7,8,9, последователно след края на файл, чието име е подадено като втори параметър, ако файла не съществува
// го създава. Чете се до края на файла или до изчерпване на входния поток.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
// works
int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        errx(1, "Invalid number of arguments");
    }

    char buff1[2];
    char buff2[2];
    int readbytes1;
    int readbytes2;

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
    {
        errx(1, "Could not open first file");
    }
    int fd2 = open(argv[2], O_CREAT | O_WRONLY, 0644);
    if (fd2 < 0)
    {
        errx(1, "Could not open second file");
    }
    while ((readbytes1 = read(0, buff1, 1)) && (readbytes2 = read(fd1, buff2, 1)))
    {
        if (!(buff1[0] >= '0' && buff1[0] <= '9'))
        {
            write(fd2, buff1, 1);
        }
        if (!(buff2[0] >= '0' && buff2[0] <= '9'))
        {
            write(fd2, buff2, 1);
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}