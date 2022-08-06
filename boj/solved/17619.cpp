#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
constexpr int MAXN = 100002;
int N, Q;

int x1[MAXN];
int x2[MAXN];
int logSorted[MAXN]; // x1기준 오름차순으로 정렬된 Log들의 인덱스
int logGroup[MAXN]; // x1기준 오름차순으로 정렬된 Log들의 그룹번호
int logOrder[MAXN]; // logOrder[log.ind] = 정렬순서

/*
logs - 그냥 값 저장
logSorted 1 3 2 4 5 6
logGroup 0 0 0 0 1 1
logOrder X 0 2 1 3 4 5

3번과 5번 연결 확인:
logGroup[LogOrder[3]] == logGroup[LogOrder[5]]
*/

bool cmpLog(int c1, int c2)
{
    return x1[c1] < x1[c2];
}

bool isConnected(int i1, int i2)
{
    return logGroup[logOrder[i1]] == logGroup[logOrder[i2]];
}

void solve()
{
    int maxX2 = x2[logSorted[0]];
    int nx1, nx2;
    int groupNum = 0;
    for (int l=0;l<N;l++)
    {
        nx1 = x1[logSorted[l]];
        nx2 = x2[logSorted[l]];
        
        if (nx1 > maxX2) groupNum++;
        logGroup[logOrder[logSorted[l]]] = groupNum;
        maxX2 = max(nx2, maxX2);
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(x1, 0, sizeof(x1));
    memset(x2, 0, sizeof(x2));
    memset(logSorted, 0, sizeof(logSorted));
    memset(logGroup, 0, sizeof(logGroup));
    memset(logOrder, 0, sizeof(logOrder));
    
    cin >> N >> Q;
    int tx1, tx2, ty;
    for (int i=1;i<=N;i++)
    {
        cin >> tx1 >> tx2 >> ty;
        x1[i] = tx1; x2[i] = tx2;
        logSorted[i-1] = i;
    }
    
    sort(logSorted, logSorted+N, cmpLog);
    
    // init logOrder
    for (int k=0;k<N;k++)
    {
        logOrder[logSorted[k]] = k;
    }
    
    solve();

    int l1, l2;
    for (int j=0;j<Q;j++)
    {
        cin >> l1 >> l2;
        cout << isConnected(l1, l2) << '\n';
    }
    return 0;
}
