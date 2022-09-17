#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> p;
int N, L, P;
p station[10001]; 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N;
    for (int i=0;i<N;i++)
    {
        cin >> station[i].first >> station[i].second;
    }
    cin >> L >> P;
    sort(station, station+N);
    
    priority_queue<int> pq;
    int maxStation = 0, maxDist = P, ans = 0;
    
    /* 중요!
    1) maxDist는 누적된다
    2) 주유소 방문 순서는 거리순이 아니다!
    즉 pq에서 pop하는 순서는 뒤에 먼저 갔다가 앞의 주유소를 갔다가 하는 식이 될 수 있다.
    결국 중요한건 maxDist가 L을 넘어야 한다는 것이기에 넘을 수 있는 최소한의 주유소 방문을 구하려면 
    현재 가능한 범위에서 가장 많은 연료를 주는 주유소에 방문하면 된다.
    그래야 그렇게 얻은 연료로 탐색 범위를 최대한으로 넓혀 이동가능한 모든 경우의 수를 전부 탐색할 수 있다. 
    
    초기 연료가 10, 마을 거리가 20,
    주유소 거리: 2 6 16
    주유소 연료: 4 5 8
    인 경우를 생각해보자.
    
    처음 거리 10 내인 주유소 중 가장 많은 연료를 주는 6에 방문, 최대 탐색거리는 15가 된다. 
    (연료는 10+5 - 이동한 6을 뺀 9이지만, 이는 중요치 않다. 
    왜? 6번을 지금 제일 먼저 방문했다고해서 
    우리가 구하려는 최적의 경로에서도 6번을 가장 먼저 방문하는 것이 아니기 때문이다.)
    
    그 다음 거리 15 내인 주유소 중 가장 많은 연료를 주는 2에 방문, 최대 탐색 거리는 19가 된다.
    이때 6이 더 뒤에 있음에도 우리는 6->2 순으로 방문함을 알 수 있는데, 이는 실제 최적의 경로에서 2->6을 방문하는 것과 동일하다.
    이런 의문을 가질 수 있다: 처음에 2 먼저방문한 이후 6으로 가는 연료가 부족할 수 있지 않은가?
    -> 그러나 애초에 초기 연료로 방문 가능한 범위 내에 6이 들어있었기에 6을 먼저 방문한 것이기에, 그러한 경우가 발생하지 않는다고 확신할 수 있다.
    
    이 과정을 반복해 16에도 방문, 마지막으로 마을에 방문해주면 된다.
    */
    while (maxDist < L) // 넘는 순간 마을에 도착이 가능해짐
    {
        while (maxStation < N && station[maxStation].first <= maxDist)
        {
            pq.push(station[maxStation].second);
            maxStation++;
        }
        
        if (pq.empty())
        {
            ans = -1;
            break;
        }
        maxDist += pq.top();
        pq.pop();
        ans++;
    }
    cout << ans << '\n';
    return 0;
}
