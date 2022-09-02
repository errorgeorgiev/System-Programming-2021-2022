# System-Programming-2021-2022
Linux System Programming Course at FMI/Sofia University

Problems: 

1. File I/O
2. Buffered I/O
3. Advanced File I/O
4. Process Management
5. Advanced Process Management
6. File and Directory Management
7. Memory Management
8. Signals
9. Time
10. GCC Extensions to the C Language

Theory:

1. Файлов дескриптор: абстракция за информационен канал между процес и други обекти в
ОС UNIX.
2. Права за достъп в UNIX, потребители и групи, асоциирани с информационните обекти
(файлове, процеси).
3. Основни системни извиквания за ползване на файлов дескриптор: read(2), write(2), close(2).
4. Работа с обикновени файлове: open(2), lseek(2).
5. Анонимни и именувани тръби pipe(7): pipe(2), mkfifo(2).
6. Атрибути на файлове и тяхната промяна: stat(2), chmod(2), chown(2), umask(2), utime(2).
7. Манипулиране на файлов дескриптор: fcntl(2), dup(2).
8. Връзки в пространството на имената: link(2), symlink(7), unlink(2).
9. Работа с каталози: mkdir(2), rmdir(2), chdir(2), opendir(3), readdir(3), closedir(3), rewinddir(3).
10. Монтиране и синхронизация: mount(2), umount(2), sync(2), fsync(2).
11. Управление на процеси: fork(2), exit(3), atexit(3), wait(2), exec(3), getpid(2), getppid(2).
12. Права и идентификатори на процес: setuid(2), getuid(2), geteuid(2), credentials(7).
13. Групи процеси и сесия: setpgrp(2), setpgid(2), getpgrp(2), getpgid(2), setsid(2), getsid(2).
14. Изпращане и обработка на сигнали signal(7): signal(2), kill(2), pause(2), alarm(2).
15. Разговори между процеси чрез socket(7): socket(2), connect(2), bind(2), listen(2), accept(2).
16. Споделена памет shm_overview(7): shm_open(3), ftruncate(2), mmap(2).
17. Семафори sem_overview(7): sem_init(3), sem_post(3), sem_wait(3), sem_destroy(3).
18. Съобщения mq_overview(7): mq_open(3), mq_send(3), mq_receive(3).
19. Нишки в POSIX: pthreads(7).
