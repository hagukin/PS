#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;
int N, M;
ll ret = 0;
vector<pair<ll,ll >> decr; // 감소방향쪽으로 이동하는 사람들
vector<pair<ll,ll >> nDecr;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    ll A, B;
    for (int i=0;i<N;++i)
    {
        cin >> A >> B;
        if (A>B) decr.push_back({A,B});
    }
    sort(decr.begin(), decr.end(), greater<>());
    
    pair<ll,ll> prev = make_pair<ll,ll>(-1LL,-1LL);
    for (int i=0;i<decr.size();++i)
    {
        pair<ll,ll>& curr = decr[i];
        
        // 첫 엘리먼트 발견 시
        if (prev.first<0)
        {
            prev=curr;
            continue;
        }
        // 병합 판정
        if (curr.first >= prev.second) 
        {
            if (curr.second < prev.second) prev.second = curr.second;
        }
        else
        {
            nDecr.push_back(prev);
            prev = curr;
        }
    }
    nDecr.push_back(prev);
    
    ret += M;
    for (const auto& x : nDecr)
    {
        ret += (x.first - x.second) * 2;
    }
    cout << ret << '\n';
    return 0;
}
