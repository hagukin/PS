#include <queue>
#include <vector>
#include <iostream>
#include <memory.h>

using namespace std;

struct Path
{
    int start, goal, dist;
};

struct cmp
{
    bool operator()(const Path& p1, const Path& p2)
    {
        if (p1.dist == p2.dist) return p1.goal < p2.goal;
        return p1.dist > p2.dist;
    }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    
    /*
    결과는 무조건 대칭이 나옴 (예시에서 비대칭이긴한데 이건 대칭으로도 정답구하기가 가능)
    고로 우리는 intensity가 최소인 출발-정상까지의 경로만 구하면 됨
    
    <시간초과: Brute force 50000^4>
    for 모든 정상
    for 모든 출입구
    DFS로 출입구-정상 찾고 intensity 값 구하기
    
    <DP로 최적화>
    priority_queue (heap) 사용
    for 모든 출발지
    해당 출발지의 등산로 정보 추가, 거리짧은 순으로 정렬, 거리가 같으면 번호 작은순으로 정렬
    이때 등산로는 양방향인데, 어느 방향으로 나아갈지 어떻게 아느냐?
    -> 방문한 노드들은 visited 처리해주고, visited에서 nonvisited로 이동하는 경로로 이동해 다음 노드를 정하면됨.
    
    가장 짧은 길부터 선택, 이동후 이어진 노드를 추가 (=즉 이어진 노드의 등산로들도 다 힙에 추가)
    int intensities[n+1]
    intensities[i]번에 해당 추가된 노드까지 가는 intensity를 갱신(max(현재노드, 도착노드))
    */
    
    /*
    구현:
    1) 노드i가 가진 등산로 정보들을 가져올 수 있어야 함.
    2) 노드i ~ j의 dist를 구할 수 있어야 함.
    
    -> 입력된 paths를 변형해서 다음과 같은 형태로 만들기
    newPaths[노드번호][<=n]
    newPaths[i]에는 i의 등산로 정보들이 들어있음.
    ex. newPaths[1] = {{1,2,4},{1,5,12}, {1,8,2}} 이때 start노드도 기록 필요함.
    1~2는 4, 1~5는 12 이런 식
    
    이렇게 하면 모든 출발지에 대해 각 출발지의 등산로 정보를 추가하는데 O(V+E)로 할 수 있음.
    
    3) visited 배열 만들기
    
    4) 어떤 노드가 gate인지, summit인지를 O(1)에 알 수 있어야 함.
    newPaths;
    bool isGate[50001]; 
    bool isSummit[50001];
    vector<int> answerCandidates[50001]; // 각 s별 ret값
    
    // 등산로 입력
    for 출발노드 s
    {
        bool visited[50001];
        int intensity[50001];
        priority_queue pq;
        vector<int> ret; // 이 s의 경우의 ret값
        
        visited[s] = true;
        for s의 등산로 p:
            if (visited[p.goal]) continue;
            pq.push(p)
        
        while(!pq.empty())
        {
            currP = pq.pop();
            visited[currP.goal] = true;
            intensity[currP.goal] = max(currP.dist, intensity[currP.start]);
            if currP.goal이 산봉우리면:
                if ret[1] > intensity[currP.goal]이면:
                    ret 새로 덮어쓰기

            for currP.goal의 등산로 pp:
                if (visited[pp.goal]) continue;
                pq.push(pp)
        }
        
        // 이 시점에는 이미 ret 구해짐
        answerCandidates[s] = ret;
    }
    */
    
    // 1
    vector<vector<Path>> newPaths;
    for (int i=0;i<=n;i++) 
    {
        vector<Path> nv;
        newPaths.push_back(nv);
    }
    for (int i=0;i<paths.size();i++)
    {
        Path np = {paths[i][0], paths[i][1], paths[i][2]};
        newPaths[paths[i][0]].push_back(np);
        np = {paths[i][1], paths[i][0], paths[i][2]};
        newPaths[paths[i][1]].push_back(np);
    }
    
    // 2
    bool isSummit[50001];
    for (int i=0;i<summits.size();i++)
    {
        isSummit[summits[i]] = true;
    }
    
    // 3
    vector<int> answerCandidates[50001];
    
    // solve
    for (int i=0;i<gates.size();i++)
    {
        bool visited[50001] = {0,};
        int intensity[50001] = {0,};
        priority_queue<Path, vector<Path>, cmp> pq;
        vector<int> cRet;
        cRet.push_back(987654321);
        cRet.push_back(987654321); // {INF, INF}
        
        const int& s = gates[i];
        visited[s] = true;
        for (int j=0;j<newPaths[s].size();j++)
        {
            Path cPath = newPaths[s][j];
            if (visited[cPath.goal]) continue;
            pq.push(cPath);
        }
        
        // main logic
        while (!pq.empty())
        {
            Path currP = pq.top();
            pq.pop();
            if (visited[currP.goal]) continue;
            cout << currP.start << currP.goal << currP.dist << endl;
            visited[currP.goal] = true;
            
            intensity[currP.goal] = max(currP.dist, intensity[currP.start]);

            for (int j=0;j<newPaths[currP.goal].size();j++)
            {
                Path cPath = newPaths[currP.goal][j];
                if (visited[cPath.goal]) continue; // 없애도되나?
                pq.push(cPath);
            }
            
            if (isSummit[currP.goal])
            {
                if (cRet[1] > intensity[currP.goal] && currP.start != s)
                {
                    cRet[0] = currP.goal;
                    cRet[1] = intensity[currP.goal];
                }
            }
        }
        answerCandidates[s] = cRet;
        
        
        cout << s << " s " << endl;
        for (int i=1;i<7;i++)
        {
            cout << intensity[i] << " ";
        }
        cout << endl;
    }
    
    return answer;
}
