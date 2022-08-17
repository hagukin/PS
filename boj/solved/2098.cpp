#include <iostream>
#include <cstring>
using namespace std;

constexpr int MAXN = 16;
constexpr int DPNUM = 1<<MAXN;
constexpr int INT_MAX = 17000000;
// climits의 INT_MAX 사용시 오답. 
// 왜? visited == ALLONE일 경우이면서 lastNode가 0이면 자기자신으로 가는 경로가 없기 때문에 INT_MAX를 반환하는데,
// 상위호출함수가 이 값에 W[lastNode][i]를 반복하므로 오버플로우 발생해서 엄청나게 작은 값이 되어버림.
// 때문에 min()에서 이 값이 살아남아 최종적으로 값이 -21억에 가까운 이상한 값이 나오게됨.
// 그렇다면 이 값은 얼마 정도로 해야 적당한가?
// 1600만보다 크기만 하면 됨. (각 간선 비용 최대 100만, 노드 최대 16개)

int dp[DPNUM][MAXN]; // dp[visited][lastNode] = visited들을 방문했고 마지막 노드가 lastNode일때 가능한 비용의 합의 최솟값.
int W[MAXN][MAXN];
int N;
int ALLONE;

bool getIdx(int x, int idx) // 역순 (맨 우측이 idx 0번)
{
    return ((x >> idx) & 1);
}

int setIdxOne(int origin, int idx)
{
    int funcRet = origin;
    funcRet |= (1<<idx);
    return funcRet;
}

int setIdxZero(int origin, int idx)
{
    if (!getIdx(origin, idx)) return origin;
    int funcRet = ~origin;
    funcRet = setIdxOne(funcRet, idx);
    funcRet = ~funcRet;
    return funcRet;
}

int dfs(int visited, int lastNode) 
// visited들을 방문했고 현재 lastNode일때 남은 모든 도시를 다 순회하고 시작(0)으로 돌아가기위한 추가적인 경로비용합의 최솟값
// 포인트는 "추가적인" 비용이라는 점임. 즉 이미 방문한 노드들에서 사용한 비용을 제외하고, 남은 미방문 노드를 방문하기 위한 비용만 구한다는 말임.
{
    if (visited == ALLONE)
    {
        if (W[lastNode][0]) return W[lastNode][0]; // 기저사례: 모든 노드를 방문했을 경우 lastNode에서 다시 시작노드로 돌아가야 하므로 W[lastNode][0]을 반환.
        else return INT_MAX; // 불가능한 경우 이 경우의 수를 제거하기 위해 최댓값으로 설정해버린다.
    }
    
    int& funcRet = dp[visited][lastNode];
    if (funcRet) return funcRet;
    funcRet = INT_MAX;
    for(int i=0;i<N;i++)
    {
        if (i!=lastNode && !getIdx(visited,i) && W[lastNode][i]) // 자기자신X, 방문X, 경로존재
        // 자기자신으로 향하는 경로는 어차피 주어지지 않으므로 굳이 필요없는 조건임.
        {
            int nVisited = setIdxOne(visited, i);
            funcRet = min(dfs(nVisited, i) + W[lastNode][i], funcRet);
        }
    }
    return funcRet;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(dp, 0, sizeof(dp));
    memset(W, 0, sizeof(W));
    
    cin >> N;
    ALLONE = (1<<N)-1;
    for(int i=0;i<N;i++) // 1~N 대신 0~N-1 사용 (2^16으로 표현가능)
    {
        for(int j=0;j<N;j++)
        {
            cin >> W[i][j];
        } 
    }
    // 어차피 모든 도시에 방문하므로 무조건 0번 도시에서 시작한다고 가정.
    // visited가 0이 아닌 1임에 주의. 나중에 다시 0번노드로 돌아오는 건 기저사례에서 처리해줌.
    cout << dfs(1,0) << '\n';
    return 0;
}
