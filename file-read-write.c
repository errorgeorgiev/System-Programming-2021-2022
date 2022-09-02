// Да се напише програма която получава като параметри две имена на файлове. Чете последователност от символи от стандартния вход.
// Добавя ги след края на файла, чието име е подадено като първи параметър. В прочетения текст замества три символа 'a' c '>' и резултата
// записва във файл, чието име е подадено като втори параметър /ако файла съществува, старото съдържание се изтрива/.

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        err(1, "Invalid arguments");
    }
    int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0)
    {
        err(2, "File could not be open");
    }
    if (fd2 < 0)
    {
        err(2, "File could not be open");
    }
    int number_of_a = 0;
    char buff[2];
    while (read(0, buff, 1) > 0)
    {
        write(fd1, buff, 1);
        if (number_of_a < 3 && buff[0] == 'a')
        {
            number_of_a++;
            write(fd1, ">", 1);
        }
        else
        {
            write(fd2, buff, 1);
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}