#include <iostream>
#include <string.h>
using namespace std;
int blue[4][6];
int green[6][4];
int score;

void pushback() {
   if (blue[0][1] == 1 || blue[1][1] == 1 || blue[2][1] == 1 || blue[3][1] == 1) {
      //blue[0][5] = blue[1][5] = blue[2][5] = blue[3][5] = 0;
      if (blue[0][0] == 1 || blue[1][0] == 1 || blue[2][0] == 1 || blue[3][0] == 1) {
         //blue[0][4] = blue[1][4] = blue[2][4] = blue[3][4] = 0;
         for (int i = 3; i > -1; i--) {
            blue[0][i + 2] = blue[0][i];
            blue[1][i + 2] = blue[1][i];
            blue[2][i + 2] = blue[2][i];
            blue[3][i + 2] = blue[3][i];
         }
         blue[0][0] = blue[1][0] = blue[2][0] = blue[3][0] = 0;
         blue[0][1] = blue[1][1] = blue[2][1] = blue[3][1] = 0;
      }
      else {
         for (int i = 4; i > -1; i--) {
            blue[0][i + 1] = blue[0][i];
            blue[1][i + 1] = blue[1][i];
            blue[2][i + 1] = blue[2][i];
            blue[3][i + 1] = blue[3][i];
         }
         //blue[0][1] = blue[1][1] = blue[2][1] = blue[3][1] = 0;
      }
   }

   if (green[1][0] == 1 || green[1][1] == 1 || green[1][2] == 1 || green[1][3] == 1) {
      //green[5][0] = green[5][1] = green[5][2] = green[5][3] = 0;
      if (green[0][0] == 1 || green[0][1] == 1 || green[0][2] == 1 || green[0][3] == 1) {
         //green[4][0] = green[4][1] = green[4][2] = green[4][3] = 0;
         for (int i = 3; i > -1; i--) {
            green[i + 2][0] = green[i][0];
            green[i + 2][1] = green[i][1];
            green[i + 2][2] = green[i][2];
            green[i + 2][3] = green[i][3];
         }
         green[0][0] = green[0][1] = green[0][2] = green[0][3] = 0;
         green[1][0] = green[1][1] = green[1][2] = green[1][3] = 0;
      }
      else {
         for (int i = 4; i > -1; i--) {
            green[i + 1][0] = green[i][0];
            green[i + 1][1] = green[i][1];
            green[i + 1][2] = green[i][2];
            green[i + 1][3] = green[i][3];
         }
      }
   }
   /*cout << "pushback blue\n";
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 6; j++) {
         cout << blue[i][j] << ' ';
      }
      puts("");
   }
   cout << "pushback green\n";
   for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 4; j++) {
         cout << green[i][j] << ' ';
      }
      puts("");
   }*/
}

