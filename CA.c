#include<stdio.h>

#define MAX_N 500
#define MARGIN 1

typedef struct{
    int x, y;
}Pos;

typedef struct{
    Pos p;
    int value;
}Spot;

int Map[MAX_N+MARGIN][MAX_N+MARGIN];
int Cnt[MAX_N+MARGIN][MAX_N+MARGIN];
Spot List[MAX_N*MAX_N+MARGIN];  int End = -1;

void sort(Spot list[], int left, int right);
void record(Spot list[], int end, const int n, const int m);

int main(){
    int N, M;
    int i, j;

    scanf("%d %d", &M, &N);
    for(i = 1;i <= M;i++){
        for(j = 1;j <= N;j++){
            scanf("%d", &Map[i][j]);

            List[++End].value = Map[i][j];
            List[End].p.x = j;
            List[End].p.y = i;
        }
    }

    sort(List, 0, End);
    record(List, End, N, M);

    printf("%d", Cnt[M][N]);

    return 0;
}

int comparePos(Pos p1, Pos p2){
    if(p1.y > p2.y)
        return -1;
    else if(p1.y < p2.y)
        return 1;
    else{
        if(p1.x > p2.x)
            return -1;
        else if(p1.x < p2.x)
            return 1;
        else
            return 0;
    }
}
int compare(Spot s1, Spot s2){
    if(s1.value > s2.value)
        return -1;
    else if(s1.value < s2.value)
        return 1;
    else{
        return comparePos(s1.p, s2.p);
    }
}
void sort(Spot list[], int left, int right){
    int mid = (left+right)/2;
    int l = left, r = mid+1;
    Spot tmp[right-left+MARGIN];    int i = 0;

    if(left < right){
        sort(list, left, mid);
        sort(list, mid+1, right);

        while(l <= mid && r <= right){
            if(compare(list[l], list[r]) <= 0)
                tmp[i++] = list[l++];
            else
                tmp[i++] = list[r++];
        }

        while(l <= mid){
            tmp[i++] = list[l++];
        }
        while(r <= right){
            tmp[i++] = list[r++];
        }

        for(i = left;i <= right;i++){
            list[i] = tmp[i-left];
        }
    }
}
void record(Spot list[], int end, const int n, const int m){
    int move[5] = {0, -1, 0, 1, 0}, j, i;
    Pos start = {1, 1}, finish = {n, m};
    Pos adjacent;

    for(i = 0;comparePos(list[i].p, start) != 0;i++){ }

    Cnt[start.y][start.x] = 1;

    for(;comparePos(list[i].p, finish) != 0 && i <= End;i++){
        for(j = 0;j < 4;j++){
            adjacent.x = list[i].p.x+move[j];
            adjacent.y = list[i].p.y+move[j+1];

            if((1 <= adjacent.x&&adjacent.x <= n) && (1 <= adjacent.y&&adjacent.y <= m)){
                if(Map[adjacent.y][adjacent.x] < Map[list[i].p.y][list[i].p.x]){
                    Cnt[adjacent.y][adjacent.x] += Cnt[list[i].p.y][list[i].p.x];
                }
            }
        }
    }
}

