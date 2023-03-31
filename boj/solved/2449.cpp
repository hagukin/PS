/*
처음 시도했던 방법은 구간을 분할하는 것까진 동일하나 각 구간을 20가지의 색 중 하나로 정해 계산하는 방법이었다. (dp[201][201][20])
이 풀이로 해결한 사람이 있는 걸 보아 작동은 하지만 구현 상의 문제인지 테케 게시판 반례 다 맞았지만 어디선가 막혔다

두번째 풀이는 이를 개선한 방법으로, 첫번째 풀이에서의 발상과 더불어 몇 가지 사실을 캐치해야 한다.
코드 주석 참고

입력값을 전처리하는 simplify() 함수도 작성했는데, 애초에 입력값이 커봐야 200정도라 큰 의미는 없을 듯 하다.
simplify()를 없애려면 그냥 vector<int> lights를 지워버리고
origin을 이름을 lights로 바꿔주면 된다
*/

#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;
constexpr int INF = 987654321;

int N, K;
vector<int> lights;
int origin[201];
int dp[201][201];

void simplify()
{
    // 이 함수가 없어도 풀린다
    // 아주 약간의 성능 개선을 위해 추가
    lights.push_back(origin[0]);
    for (int i=1;i<N;++i)
    {
        if (origin[i] == origin[i-1]) continue;
        lights.push_back(origin[i]);
    }
    N = lights.size();
}

int solve(int l, int r)
{
    // [l,r]을 l 또는 r로 통일시키는데 필요한 횟수
    
    // 풀이가 두 가지 있는데, 그 중 더 우아한 풀이법이다
    // 이 풀이를 적용하기 위해 다음 두 가지 사실들을 인지해야 한다.
    // 1: l로 통일시키거나 r로 통일시키거나 그 횟수는 반드시 동일하다
    // 2: l또는 r로 통일시키는 게 횟수를 최소한으로 줄이는 경우이다
    
    // 이 구현법에서는 한 덩어리를 l로 통일시킨다. 
    // 즉 가장 좌측 전구 색으로 통일한다
    // 그러나 1번 사실에서 알 수 있듯이 좌로 하던 우로 하던 관계없다
    if (l == r) return 0; // 기저 1
    if (r-l == 1) return lights[l] != lights[r]; // 기저 2
    if (dp[l][r] != -1) return dp[l][r];
    int ret = INF;
    for (int i=l;i<r;++i)
    {
        ret = min(ret, solve(l,i) + solve(i+1,r) + (lights[i] != lights[r] ? 1 : 0));
    }
    return dp[l][r] = ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> K;
    memset(dp, -1, sizeof(dp));
    for (int i=0;i<N;++i)
    {
        cin >> origin[i];
    }
    simplify();
    cout << solve(0,N-1) << '\n';
    return 0;
}
