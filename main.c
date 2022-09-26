#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_FILE_NAME_LEN 100
#define MAX_SYSTEM_COMMAND_LEN 200

#define INPUT_TEXT_FILE_NAME "input.txt"
#define CA_OUTPUT_TEXT_FILE_NAME "output_CA.txt"
#define WA_OUTPUT_TEXT_FILE_NAME "output_WA.txt"

#define INPUT_GENERATER_EXE_FILE_NAME "input_Generater.exe"
#define CA_EXE_FILE_NAME "CA.exe"
#define WA_EXE_FILE_NAME "WA.exe"

#define SYSTEM_SPACE " "
#define SYSTEM_NOW_FOLDER ".\\"
#define SYSTEM_GCC_COMPILE_PREFIX "gcc -o"
#define SYSTEM_GPP_COMPILE_PREFIX "g++ -o"
#define SYSTEM_DELETE "del"

#define ERROR_TEXT_UNKNOWN_EXTENSION "error : Unknown filename extension"
#define ERROR_TEXT_SYSTEM_COMMAND "error : System command error"

void write_input_file(char *generaterName);
int compile(char *fileName, char *outName);
void run_exe(char *exeFileName);
void delete_file(char *fileName);
int compare_file(char *fileName_1, char *fileName_2);
int compare_output(char *inputFileName);
void print_file(char *fileName, int start_cursor, int end_cursor);

int main(int argc, char *argv[])
{
    char *CA_codeName;
    char *WA_codeName;
    char *generaterName;

    if(argc == 3+1){
        CA_codeName = argv[1];
        WA_codeName = argv[2];
        generaterName = argv[3];        

        compile(generaterName, INPUT_GENERATER_EXE_FILE_NAME);
        compile(CA_codeName, CA_EXE_FILE_NAME);
        compile(WA_codeName, WA_EXE_FILE_NAME);

        int T;
        printf("Test Count : ");
        scanf("%d", &T);
        while(T-- > 0){
            write_input_file(generaterName);
            if(compare_output(INPUT_TEXT_FILE_NAME) == 1)
                return 1;
        }

        return 0;
    }
    else if(argc == 2+1){
        char inputFileName[MAX_FILE_NAME_LEN];

        printf("input file name : ");
        gets(inputFileName);

        CA_codeName = argv[1];
        WA_codeName = argv[2];

        compile(CA_codeName, CA_EXE_FILE_NAME);
        compile(WA_codeName, WA_EXE_FILE_NAME);

        return compare_output(inputFileName);
    }
    else{
        puts("wrong arguments");

        return -1;
    }
}

int _system(char *system_command){
    FILE *con = fopen("CON", "w");
    fputs(system_command, con);
    fputs("\n", con);
    fclose(con);
    if(system(system_command) == 0){
        return 0;
    }
    else{
        FILE *con = fopen("CON", "w");
        fputs(ERROR_TEXT_SYSTEM_COMMAND, con);
        fputs("\n", con);
        fclose(con);
        exit(-1);
        return -1;
    }
}

