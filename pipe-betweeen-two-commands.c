#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>


// ./a.out ls | sort 

int main(const int argc, const char* argv[]) {
    // argv[1] = command one
    // argv[2] = command two


    if(argc != 3) {
        err(1,"Arguments error");
    }

    int pfd[2];
    if(pipe(pfd) < 0) {
        err(2,"Pipe error");
    }


    pid_t p = fork();

    if( p < 0) {
        err(2,"Fork error");
    }
    else if(p == 0) {
        close(pfd[0]);
        if(dup2(pfd[1],1) < 0) {
            err(3,"Dup error");
        }
        if(execlp(argv[1],argv[1],NULL) < 0) {
            err(4,"Execlp error");
        }
    }
    close(pfd[1]);
    if(dup2(pfd[0],0) < 0) {
        err(3,"Dup error");
    }
    if(execlp(argv[2],argv[2],NULL) < 0) {
        err(4,"Execlp error");
    }


    exit(0);

}