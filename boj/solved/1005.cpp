#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
constexpr int MAXN = 1001;
int T;
int bTime[MAXN]; // 딱 그 건물만 짓는데 드는 시간
int bbTime[MAXN]; // 그 건물을 비롯한 그 건물의 하위건물까지 포함하여 드는 시간
vector<int> bo[MAXN]; // bo[5]에 3이 들어있다면 5를 짓기전 3을 지어야 한다는 의미.

int dfs(int n)
{
    if (bbTime[n] != -1) return bbTime[n];
    int cTime = 0;
    for (int i : bo[n])
    {
        cTime = max(cTime, dfs(i));
    }
    cTime += bTime[n];
    bbTime[n] = cTime;
    return cTime;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> T;
    for (int t=0;t<T;t++)
    {
        // 데이터 초기화
        int N, K, W, X, Y;
        memset(bTime, -1, sizeof(bTime));
        memset(bbTime, -1, sizeof(bbTime));
        for (int vi=0;vi<MAXN;vi++)
        {
            bo[vi].clear(); // 벡터 초기화
        }
        
        // 인풋
        cin >> N >> K;
        for (int i=1;i<=N;i++)
        {
            cin >> bTime[i];
        }
        for (int i=0;i<K;i++)
        {
            cin >> X >> Y;
            bo[Y].push_back(X);
        }
        cin >> W;
        
        // solve
        cout << dfs(W) << '\n';
    }
    return 0;
}
