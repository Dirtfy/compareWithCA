#include<stdio.h>

#define MAX_N 500
#define MARGIN 1

#define NOT_CHECKED 0
#define CHECKED 1

int Map[MAX_N+MARGIN][MAX_N+MARGIN];
int Record[MAX_N+MARGIN][MAX_N+MARGIN];

int DFS(int x, int y, const int N, const int M);

int main(){
    int M, N;

    scanf("%d %d", &M, &N);
    for(int i = 0;i < M;i++){
        for(int j = 0;j < N;j++){
            scanf("%d", &(Map[i][j]));
        }
    }
    
    Record[M-1][N-1] = 1;
    printf("%d", DFS(0, 0, N, M));

    // puts("");
    // for(int i = 0;i < M;i++){
    //     for(int j = 0;j < N;j++){
    //         printf("%d ", Record[i][j]);
    //     }puts("");
    // }puts("");

    return 0;
}

int DFS(int x, int y, const int N, const int M){
    if(Record[y][x] != 0)
        return Record[y][x];
    else{
        int move[5] = {0, -1, 0, 1, 0};
        int nx, ny;
        int count = 0;

        for(int i = 0;i < 4;i++){
            nx = x+move[i];   ny = y+move[i+1];

            if((0 <= nx&&nx < N) && (0 <= ny&&ny < M)){
                if(Map[ny][nx] < Map[y][x]){
                    count += DFS(nx, ny, N, M);
                }
            }
        }

        Record[y][x] = count;

        return count;
    }
}