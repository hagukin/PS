#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> pos;
int N, W;
pos positions[1002];
int dp[1001][1001]; // dp[a][b] = 경찰차1이 a번 위치, 경찰차2가 b번 위치일때 남은 모든 사건 해결을 위해 필요한 최소 거리
bool found[1001][1001]; // dp[a][b]를 구했는지 여부. if(dp[a][b])를 안쓰는 이유는 min()을 사용해야하는데 dp를 0이나 -1로 초기화하기 애매하기때문에 그냥 속편하게 이렇게 구현

/*
점화식
dp[a][b] = min(dp[a+1][b] + dist(a,a+1), dp[a][a+1] + dist(b,a+1))

문제에서는 총거리 + 각 사건별 어떤 경찰차가 해결했는지를 요구한다

총거리는 쉽게 구할 수 있지만 어떤 경찰차가 해결했는지를 묻는게 까다로운데
어떤 경로를 따라왔는지를 backtracking하기에는 노드가 1000개나 되서 오브젝트 복사하는데 시간이 너무 오래 걸림,

깔끔한 풀이: https://chanqun.tistory.com/267
*/

// 구현중
int getDist(int pt1, int pt2)
{
    return abs(positions[pt1].first - positions[pt2].first) + abs(positions[pt1].second - positions[pt2].second);
}

int solve(int x, int y)
{
    int a = max(x, y) + 1;
    if (a > W) return 0; // TODO: 테스트해보기 >= 아닌가?
    if (found[x][y]) return dp[x][y];
    found[x][y] = true;
    return dp[x][y] = min(solve(a, y) + z(1, x, a), solve(x, a) + z(N, y, a));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> W;
    int tmp1, tmp2;
    for (int i=1;i<=W;++i)
    {
        cin >> tmp1 >> tmp2;
        positions[i] = make_pair(tmp1, tmp2);
    }
    
    return 0;
}
