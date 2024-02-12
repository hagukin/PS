#include <iostream>
#include <deque>
using namespace std;
typedef pair<int,int> pp;
int N, L;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> L;
    deque<pp> q;
    int x;
    for (int i=0; i<N; ++i) {
        cin >> x;
        
        while(!q.empty() && i - q.front().first + 1 > L) {
            q.pop_front();
        }
        while (!q.empty() && q.back().second > x) {
            q.pop_back();
        }
        q.push_back({i, x});
        cout << q.front().second << ' ';
    }
    return 0;
}
