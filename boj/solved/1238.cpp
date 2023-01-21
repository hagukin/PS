#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, X;
vector<vector<int >> originRoad;
vector<vector<int >> reversedRoad;
int toX[1001]; // 노드 i에서 X까지 가는 최단거리
int fromX[1001]; // X에서 노드 i까지 오는 최단거리
constexpr int INF = 987654321;

vector<int> djikstra1(int startN, const vector<vector<int >>& road)
{
    // road[1001][1001] 가정
    
    vector<int> dist;
    for (int i=0;i<1001;++i)
        dist.push_back(INF);

    bool visited[1001] = {false,};
    int curr = startN;
    dist[startN] = 0;
    
    while (true)
    {
        visited[curr] = true;
        for (int i=1;i<=N;++i)
        {
            if (road[curr][i])
            {
                dist[i] = min(dist[curr] + road[curr][i], dist[i]);
            }
        }
        
        int minDist = INF;
        int next = -1;
        for (int i=1;i<=N;++i)
        {
            if (!visited[i] && dist[i] < minDist) 
            {
                minDist = dist[i];
                next = i;
            }
        }
        if (next == -1) break; // 완료
        else {curr = next; continue;}
    }
    return dist;
}

struct S
{
    int node, value=INF;
};

struct cmp
{
    bool operator()(const S& s1, const S& s2)
    {
        return s1.value < s2.value;
    }
};


// vector<int> djikstra2(int startN, const vector<vector<int >>& road)
// {
//     bool visited[1001] = {false,};
    
//     vector<int> dist(INF, 1001);
//     dist[startN] = 0;
    
//     priority_queue<S, vector<S>, cmp> pq;
//     S curr = {startN, 0};
//     pq.push(curr);
    
//     while(!pq.empty())
//     {
//         curr = pq.top();
//         pq.pop();
//         visited[curr] = true;
        
//         for (int i=0;i<1001;++i)
//         {
//             if (road[curr.node][i] && !visited[i])
//             {
//                 dist[i] = min(dist[curr.node] + road[curr.node][i], dist[i]);
//             }
//         }
//     }
//     return dist;
// }

int main()
{
    cin >> N >> M >> X;
    for (int i=0;i<1001;++i)
    {
        originRoad.push_back(vector<int>());
        reversedRoad.push_back(vector<int>());
        for (int j=0;j<1001;++j)
        {
            originRoad[i].push_back(INF);
            reversedRoad[i].push_back(INF);
        }
    }

    int a, b;
    for (int i=0;i<M;++i)
    {
        cin >> a >> b;
        cin >> originRoad[a][b];
        reversedRoad[b][a] = originRoad[a][b];
    }
    
    vector<int> v = djikstra1(X, originRoad);
    vector<int> v2 = djikstra1(X, reversedRoad);
    
    int ret = -1;
    for (int i=1;i<=N;++i)
    {
        ret = max(v[i]+v2[i], ret);
    }
    cout << ret << '\n';
    return 0;
}
