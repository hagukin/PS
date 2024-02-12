#include <iostream>
#include <limits.h>
#include <deque>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pp;
constexpr ll INF = LONG_LONG_MAX;

int T;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> T;
    for (int tc=0; tc<T; ++tc)
    {
        int N, X;
        cin >> N >> X;
        
        ll a;
        ll sum = 0;
        ll result = INF;
        
        deque<pp> dq;
        dq.push_back({0,0});
        
        for (int i=1; i<=N; ++i)
        {
            cin >> a;
            sum += a;
            
            while (!dq.empty() && sum - dq.front().second >= X)
            {
                result = min(result, i - dq.front().first);
                dq.pop_front();
            }
            
            while (!dq.empty() && sum <= dq.back().second)
            {
                dq.pop_back();
            }
            dq.push_back({i, sum});
        }
        cout << ((result != INF) ? result : -1) << '\n';
    }
    return 0;
}
