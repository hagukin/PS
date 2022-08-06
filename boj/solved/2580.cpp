#include <iostream>
#include <vector>

using namespace std;
int arr[9][9];
vector<pair<int, int>> v; // keypoint 1: 정수를 x,y 좌표로 변경해주기 위해 v 사용

bool check(int y, int x, int i) {
    for (int k = 0; k < 9; k++) 
    {
        if (arr[y][k] == i || arr[k][x] == i)
        return false;
    }
    
    // keypoint 2: 어떤 x,y가 속한 3x3 정사각형 좌표범위를 구하기 위해 int typecast 이용
    for (int k = (y / 3) * 3; k < (y / 3) * 3 + 3; k++) {
        for (int j = (x / 3) * 3; j < (x / 3) * 3 + 3; j++) {
            if (arr[k][j] == i)
                return false;
        }
    }
    return true;
}

bool dfs(int cur) { // 좌표 대신 1~81 정수 사용
    if (cur == v.size()) return true;
    int y = v[cur].first;
    int x = v[cur].second;
    for (int i = 1; i <= 9; i++) {
        if (check(y, x, i)) {
            arr[y][x] = i;
            if (dfs(cur + 1)) return true; // keypoint 3: 답이 되는 경우를 찾았을 경우 굳이 더 해보지 않고 true 반환
            arr[y][x] = 0;
        }
    }
    return false;
}

int main() {
    for (auto & i : arr) for (int & j : i) cin >> j;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (arr[i][j] == 0) v.push_back({i, j});
        }
    }
    dfs(0);
    for (auto & i : arr) { // n dimensional array에도 auto 키워드가 작동함
        for (int & j : i) cout << j << ' ';
        cout << '\n';
    }
    return 0;
}