void putblockgreen(int t, int c) {
   int i;
   switch (t) {
   case 1:
      //ㅁ
      for (i = 0; i < 6; i++) {
         if (green[i][c]) break;
      }
      green[i - 1][c] = 1;
      /*cout << "putblock green\n";
      for (int i = 0; i < 6; i++) {
         for (int j = 0; j < 4; j++) {
            cout << green[i][j] << ' ';
         }
         puts("");
      }*/
      
      //같은 행 꽉차면 깨기
      if (green[i - 1][0] == 1 && green[i - 1][1] == 1 && green[i - 1][2] == 1 && green[i - 1][3] == 1) {
         green[i - 1][0] = green[i - 1][1] = green[i - 1][2] = green[i - 1][3] = 0;
         score++;
         for (int j = i - 2; j > -1; j--) {
            green[j + 1][0] = green[j][0];
            green[j + 1][1] = green[j][1];
            green[j + 1][2] = green[j][2];
            green[j + 1][3] = green[j][3];
         }
         green[0][0] = green[0][1] = green[0][2] = green[0][3] = 0;
         /*cout << "crashblock green\n";
         for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
               cout << green[i][j] << ' ';
            }
            puts("");
         }*/
      }
      break;
   case 3:
      //ㅁ
      //ㅁ
      for (i = 0; i < 5; i++) {
         if (green[i][c] || green[i + 1][c]) break;
      }
      green[i - 1][c] = green[i][c] = 1;
      /*cout << "putblock green\n";
      for (int i = 0; i < 6; i++) {
         for (int j = 0; j < 4; j++) {
            cout << green[i][j] << ' ';
         }
         puts("");
      }*/
      if (green[i][0] == 1 && green[i][1] == 1 && green[i][2] == 1 && green[i][3] == 1) {
         green[i][0] = green[i][1] = green[i][2] = green[i][3] = 0;
         score++;
         if (green[i - 1][0] == 1 && green[i - 1][1] == 1 && green[i - 1][2] == 1 && green[i - 1][3] == 1) {
            green[i - 1][0] = green[i - 1][1] = green[i - 1][2] = green[i - 1][3] = 0;
            score++;
            for (int j = i - 2; j > -1; j--) {
               green[j + 2][0] = green[j][0];
               green[j + 2][1] = green[j][1];
               green[j + 2][2] = green[j][2];
               green[j + 2][3] = green[j][3];
            }
            green[0][0] = green[0][1] = green[0][2] = green[0][3] = 0;
         }
         else {
            for (int j = i - 1; j > -1; j--) {
               green[j + 1][0] = green[j][0];
               green[j + 1][1] = green[j][1];
               green[j + 1][2] = green[j][2];
               green[j + 1][3] = green[j][3];
            }
            green[0][0] = green[0][1] = green[0][2] = green[0][3] = 0;
         }
         /*cout << "crashblock green\n";
         for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
               cout << green[i][j] << ' ';
            }
            puts("");
         }*/
      }
      else if (green[i - 1][0] == 1 && green[i - 1][1] == 1 && green[i - 1][2] == 1 && green[i - 1][3] == 1) {
         green[i - 1][0] = green[i - 1][1] = green[i - 1][2] = green[i - 1][3] = 0;
         score++;
         for (int j = i - 2; j > -1; j--) {
            green[j + 1][0] = green[j][0];
            green[j + 1][1] = green[j][1];
            green[j + 1][2] = green[j][2];
            green[j + 1][3] = green[j][3];
         }
         green[0][0] = green[0][1] = green[0][1] = green[0][1] = 0;
         /*cout << "crashblock green\n";
         for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
               cout << green[i][j] << ' ';
            }
            puts("");
         }*/
      }
      break;
   case 2:
      //ㅁㅁ
      for (i = 0; i < 6; i++) {
         if (green[i][c] || green[i][c + 1]) break;
      }
      green[i - 1][c] = green[i - 1][c + 1] = 1;
      /*cout << "putblock green\n";
      for (int i = 0; i < 6; i++) {
         for (int j = 0; j < 4; j++) {
            cout << green[i][j] << ' ';
         }
         puts("");
      }*/
      //같은 열 꽉차면 깨기
      if (green[i - 1][0] == 1 && green[i - 1][1] == 1 && green[i - 1][2] == 1 && green[i - 1][3] == 1) {
         green[i - 1][0] = green[i - 1][1] = green[i - 1][2] = green[i - 1][3] = 0;
         score++;
         for (int j = i - 2; j > -1; j--) {
            green[j + 1][0] = green[j][0];
            green[j + 1][1] = green[j][1];
            green[j + 1][2] = green[j][2];
            green[j + 1][3] = green[j][3];
         }
         green[0][0] = green[0][1] = green[0][2] = green[0][3] = 0;
         /*cout << "crashblock green\n";
         for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
               cout << green[i][j] << ' ';
            }
            puts("");
         }*/
      }
      break;
   }
}

