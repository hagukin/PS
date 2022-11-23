#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pp;

bool cmpByDeadline(const pp& a, const pp& b)
{
    return a.first < b.first; // 벡터 맨 뒤가 가장 데드라인 크게 정렬
}

int N, ret = 0;
priority_queue<int> pq;
vector<pp> v;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int A, B;
    for (int i=0;i<N;++i)
    {
        cin >> A >> B;
        pp tmp;
        tmp.first = A; tmp.second = B;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end(), cmpByDeadline);
    
    int ramen, dead;
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
