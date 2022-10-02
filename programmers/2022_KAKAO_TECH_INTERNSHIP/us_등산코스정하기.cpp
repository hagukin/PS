#include <string>
#include <queue>
#include <vector>

using namespace std;

int intensity[50001];
char nodeInfo[50001] = {0,};
vector<pair<int,int>> adj[50001]; // 노드i의 인접노드와 그 거리를 저장

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    constexpr int INF = 987654321;
    
    for (int i=1;i<=n;++i) 
        intensity[i] = INF;
    for (auto& g : gates)
        nodeInfo[g] = 'G';
    for (auto& s : summits)
        nodeInfo[s] = 'S';
    
    // 필요없는 등산로 제거
    for (auto& p : paths)
    {
        // 시작이 게이트 또는 도착이 산정상 (이 부분을 고려 안해서 틀림)
        if (nodeInfo[p[0]] == 'G' || nodeInfo[p[1]] == 'S')
            adj[p[0]].push_back(make_pair(p[1],p[2]));
        // 도착이 게이트 또는 시작이 산정상
        else if (nodeInfo[p[0]] == 'S' || nodeInfo[p[1]] == 'G')
            adj[p[1]].push_back(make_pair(p[0],p[2]));
        else // 그 왜의 경우는 양방향 모두 adj에 추가해준다
            adj[p[0]].push_back(make_pair(p[1],p[2])), adj[p[1]].push_back(make_pair(p[0],p[2]));
    }
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // pair는 거리, 도착정점 순
    for (auto& g : gates)
    {
        pq.push(make_pair(0, g)); // 중요: 모든 시작지점을 그냥 처음부터 pq에 다 넣어버린다
        // 처음 풀 때 이렇게 안하고 각 gates 별로 개별적으로 pq를 만들어 탐색하다 보니까 시간초과가 났음 - worst case O(V*V)
        // 이렇게 시작지점별 구분 없이 그냥 모든 케이스를 한번에 탐색하면 훨씬 빠름 - O(E) (200000)
        intensity[g] = 0;
    }
    while (!pq.empty())
    {
        pair<int,int> cRoad = pq.top();
        pq.pop();
        int dist = cRoad.first;
        int cNode = cRoad.second;
        if (intensity[cNode] < dist) continue; // 중요: 다른 시작지점에서 출발한 경로중 이 노드에 더 낮은 intensity로 방문하는 경우가 있을 경우 현재의 시작지점에서는 해당 노드를 더 탐색할 필요가 없다.
        
        // 인접 노드들 방문
        for (auto& nRoad : adj[cNode])
        {
            int nextNode = nRoad.first;
            int nodeDist = nRoad.second;
            if (intensity[nextNode] > max(nodeDist, dist))
            {
                intensity[nextNode] = max(nodeDist, dist);
                pq.push(make_pair(intensity[nextNode], nextNode));
            }
        }
    }
    
    vector<int> answer{INF, INF};
    for (auto& s : summits)
    {
        if (intensity[s] < answer[1])
            answer[0] = s, answer[1] = intensity[s];
        else if (intensity[s] == answer[1])
            answer[0] = min(s, answer[0]);
    }
    
    return answer;
}
