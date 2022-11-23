// 내가 쓴 질문글: https://www.acmicpc.net/board/view/104433
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pp;

bool cmpByDeadline(const pp& a, const pp& b)
{
    return a.first < b.first;
}

ll N; ll ret = 0;
priority_queue<ll> pq;
vector<pp> v;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    ll A; ll B;
    for (int i=0;i<N;++i)
    {
        cin >> A >> B;
        pp tmp;
        tmp.first = A; tmp.second = B;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end(), cmpByDeadline);
    
    ll dead; ll ramen;
    for (int i=N;i>=1;--i)
    {
        dead = v.back().first;
        ramen = v.back().second;
        if (dead >= i)
        {
            while(dead >= i)
            {
                pq.push(ramen);
                v.pop_back();
                dead = v.back().first;
                ramen = v.back().second;
            }
        }
        if (!pq.empty())
        {
            ret += pq.top();
            pq.pop();
        }
    }
    cout << ret << '\n';
    return 0;
}