void write_input_file(char *generaterName){
    char system_command[MAX_SYSTEM_COMMAND_LEN];
    
    freopen(INPUT_TEXT_FILE_NAME, "w+", stdout);
    run_exe(INPUT_GENERATER_EXE_FILE_NAME);
    freopen("CON", "w" ,stdout);

    //delete_file(INPUT_GENERATER_EXE_FILE_NAME);
}
int getExtension(char *fileName, char *extension){
    for(int i = 0;fileName[i] != '\0';i++){
        if(fileName[i] == '.'){
            extension[0] = '\0';
            strcat(extension, fileName+(i+1));
            return 0;
        }
    }
    return 1;
}
int compile(char *fileName, char *outName){
    char system_command[MAX_SYSTEM_COMMAND_LEN];
    char extension[MAX_FILE_NAME_LEN];

    if(getExtension(fileName, extension) == 0){
        system_command[0] = '\0';

        if(strcmp(extension, "c") == 0)
            strcat(system_command, SYSTEM_GCC_COMPILE_PREFIX);
        else if(strcmp(extension, "cpp") == 0)
            strcat(system_command, SYSTEM_GPP_COMPILE_PREFIX);
        else{
            puts(ERROR_TEXT_UNKNOWN_EXTENSION);
            return 1;
        }
        
        strcat(system_command, SYSTEM_SPACE);
        strcat(system_command, outName);
        strcat(system_command, SYSTEM_SPACE);
        strcat(system_command, fileName);

        _system(system_command);

        return 0;
    }

    return 2;
}
void run_exe(char *exeFileName){
    char system_command[MAX_SYSTEM_COMMAND_LEN];

    system_command[0] = '\0';
    strcat(system_command, SYSTEM_NOW_FOLDER);
    strcat(system_command, exeFileName);
    
    _system(system_command);
}
void delete_file(char *fileName){
    char system_command[MAX_SYSTEM_COMMAND_LEN];

    system_command[0] = '\0';
    strcat(system_command, SYSTEM_DELETE);
    strcat(system_command, SYSTEM_SPACE);
    strcat(system_command, SYSTEM_NOW_FOLDER);
    strcat(system_command, fileName);
    
    _system(system_command);
}
int compare_file(char *fileName_1, char *fileName_2){
    FILE *file_1 = fopen(fileName_1, "r");
    FILE *file_2 = fopen(fileName_2, "r");
    char c_1, c_2;

    while((c_1 = fgetc(file_1)) == (c_2 = fgetc(file_2)) && (c_1 != EOF && c_2 != EOF)){ }

    fclose(file_1);
    fclose(file_2);

    if(c_1 == EOF && c_2 == EOF)
        return 0;
    else
        return 1;
}
int compare_output(char *inputFileName){
    freopen(inputFileName, "r", stdin);

    // fseek(stdin, 0, SEEK_END);
    // int eof_position = ftell(stdin);

    // fseek(stdin, 0, SEEK_SET);
    // int case_start_cursor = ftell(stdin), case_end_cursor;

    // printf("%d %d\n", case_start_cursor, eof_position);

    // do{
        freopen(CA_OUTPUT_TEXT_FILE_NAME, "w+", stdout);
        run_exe(CA_EXE_FILE_NAME);
        freopen("CON", "w", stdout);

        // case_end_cursor = ftell(stdin);
        // fseek(stdin, case_start_cursor, SEEK_SET);
        fseek(stdin, 0, SEEK_SET);

        freopen(WA_OUTPUT_TEXT_FILE_NAME, "w+", stdout);
        run_exe(WA_EXE_FILE_NAME);
        freopen("CON", "w", stdout);

        if(compare_file(CA_OUTPUT_TEXT_FILE_NAME, WA_OUTPUT_TEXT_FILE_NAME) != 0){
            puts("Wrong!\n");

            puts("Case : ");
            // print_file(INPUT_TEXT_FILE_NAME, case_start_cursor, case_end_cursor);
            print_file(INPUT_TEXT_FILE_NAME, 0, -1);
            puts("");

            puts("CA : ");
            print_file(CA_OUTPUT_TEXT_FILE_NAME, 0, -1);
            puts("");
            
            puts("WA : ");
            print_file(WA_OUTPUT_TEXT_FILE_NAME, 0, -1);

            return 1;
        }

    //     printf("%d %d\n", case_start_cursor, case_end_cursor);

    //     case_start_cursor = case_end_cursor;
    // }while(ftell(stdin) != eof_position);
    freopen("CON", "r", stdin);

    puts("Correct!");

    return 0;
}
void print_file(char *fileName, int start_cursor, int end_cursor){
    FILE *file = fopen(fileName, "r");
    FILE *con = fopen("CON", "w");
    if(end_cursor == -1){
        char ch;
        while((ch = fgetc(file)) != EOF){
            fputc(ch, con);
        }
    }
    else{
        fseek(file, start_cursor, SEEK_SET);
        while(ftell(file) < end_cursor){
            fputc(fgetc(file), con);
        }
    }
    fclose(file);
    fclose(con);
}
