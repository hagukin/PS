#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>
using namespace std;
int S;
queue<pair<int,pair<int,int>>> q; // 현 개수, 클립보드 개수, 시간
int memo[2001][2001]; // 개수, 클립보드 개수 -> 시간
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> S;
    memset(memo, -1, sizeof(memo));
    
    q.push({1, {0, 0}});
    while(!q.empty())
    {
        pair<int,pair<int,int>> curr = q.front();
        q.pop();
        if (curr.first <= 0 || curr.first > 1000) continue;
        if (memo[curr.first][curr.second.first] > curr.second.second || memo[curr.first][curr.second.first] == -1)
        {
            memo[curr.first][curr.second.first] = curr.second.second;
            
            if (curr.second.first > 0) q.push({curr.first + curr.second.first, {curr.second.first, curr.second.second + 1}}); // 붙여넣기
            q.push({curr.first, {curr.first, curr.second.second + 1}}); // 복사
            q.push({curr.first - 1, {curr.second.first, curr.second.second + 1}}); // 삭제
        }
    }
    
    int result = 987654321;
    for (int i = 0; i < 2001; ++i)
    {
        if (memo[S][i] != -1 && memo[S][i] < result) result = memo[S][i];
    }
    cout << result << endl;
    return 0;
}
