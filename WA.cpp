#include<iostream>
using namespace std;
int N, t, x, y, ans, checkans;
int green[7][5];
int blue[7][5];
void print() {
   cout << "green\n\n";
   for (int i = 0;i < 6;i++) {
      for (int j = 0;j < 4;j++) {
         cout << green[i][j] << ' ';
      }
      cout << '\n';
   }
   cout << "blue\n\n";
   for (int i = 0;i < 6;i++) {
      for (int j = 0;j < 4;j++) {
         cout << blue[i][j] << ' ';
      }
      cout << '\n';
   }
}

void check() {
   for (int i = 0;i < 6;i++) {
      for (int j = 0;j < 4;j++) {
         if (green[i][j] != 0)checkans++;
         if (blue[i][j] != 0)checkans++;
      }
   }
}

void move(int mode, int high, int st, int len) {
   int r = -1, rr = 987654321;
   for (int i = 0;i <= 5;i++) {
      if (mode == 0) {//green
         if (green[i][st] != 0) {
            r = i; break; 
         }
      }
      else if (mode == 1) {//blue
         if (blue[i][st] != 0) {
            r = i; break;
         }
      }
      if (i == 5)r = 6;
   }
   if (len == 2) {
      for (int i = 0;i <= 5;i++) {
         if (mode == 0) {//green
            if (green[i][st + 1] != 0) {
               rr = i; break;
            }
         }
         else if (mode == 1) {//blue
            if (blue[i][st + 1] != 0) {
               rr = i; break;
            }
         }
         if (i == 5)rr = 6;
      }
   }
   r = min(rr, r);
   r -= 1;
   if (len == 1 && high == 1) {
      if (mode == 0) green[r][st] = 1;
      else if (mode == 1) blue[r][st] = 1;
   }
   else if (len == 2) {
      if (mode == 0) {
         green[r][st] = 1; green[r][st + 1] = 1;
      }
      else if (mode == 1) {
         blue[r][st] = 1; blue[r][st + 1] = 1;
      }
   }
   else if (high == 2) {
      if (mode == 0) {
         green[r][st] = 1; green[r - 1][st] = 1;
      }
      else if (mode == 1) {
         blue[r][st] = 1; blue[r - 1][st] = 1;
      }
   }
}
void down() {
   int high = 0, st = -1, len = -1, H = 0, St = -1, Len = -1;
   switch (t) {
   case 1:
      high = 1; st = y; len = 1; H = 1; St = x; Len = 1; break;

   case 2:
      high = 1; st = y; len = 2; H = 2; St = x; Len = 1; break;
   case 3:
      high = 2; st = y; len = 1; H = 1; St = x; Len = 2; break;
   }
   //green
   move(0, high, st, len);
   //blue
   move(1, H, St, Len);
}

void erase(int mode, int n) {
   //cout << "erase\n";
   //cout << mode << ' ' << n << '\n';
   for (int i = n;i > 0;i--) {
      for (int j = 0;j < 4;j++) {
         if (mode == 0) {
            green[i][j] = green[i - 1][j];
         }
         else if (mode == 1) {
            blue[i][j] = blue[i - 1][j];
         }
      }
   }
   for (int j = 0;j < 4;j++) {
      green[0][j] = 0;
      blue[0][j] = 0;
   }
}
void fullerase() {
   for (int i = 5;i >= 0;i--) {
      //cout << "i" << i << '\n';
      bool greenflag = true;
      for (int j = 0;j < 4;j++) {
         if (green[i][j] == 0)greenflag = false;
      }
      if (greenflag) {
         erase(0, i);
         ans += 1;
         i++;
      }
   }
   for (int i = 5;i >= 0;i--) {
      bool blueflag = true;
      for (int j = 0;j < 4;j++) {
         if (blue[i][j] == 0)blueflag = false;
      }
      if (blueflag) {
         erase(1, i);
         ans += 1;
         i++;
      }
   }
}

void lighterase() {
   int bluef = 0;
   int greenf = 0;
   for (int i = 1;i >= 0;i--) {
      for (int j = 0;j < 4;j++) {
         if (green[i][j] != 0) {
            greenf++;
            break;
         }
      }
   }
   for (int i = 1;i >= 0;i--) {
      for (int j = 0;j < 4;j++) {
         if (blue[i][j] != 0) {
            bluef++;
            break;
         }
      }
   }
   //cout << bluef << greenf << '\n';
   for (int i = 0;i < greenf;i++) {
      erase(0, 5);
   }
   for (int i = 0;i < bluef;i++) {
      erase(1, 5);
   }
}

void solve() {
   down();
   fullerase();
   lighterase();
   //print();
}
int main() {
   ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   cin >> N;
   while (N--) {
      cin >> t >> x >> y;
      solve();
   }
   check();
   cout << ans << '\n';
   cout << checkans;
}