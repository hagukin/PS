#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> answer;

vector<int> visOrder;
int paths[103] = {0,}; // paths[i] = j:  현재 i->j 길이 활성화되어있다는 뜻
bool treeData[103][103] = {false,};
int visCnt[103] = {0,};
vector<int> ansList[103];

int MAX_DROP_CNT;
int NODE_CNT;

int drop(int curr)
{
    // 현재의 dropLeaf 다음 번 drop을 시행한다. 도착 leaf의 인덱스 반환
    int next = paths[curr]; // 값 백업
    
    // leaf
    if (next == 0)
    {
        visOrder.push_back(curr);
        return curr;
    }
    
    // paths 업데이트
    bool reachedEnd = true; // 내 뒤에 더 큰 값이 없을 경우
    for (int j=1;j<=NODE_CNT;++j)
    {
        if (treeData[curr][j] && j>next) {paths[curr] = j; reachedEnd = false; break;} // 완료
    }
    if (reachedEnd)
    {
        // 맨 앞 값으로 설정
        for (int j=1;j<=NODE_CNT;++j)
        {
            if (treeData[curr][j]) {paths[curr] = j; break;}
        }
    }
    return drop(next);
}

void getNodeAns(int node, vector<int>& v, int gCnt, int gVal)
{
    // dfs로 풀이시 시간초과
    // 일단 이게 호출되었다는 것은 gCnt * 3 >= gVal >= gCnt를 만족함이 보장된다는 것.
    /*
    9,9 -> 1,1,1,1,1,1,1,1,1  (gCnt == gVal)
    9,8 -> 1,1,1,1,1,1,1,2
    9,7 -> 1,1,1,1,1,1,3 (1,1,1,1,1,2,2보다 우선순위 위임.)
    9,6 -> 1,1,1,1,2,3
    9,5 -> 1,1,1,3,3
    9,4 -> 1,2,3,3
    9,3 -> 3,3,3   (gCnt*3 == gVal)
    9,2 -> X
    9,1 -> X
    
    10,4 -> 1,3,3,3
    10,5 -> 1,1,2,3,3
    
    
    13
    일단 최대한 크기 나타내본다
    3 3 3 3 1
    즉 못해도 5칸 필요
    
    여기서 우리는 최대 2*4 = 8칸을 늘려 13칸으로 표현 가능하다
    */
    int arr[4] = {0,};
    for (int i=0;i<gVal/3;++i)
    {
        arr[3]++;
    }
    int m = gVal % 3;
    arr[m]++;
    
    int cCnt = arr[3]+1;
    if (m==0) cCnt = arr[3]; // 이부분 주의
    while (gCnt>cCnt) // O(100)
    {
        if (arr[2] > 0)
        {
            arr[2] -= 1;
            arr[1] += 2;
        }
        else if (arr[3] > 0)
        {
            arr[3] -= 1;
            arr[2] += 1;
            arr[1] += 1;
        }
        else {cout << "ERROR" << endl;}
        cCnt += 1;
    }
    for (int i=3;i>=1;--i)
    {
        for (int j=0;j<arr[i];++j) v.push_back(i);
    }
    return;
}

vector<int> getAns(int totalCnt, vector<int>& target)
{
    // visCnt와 target을 이용해 i번 leaf node의 visCnt가 x고 target이 y일때
    // (x,y) -> x개의 1,2,3으로 이루어진, 오름차순의, 길이가 최소인, 합이 y인 벡터
    // 를 반환한다
    for (int i=1;i<=NODE_CNT;++i)
    {
        getNodeAns(i, ansList[i], visCnt[i], target[i-1]);
    }
    for (int& leaf : visOrder)
    {
        answer.push_back(ansList[leaf].back());
        ansList[leaf].pop_back();
    }
    return answer;
}

vector<int> solution(vector<vector<int>> edges, vector<int> target) {
    // INIT
    MAX_DROP_CNT = 11000; // worst case를 위한 값: 101개의 노드가 전부 100이 목표값일 때 이걸 전부 1로 채워야 할 경우 대략 10100번의 drop을 시행해줘야한다
    NODE_CNT = edges.size() + 1;
    for (vector<int>& e : edges)
    {
        treeData[e[0]][e[1]] = true;
        if (paths[e[0]] == 0) paths[e[0]] = e[1]; // 초기화
        else paths[e[0]] = min(paths[e[0]], e[1]); // 더 작은 값으로
    }
    
    // SOLVE
    for (int dropCnt = 1;dropCnt<=MAX_DROP_CNT;++dropCnt)
    {
        int cDropLeaf = drop(1); // root에 드랍
        visCnt[cDropLeaf]++;
        
        bool cntValid = true;
        for (int i=1;i<=NODE_CNT;++i)
        {
            if (visCnt[i] * 3 >= target[i-1] && target[i-1] >= visCnt[i]) continue;
            else {cntValid = false; break;}
        }
        if (!cntValid) continue;
        
        // 필요 최소 횟수 찾음
        return getAns(dropCnt, target);
    }
    
    // MAX_DROP_CNT 이상의 인덱스에서부터는 불가능
    answer.push_back(-1);
    return answer;
}
