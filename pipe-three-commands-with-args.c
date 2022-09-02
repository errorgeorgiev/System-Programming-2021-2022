#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <err.h>

// ./a.out who | grep s81384 | wc -l

//pipe between 3 commands
int main(const int argc, const char* argv[]) {

    // if(argc != 4) {
    //     err(1,"Invalid arguments");
    // }

    int pfd1[2];
    
    if(pipe(pfd1) < 0) {
        err(2,"First pipe error");
    }
    pid_t p1 = fork();
    if( p1 < 0) {
        err(3,"First fork error");
    }
    else if(p1 == 0) {
        int pfd2[2];
        if(pipe(pfd2) < 0) {
            err(2,"Second pipe error");
        }
        pid_t p2 = fork();
        if(p2 < 0) {
            err(3,"Second fork error");
        }
        if(p2 == 0) {
            close(1);
            dup(pfd2[1]);
            close(pfd2[0]);
            close(pfd2[1]);
            execlp("who","who",NULL);
        }
        else {
            close(0);
            dup(pfd2[0]);
            close(pfd2[0]);
            close(pfd2[1]);
            close(1);
            dup(pfd1[1]);
            close(pfd1[0]);
            close(pfd1[1]);
            execlp("grep","grep","errorgeorgiev",NULL);
        }
    }
    else {
        close(0);
        dup(pfd1[0]);
        close(pfd1[0]);
        close(pfd1[1]);
        execlp("wc","wc","-l",NULL);
    }
    return 0;
}