#include <string>
#include <vector>
#include <iostream>

using namespace std;

constexpr int INF = 487654321;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    // 플로이드 워셜로 모든 경로 구하고 min(S-A + S-B, S-i + i-A + i-B를 모든 i에대해) 하면 됨
    int answer = 0;
    int price[201][201];
    
    // 초기화
    for (int i=0;i<201;++i)
    {
        for (int j=0;j<201;++j)
            price[i][j] = INF;
    }
    for (int i=0;i<201;++i) price[i][i] = 0;
    
    for (const vector<int>& fare : fares)
    {
        price[fare[0]][fare[1]] = fare[2];
        price[fare[1]][fare[0]] = fare[2];
    }
    
    // 플로이드 와셜
    for (int y=1;y<=n;++y) // 중개지점
    {
        for (int x=1;x<=n;++x) // 시작지점
        {
            for (int z=1;z<=n;++z) // 도착지점
            {
                price[x][z] = min(price[x][z], price[x][y] + price[y][z]);
            }
        }
    }
    
    // solve
    answer = price[s][a] + price[s][b];
    for (int i=1;i<=n;++i)
    {
        answer = min(answer, price[s][i] + price[i][a] + price[i][b]);
    }
    return answer;
}
