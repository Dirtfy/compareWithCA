#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(){
    srand(time(NULL));

    int T;
    int a, b, c;
    // T = rand()%8+1;
    T = 5;
    printf("%d\n", T);
    while(T-- > 0){
        a = rand()%3+1;
        switch(a){
            case 1:
                b = rand()%4;
                c = rand()%4;
                break;
            case 2:
                b = rand()%4;
                c = rand()%3;
                break;
            case 3:
                b = rand()%3;
                c = rand()%4;
                break;
        }

        printf("%d %d %d\n", a, b, c);
    }
    

    return 0;
}
