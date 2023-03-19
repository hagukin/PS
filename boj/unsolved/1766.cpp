#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;

vector<int> paths[32001];
int inPath[32001] = {0,};
bool visited[32001] = {false,};
vector<int> retV;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    
    int A, B;
    for (int i=0;i<M;++i)
    {
        cin >> A >> B;
        inPath[B]++;
        paths[A].push_back(B);
    }
    
    priority_queue<int, vector<int>, greater<int>> pq;
    // 시작점
    for (int i=1;i<=N;++i)
    {
        if (inPath[i] == 0 && !visited[i])
        {
            visited[i] = true;
            pq.push(i);
        }
    }
    
    while (!pq.empty())
    {
        int c = pq.top();
        pq.pop();
        cout << c << ' ';
        retV.push_back(c);
        for (int adj : paths[c])
        {
            inPath[adj]--;
            if (inPath[adj] == 0) pq.push(adj); 
            /* 
            주의할 부분: inPath가 0인 노드를 큐에 추가해주는 과정을 
            따로 빼서 별도의 루프에서 0인 애들을 찾는 과정으로 구현했다가 
            시간초과 발생함. N만큼 루프를 매번 돌아야 하기 때문에 O(V^2)이 소요되기 때문.
            하지만 이렇게 adjList 내에서 처리하면 O(V+E) (priority_queue때문에 정확히는 O(V+ElogE)가 소요됨.
            */
        }
    }
    return 0;
}
