#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int MAXN = 10002;
constexpr int INF = 987654321;
constexpr int UNVISITED = -1;

int V, E;

bool edges[MAXN][MAXN] = {false,};

vector<int> st; // real id 저장
bool isInStack[MAXN] = {false,}; // isInStack[real id] : 스택에 현재 들어있는지 확인
int ids[MAXN] = {0, }; // ids[input id] : 방문여부 확인 및 id 맵핑
int lows[MAXN] = {0, }; // lows[real id] : low값 확인
int idMap[MAXN] = {0, }; // real id를 input id로
int sccCnt = 0; // 정확히는 cnt+1 개 있음
int cId = 0;

void dfs(int curr) // curr은 input id임에 유의
{
    ids[curr] = ++cId; // 1번부터 번호매김
    int& nId = ids[curr];
    lows[nId] = nId;
    
    st.push_back(nId);
    isInStack[nId] = true;
    
    for (int i=1;i<=V;++i) // 엣지탐색
    {
        if (edges[curr][i])
        {
            if (ids[i] == UNVISITED) dfs(i);
            // 이미 방문했더라도 값을 업데이트해주어야 할 수도 있음 (e.g. 0-1-2-0순 dfs)
            if (isInStack[ids[i]])
                lows[nId] = min(lows[nId], lows[ids[i]]);
        }
    }
    
    if (nId == lows[nId])
    {
        while (true)
        {
            int cn = st.back();
            isInStack[cn] = false;
            st.pop_back();
            if (cn == nId) break;
        }
        sccCnt++;
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> V >> E;
    int A, B;
    
    for (int i=0;i<E;++i)
    {
        cin >> A >> B;
        edges[A][B] = true;
    }
    memset(ids, UNVISITED, sizeof(ids));
    
    // SCC
    for (int i=1;i<=V;++i)
    {
        if (ids[i] == UNVISITED) dfs(i);
    }
    
    cout << sccCnt << '\n';
    
    for (int i=1;i<=V;++i) idMap[ids[i]] = i;
    
    vector<int> retV[MAXN];
    for (int i=1;i<=V;++i)
    {
        retV[lows[i]].push_back(idMap[i]);
    }
    
    // {{}, {}, ... {1,5,4}, ... {7,3,2}, ... {6} ... {}, {}}
    // 를 내부 정렬한 후 첫자리 오름차 순으로 정렬해야 함.
    
    // 내부 정렬
    for (int i=1;i<=V;++i)
    {
        if (!retV[i].empty())
        {
            vector<int> tmp;
            for (int j : retV[i]) tmp.push_back(j);
            sort(tmp.begin(), tmp.end());
            retV[i] = tmp;
        }
    }
    
    // 첫자리 기준 정렬
    // TODO
    return 0;
}
