#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN = 1001;
constexpr int MAXD = 987654321;
constexpr int STARTN = 1;
int N, M, K;
int nw[1001][1001];
int cntRet = -1;

// djikstra
int dist[1001]; // 1~i 거리
bool visited[1001];
int route[1001]; // route[i] = start부터 i까지의 최단경로중 i 바로 이전의 노드의 번호
bool restore[1001][1001]; // i-j 회선을 복구해야 하는지 여부.

int getMinDist()
{
    int minDist = MAXD;
    int ret = -1;
    for (int j=1;j<=N;j++)
    {
        if (!visited[j] && dist[j] < minDist)
        {
            minDist = dist[j];
            ret = j;
        }
    }
    return ret;
}

void djikstra(int start)
{
    for (int i=1;i<=N;i++)
    {
        dist[i] = MAXD;
        if (!nw[start][i]) continue;
        else 
        {
            dist[i] = min(nw[start][i], dist[i]);
            route[i] = start;
        }
    }
    dist[start] = 0;
    route[start] = start;
    visited[start] = true;
    
    for (int i=1;i<=N-1;i++) // 남은건 N-1개 노드들
    {
        int curr = getMinDist();
        visited[curr] = true;
        for (int j=1;j<=N;j++)
        {
            if (!visited[j] && nw[curr][j] && dist[j] > dist[curr] + nw[curr][j])
            {
                dist[j] = dist[curr] + nw[curr][j];
                route[j] = curr;
            }
        }
    }
    return;
}

void getRoute(int goal, vector<int>& r)
{
    if (!route[goal]) return; // 경로 없음
    if (route[goal] == STARTN) {r.push_back(STARTN); return;}
    else
    {
        r.push_back(route[goal]);
        getRoute(route[goal], r);
        return;
    }
}

int main()
{
    // 입력
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> M;
    int A, B, C;
    for (int i=0;i<M;i++)
    {
        cin >> A >> B >> C;
        nw[A][B] = C;
        nw[B][A] = C;
    }
    
    // 회선 찾기
    djikstra(STARTN);
    
    // 회선 추출
    for (int i=1;i<=N;i++)
    {
        vector<int> tmp;
        tmp.push_back(i);
        getRoute(i, tmp);
        for (int j=tmp.size()-1;j>0;j--)
        {
            if (!restore[tmp[j-1]][tmp[j]]) ++cntRet; // 새로 추가된 경로면 cnt++
            restore[tmp[j-1]][tmp[j]] = true;
            restore[tmp[j]][tmp[j-1]] = true;
        }
    }
    
    // 출력
    cout << cntRet << '\n';
    for (int i=1;i<=N;i++)
    {
        for (int j=i+1;j<=N;j++)
        {
            if (restore[i][j]) cout << i << " " << j << '\n';
        }
    }
    return 0;
}
