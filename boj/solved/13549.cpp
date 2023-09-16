#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
using namespace std;
int memo[100001];
int N, K;
queue<pair<int,int>> q;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(memo, -1, sizeof(memo));
    cin >> N >> K;
    q.push({N, 0});
    while (!q.empty())
    {
        pair<int,int> curr = q.front();
        q.pop();
        if (curr.first > 100000 || curr.second < 0) continue;
        if (memo[curr.first] > curr.second || memo[curr.first] == -1)
        {
            memo[curr.first] = curr.second;
            if (curr.first < K)
            {
                q.push({curr.first * 2, curr.second});
                q.push({curr.first + 1, curr.second + 1});
            }
            q.push({curr.first - 1, curr.second + 1});
        }
    }
    cout << memo[K] << '\n';
    return 0;
}
