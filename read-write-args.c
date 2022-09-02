// Напишете програма, която приема име на файл като първи параметър и го отваря веднъж за четене и веднъж за писане. Дава грешка, ако
// файлът не може да бъде отворен. Чете от файла символ по символ и всеки прочетен елемент го записва в края на файла, докато
// не срещне цифра. Когато срещне цифра, записва останалата част от файла на стандартния изход

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <stdbool.h>
// works
int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        errx(1, "Invalid arguments");
    }
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[1], O_WRONLY | O_APPEND);
    if (fd1 < 0)
    {
        errx(2, "Cannot open file for reading");
    }
    if (fd2 < 0)
    {
        errx(2, "Cannot open file for writing");
    }
    char buffer[2];
    int readbyte;
    bool flag = false;
    while ((readbyte = read(fd1, buffer, 1)) > 0)
    {
        // printf("Readbyte = %d\n", readbyte);
        if (buffer[0] >= '0' && buffer[0] <= '9')
        {
            // write(fd2, buffer, 1);
            flag = true;
        }
        if (!flag)
        {
            write(fd2, buffer, 1);
        }
        else
        {
            write(1, buffer, 1);
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}