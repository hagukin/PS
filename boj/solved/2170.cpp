#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
pair<int,int> lines[1000002];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int x, y;
    pair<int,int> tmp;
    for (int i=0;i<N;++i)
    {
        cin >> x >> y;
        tmp = make_pair(x,y);
        lines[i] = tmp;
    }
    
    sort(lines, lines+N);
    
    int ret = 0;
    int l=lines[0].first, r=lines[0].second;
    for (int i=1;i<N;++i)
    {
        if (lines[i].second <= r) continue; // i번 선이 이전에 merge된 선 내에 포함되는 경우
        if (lines[i-1].second >= lines[i].first)
            r = lines[i].second;
        else
        {
            ret += (r-l);
            l = lines[i].first;
            r = lines[i].second;
        }
    }
    ret += (r-l);
    cout << ret << '\n';
    return 0;
}
