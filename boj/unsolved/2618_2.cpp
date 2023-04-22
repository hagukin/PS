// 힌트없이 풀이헀을 때 얻은 풀이로, 이것보다 우아한 풀이가 있지만 이 방법도 일단 풀린다
// 깔끔한 풀이는 올려둔게 있으니 이 레포에서 찾아볼것
/*
1~1000개의 사건
abaabbbabbababab ... 
2^1000가지의 모든 경우의 수

point m to n으로 가는 건 장애물이 없기 떄문에 O(1)에 택시거리로 구할 수 있음
그렇다고 한들 2^1000은 너무 큼

dp[i][j][k] = 
k번 사건이 해결되는 시점에 a는 i번 사건 위치에, b는 j번 사건 위치에 있다고 했을 때의 최소 거리의 합
(
k == i or k == j이다. 
i != j이지만 VALUE(i) == VALUE(j)일 수 있다
)


// 매 시행은 결국 두 경우 중 하나로 나뉜다
// 이전에 움직이는 애가 또 움직인 경우
// 이전에 안움직인 애가 움직인 경우

for (int ki = 0; ki < k; ++ki)
{
    dp[k+1][ki][k+1] = 
    min
    (
        dp[k+1][ki][k+1],
        // k에서 k+1로 이동한 경우
        min
        (
            dp[k][ki][k],
            dp[ki][k][k]
        ) + dist(k,k+1),
    )
    
    
    dp[k][k+1][k+1] = 
    // ki에서 k+1로 이동한 경우
    min
    (
        dp[k][ki][k],
        dp[ki][k][k]
    ) + dist(ki,k+1),
}



현재 3번 사건이라 하면

0,2 -> 3
1,2 -> 3
2,0 -> 3
2,1 -> 3

이후 가진 정보는
0,3 (0,2)
1,3 (1,2)
2,3 (2,0 / 2,1)
3,0 (2,0)
3,1 (2,1)
3,2 (0,2 / 1,2)

순서대로 하면
쭉쭉 구해나가면서 전부 구할 수 있다

*/
#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = 987654321;

int N, W;
pair<int,int> events[1001]; // 1번 인덱스부터 시작 (0번은 초기 위치)
int dp[1001][1001] = {0,}; // 경찰차가 i,j번에 위치해 있을 때 max(i,j)+1번 위치로 가기 위해 필요한 거리 + 그동한 이동한 거리들의 합

// 시간이 없어서 설명을 일단 모호하게나마 작성
// TODO
pair<int,int> btDp[1001][1001]; // (i,j)에 대해 최솟값을 구할 수 있는 이전번 (?,?)를 기록
bool isADp[1001][1001]; // (i,j)에 대해 마지막 이동이 A인지를 기록


inline int getDist(int m, int n, bool isA)
{
    int sx = events[m].first;
    int sy = events[m].second;
    if (m == 0)
    {
        if (isA) {sx = 1; sy = 1;}
        else {sx = N; sy = N;}
    }
    return abs(sx - events[n].first) + abs(sy - events[n].second);
}

void memoMin(int i, int j, int cmpVal, int pi, int pj)
{
    // dp[i][j]를 cmpVal과 비교하고, 만약 dp[i][j]가 더 작다면 cmpVal을 업데이트 해주면서 동시에 isADp와 btDp를 업데이트한다
    // pi,pj는 이전번 i,j를 의미한다
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> W;
    for (int i=1;i<=W;++i)
    {
        cin >> events[i].first >> events[i].second;
    }
    
    // init (0,x 또는 x,0 칸들은 0으로 설정해줘야함)
    for (int i=0;i<1001;++i)
        for (int j=0;j<1001;++j)
            dp[i][j] = INF;
    dp[0][0] = 0;
    dp[1][0] = getDist(0,1,true);
    dp[0][1] = getDist(0,1,false);
    
    
    
    // TODO: W==1인 경우는 수동으로 처리해주어야 한다
    
    
    
    for (int ev=2;ev<=W;++ev)
    {
        int ans = INF;
        for (int ki=0;ki<ev-1;++ki)
        {
            dp[ev][ev-1] = min(dp[ev][ev-1], dp[ki][ev-1] + getDist(ki, ev, true)); // 0,2  /  1,2  ->  3,2
            dp[ev-1][ev] = min(dp[ev-1][ev], dp[ev-1][ki] + getDist(ki, ev, false)); // 2,0  /  2,1  ->  2,3
            
            dp[ev][ki] = min(dp[ev][ki], dp[ev-1][ki] + getDist(ev-1, ev, true));
            dp[ki][ev] = min(dp[ki][ev], dp[ki][ev-1] + getDist(ev-1, ev, false));
            
            // TODO: memoMin함수로 싹 교체해줄것
            ans = min(dp[ev][ev-1], ans);
            ans = min(dp[ev-1][ev], ans);
            ans = min(dp[ev][ki], ans);
            ans = min(dp[ki][ev], ans);
        }
        if (ev==W) cout << ans << '\n';
    }
    return 0;
}
