#include <stdio.h>   // fprintf()
#include <unistd.h>  // fork(), exec()
#include <string.h>  // strerror()
#include <errno.h>   // errno
#include <stdlib.h>  // exit()

void forkAndExecute (const char *path, char *const args[]) {
    int pid = fork();
    if (pid == -1) {
        fprintf ( stderr,
            "fork() failed: %s",
            strerror(errno)
        );
        return;
    }
    if (pid != 0) return;
// If pid == 0, this is the child process.
    if (execvp(path, args) == -1) {
        fprintf ( stderr,
            "execvp(%s) failed: %s %s",
            path, strerror(errno)
        );
        exit(-1);
    }
} 
int main (int argc, const char *argv[]) {
    char *const args[] = { "ls", "-l", "/" };
    forkAndExecute("cd /home/pi/mw00899/project/", args);
    puts("Hello world");
    return 0;
}  
