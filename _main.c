#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char **new_argv;
    // char command[]  = "gcc -o main.exe main.c";
    char command[] = ".\\test.exe";
    int  idx;

    for(int i = 0;argv[i] != '\0';i++){
        puts(argv[i]);
    }

    new_argv = (char **)malloc(sizeof(char *) * (argc + 1));

    /* 명령어를 ls로 변경 */
    new_argv[0] = command;

    /* command line으로 넘어온 parameter를 그대로 사용 */
    for(idx = 1; idx < argc; idx++) {
        new_argv[idx] = argv[idx];
    }

    /* argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 파라미터의 끝을 의미함 */
    new_argv[argc] = NULL;

    new_argv[0] = NULL;

    // if(execv("C:/MinGW/bin/gcc", (const char * const*)new_argv) == -1) {
    if(execv("D:/Project/CompareWithCA", (const char * const*)new_argv) == -1) {
        puts("error");
        // fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
        fprintf(stderr, "error: %s\n", strerror(errno));
        return 1;
    }

    /* ls 명령어 binary로 실행로직이 교체되었으므로 이후의 로직은 절대 실행되지 않습니다. */
    printf("이곳이 이제 ls 명령어라 이 라인은 출력이 되지 않습니다.\n");

    return 0;
}