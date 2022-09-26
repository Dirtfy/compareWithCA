#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAXLINE 256

int main(){
        char buf[MAXLINE];
        pid_t pid;
        int status;
        printf("@ ");
        while(fgets(buf,MAXLINE, stdin) != NULL){
                if(buf[strlen(buf) - 1] == '\n')
                        buf[strlen(buf) -1] ='\0';

                if((pid = fork()) < 0){
                        printf("fork error\n");
                        exit(1);
                }else if(pid == 0){
                        execlp(buf, buf, NULL);
                        exit(127);
                }

                if((pid = waitpid(pid, &status, 0)) < 0){
                        printf("waitpid error\n");
                }
                printf("@ ");
        }
        return 0;
}