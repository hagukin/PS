#include <iostream>
#include <vector>
using namespace std;
int N, M, L, K, ret=0;
vector<pair<int,int> > v(101);

void bounce(const pair<int,int>& c)
{
    int tmp = 0;
    for (int s=0;s<K;s++)
    {
        if (v[s].first < c.first || v[s].second < c.second || v[s].first > c.first + L || v[s].second > c.second + L) continue;
        tmp++;
    }
    ret = max(tmp, ret);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M >> L >> K;
    int x, y;
    for (int i=0;i<K;++i)
    {
        cin >> x >> y;
        pair<int,int> c = make_pair(x, y);
        v[i] = c;
    }
    
    // solve
    pair<int,int> topLeft;
    for (int i=0;i<K;++i)
    {
        for (int j=0;j<K;++j)
        {
            topLeft.first = v[i].first;
            topLeft.second = v[j].second;
            bounce(topLeft);
        }
    }
    
    cout << K - ret << '\n';
    return 0;
}