void putblockblue(int t, int r) {
   int i;
   switch (t) {
   case 1:
      //ㅁ
      for (i = 0; i < 6; i++) {
         if (blue[r][i]) break;
      }
      blue[r][i - 1] = 1;
      /*cout << "putblock blue\n";
      for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 6; j++) {
            cout << blue[i][j] << ' ';
         }
         puts("");
      }*/
      
      //같은 열 꽉차면 깨기
      if (blue[0][i - 1] == 1 && blue[1][i - 1] == 1 && blue[2][i - 1] == 1 && blue[3][i - 1] == 1) {
         blue[0][i - 1] = blue[1][i - 1] = blue[2][i - 1] = blue[3][i - 1] = 0;
         score++;
         for (int j = i - 2; j > -1; j--) {
            blue[0][j + 1] = blue[0][j];
            blue[1][j + 1] = blue[1][j];
            blue[2][j + 1] = blue[2][j];
            blue[3][j + 1] = blue[3][j];
         }
         blue[0][0] = blue[1][0] = blue[2][0] = blue[3][0] = 0;
         /*cout << "crashblock blue\n";
         for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
               cout << blue[i][j] << ' ';
            }
            puts("");
         }*/
      }
      break;
   case 2:
      //ㅁㅁ
      for (i = 0; i < 5; i++) {
         if (blue[r][i] || blue[r][i + 1]) break;
      }
      blue[r][i - 1] = blue[r][i] = 1;
      /*cout << "putblock blue\n";
      for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 6; j++) {
            cout << blue[i][j] << ' ';
         }
         puts("");
      }*/
      if (blue[0][i] == 1 && blue[1][i] == 1 && blue[2][i] == 1 && blue[3][i] == 1) {
         blue[0][i] = blue[1][i] = blue[2][i] = blue[3][i] = 0;
         score++;
         if (blue[0][i - 1] == 1 && blue[1][i - 1] == 1 && blue[2][i - 1] == 1 && blue[3][i - 1] == 1) {
            blue[0][i - 1] = blue[1][i - 1] = blue[2][i - 1] = blue[3][i - 1] = 0;
            score++;
            for (int j = i - 2; j > -1; j--) {
               blue[0][j + 2] = blue[0][j];
               blue[1][j + 2] = blue[1][j];
               blue[2][j + 2] = blue[2][j];
               blue[3][j + 2] = blue[3][j];
            }
            blue[0][0] = blue[1][0] = blue[2][0] = blue[3][0] = 0;
         }
         else {
            for (int j = i - 1; j > -1; j--) {
               blue[0][j + 1] = blue[0][j];
               blue[1][j + 1] = blue[1][j];
               blue[2][j + 1] = blue[2][j];
               blue[3][j + 1] = blue[3][j];
            }
            blue[0][0] = blue[1][0] = blue[2][0] = blue[3][0] = 0;
         }
         /*cout << "crashblock blue\n";
         for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
               cout << blue[i][j] << ' ';
            }
            puts("");
         }*/
      }
      else if (blue[0][i - 1] == 1 && blue[1][i - 1] == 1 && blue[2][i - 1] == 1 && blue[3][i - 1] == 1) {
         blue[0][i - 1] = blue[1][i - 1] = blue[2][i - 1] = blue[3][i - 1] = 0;
         score++;
         for (int j = i - 2; j > -1; j--) {
            blue[0][j + 1] = blue[0][j];
            blue[1][j + 1] = blue[1][j];
            blue[2][j + 1] = blue[2][j];
            blue[3][j + 1] = blue[3][j];
         }
         blue[0][0] = blue[1][0] = blue[2][0] = blue[3][0] = 0;
         /*cout << "crashblock blue\n";
         for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
               cout << blue[i][j] << ' ';
            }
            puts("");
         }*/
      }
      break;
   case 3:
      //ㅁ
      //ㅁ
      for (i = 0; i < 6; i++) {
         if (blue[r][i] || blue[r + 1][i]) break;
      }
      blue[r][i - 1] = blue[r + 1][i - 1] = 1;
      /*cout << "putblock blue\n";
      for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 6; j++) {
            cout << blue[i][j] << ' ';
         }
         puts("");
      }*/
      
      //같은 열 꽉차면 깨기
      if (blue[0][i - 1] == 1 && blue[1][i - 1] == 1 && blue[2][i - 1] == 1 && blue[3][i - 1] == 1) {
         blue[0][i - 1] = blue[1][i - 1] = blue[2][i - 1] = blue[3][i - 1] = 0;
         score++;
         for (int j = i - 2; j > -1; j--) {
            blue[0][j + 1] = blue[0][j];
            blue[1][j + 1] = blue[1][j];
            blue[2][j + 1] = blue[2][j];
            blue[3][j + 1] = blue[3][j];
         }
         blue[0][0] = blue[1][0] = blue[2][0] = blue[3][0] = 0;
         /*cout << "crashblock blue\n";
         for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
               cout << blue[i][j] << ' ';
            }
            puts("");
         }*/
      }
      break;
   }
}

int main() {
   ios::sync_with_stdio; cin.tie(0); cout.tie(0);
   int N; cin >> N;
   while (N--) {
      int t, x, y;
      cin >> t >> x >> y;
      putblockblue(t, x);
      putblockgreen(t, y);
      pushback();
   }
   cout << score << '\n';
   int cnt = 0;
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 6; j++) {
         if (blue[i][j]) cnt++;
         if (green[j][i]) cnt++;
      }
   }
   cout << cnt;
}