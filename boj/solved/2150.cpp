// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <algorithm>
// using namespace std;

// constexpr int MAXN = 10002;
// constexpr int INF = 987654321;
// constexpr int UNVISITED = -1;

// int V, E;

// bool edges[MAXN][MAXN] = {false,};

// vector<int> st; // real id 저장
// bool isInStack[MAXN] = {false,}; // isInStack[real id] : 스택에 현재 들어있는지 확인
// int ids[MAXN] = {0, }; // ids[input id] : 방문여부 확인 및 id 맵핑
// int lows[MAXN] = {0, }; // lows[real id] : low값 확인
// int idMap[MAXN] = {0, }; // real id를 input id로
// int sccCnt = 0; // 정확히는 cnt+1 개 있음
// int cId = 0;

// void dfs(int curr) // curr은 input id임에 유의
// {
//     ids[curr] = ++cId; // 1번부터 번호매김
//     int& nId = ids[curr];
//     lows[nId] = nId;
    
//     st.push_back(nId);
//     isInStack[nId] = true;
    
//     for (int i=1;i<=V;++i) // 엣지탐색
//     {
//         if (edges[curr][i])
//         {
//             if (ids[i] == UNVISITED) dfs(i);
//             // 이미 방문했더라도 값을 업데이트해주어야 할 수도 있음 (e.g. 0-1-2-0순 dfs)
//             if (isInStack[ids[i]])
//                 lows[nId] = min(lows[nId], lows[ids[i]]);
//         }
//     }
    
//     if (nId == lows[nId])
//     {
//         while (true)
//         {
//             int cn = st.back();
//             isInStack[cn] = false;
//             st.pop_back();
//             if (cn == nId) break;
//         }
//         sccCnt++;
//     }
//     return;
// }

// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);
    
//     cin >> V >> E;
//     int A, B;
    
//     for (int i=0;i<E;++i)
//     {
//         cin >> A >> B;
//         edges[A][B] = true;
//     }
//     memset(ids, UNVISITED, sizeof(ids));
    
//     // SCC
//     for (int i=1;i<=V;++i)
//     {
//         if (ids[i] == UNVISITED) dfs(i);
//     }
    
//     cout << sccCnt << '\n';
    
//     for (int i=1;i<=V;++i) idMap[ids[i]] = i;
    
//     vector<int> retV[MAXN];
//     for (int i=1;i<=V;++i)
//     {
//         retV[lows[i]].push_back(idMap[i]);
//     }
    
//     // {{}, {}, ... {1,5,4}, ... {7,3,2}, ... {6} ... {}, {}}
//     // 를 내부 정렬한 후 첫자리 오름차 순으로 정렬해야 함.
    
//     // 내부 정렬
//     for (int i=1;i<=V;++i)
//     {
//         if (!retV[i].empty())
//         {
//             vector<int>& tmp = retV[i];
//             sort(tmp.begin(), tmp.end());
//         }
//     }
    
//     // 첫자리 기준 정렬
//     vector<int>* retV2[MAXN];
//     for (int i=1;i<=V;++i)
//     {
//         if (!retV[i].empty())
//         {
//             retV2[retV[i][0]] = &retV[i];
//         }
//     }
    
//     // 출력
//     for (int i=1;i<=V;++i)
//     {
//         if (retV2[i]!=nullptr)
//         {
//             for (int x : *retV2[i]) cout << x << " ";
//             cout << -1 << '\n';
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

constexpr int MAXN = 10002;


bool finished[MAXN];
vector<int> graph[MAXN];
vector<vector<int>> SCC;
stack<int> s;

int cId, d[MAXN];
int v, e;

int dfs(int x)
{
    d[x] = ++cId;
    
    s.push(x);
    int parent = d[x];
    
    for(int i=0; i <graph[x].size();++i)
    {
        int y = graph[x][i];
        if(d[y] == 0) parent = min(parent, dfs(y));
        else if(!finished[y]) parent = min(parent, d[y]);
    }
    
    if(parent == d[x])
    {
        vector<int> tmp;
        while(true)
        {
            int t = s.top();
            s.pop();
            tmp.push_back(t);
            finished[t] =true;
            if(t == x) break;
        }
        sort(tmp.begin(), tmp.end());
        SCC.push_back(tmp);
    }
    return parent;
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> v >> e;
    
    int a, b;
    for(int i=0;i<e;++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
    }
    
    for(int i=1;i<=v;++i)
    {
        if(d[i]==0) dfs(i);
    }
    
    cout<< SCC.size() << endl;
    
    sort(SCC.begin(), SCC.end());
    for(int i=0;i<SCC.size();++i) 
    {
        for(int j=0;j<SCC[i].size();++j)
        {
            cout << SCC[i][j] << ' ';
        }
        cout << -1 << '\n';
    }
}
