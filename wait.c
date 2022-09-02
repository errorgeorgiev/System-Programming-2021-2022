#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t cpid;
    printf("start\n");
    if(fork() == 0) {
        printf("child process is working\n");
        //exit(0);
    }
    else {
        cpid = wait(NULL);
        printf("parent process is working\n");
    }
    printf("parent pid = %d\n",getpid());
    printf("child pid = %d\n",cpid);

    return 0;
}