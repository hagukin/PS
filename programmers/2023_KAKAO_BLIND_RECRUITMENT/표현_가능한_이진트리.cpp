#include <string>
#include <vector>
#include <cmath>
#include <iostream>
/*
정석적인 풀이는 서브트리들로 나눠가며 조건을 확인해나가는 O(logN)풀이이지만,
나는 일단 O(N) 풀이법으로 풀이했다.
N이 커봐야 60정도이므로 시간면에서는 거의 차이가 없고, 오히려 단순연산이 많은 이 풀이가 더 빠른 경우가 많긴 하지만,
구현하는 데 훨씬 오랜 시간이 걸린다는 점이 큰 단점이다.
아직까지 이렇게 푼 사람을 보질 못하긴 했다

일단 풀이는 크게 다음과 같은 과정에 의해 처리된다.
1. 주어진 수를 이진수로 바꾸고, 이 이진수를 Complete Binary Tree로 표현했을 때 노드가 총 몇 개 필요한지를 구한다.
2. 구한 이진수의 각 노드들 (카카오 예제에서 준 그림에서는 인덱스가 1번부터 시작하지만, 구현에서는 0번부터 시작한다)을 순회하면서 현재 값이 0인 루트의 자식들중 1이 있는지를 확인한다. 
하나라도 있다면 해당 트리는 만들 수 없는 잘못된 트리이므로 이것들을 걸러낸다.

1번 과정은 로직 자체는 크게 어렵지 않지만, 고려할 것들이 조금 있다.

먼저 이진수를 어떻게 저장할까에 대해서는,
십진수를 이진수로 바꿔주는 과정에서 수의 범위가 10^15 이하이므로 
2^3^15 < 10^15 < 2^4^15 이고,
이는 2^45 < 10^15 < 2^60 이므로
길이가 대략 60정도 되는 bool 배열로 입력범위 수 전체를 커버할 수 있음이 보장된다고 판단해 길이 60짜리 벡터를 만들고 그 곳에 이진수를 저장했다.

그리고 이진수를 저장할 때 우측에서부터 읽는 이진수와는 다르게 벡터이기 때문에 좌측에서부터 저장되고,
때문에 이진수가 뒤집힌 채로 저장된다는 문제가 있는데, 우리가 구하려는 문제에 대해서는 트리가 좌우로 뒤집히더라도 동일한 결과가 나오기 때문에
굳이 다시 한 번 뒤집어주지는 않았다.

필요한 노드의 갯수에 대해서는, 완전 이진 트리 특성상 그 노드의 갯수가 2^k - 1개 꼴이 나와야 한다는 점을 간과해 시간을 꽤나 잡아먹었다.
입력으로 주어지는 이진수가 1011이라면 단순히 노드 4개를 사용하는 게 아니라, 나머지를 0으로 채운 0001011 꼴이 되어 7개를 사용해야 된다는 점을 제대로 인지하지 않고 구현하다보니
이 문제를 찾는 데까지 꽤 시간이 걸렸다.

거기다가, 또 하나의 문제점은
앞서 우리는 길이 60인 배열로 모든 입력을 저장할 수 있다는 것을 증명했다.
그러나 이건 어디까지나 입력된 수를 이진수로 바꿨을 때만의 이야기고,
입력된 수를 이진수로 바꾼뒤,
그 이진수를 Complete Binary Tree로 만들기 위해 노드를 추가하게 되면 이야기는 또 달라진다!
바로 이부분이 놓치기 쉬운 부분인데, 때문에 우리는 2^k-1인 수들 중 1,3,7,15,31,63까지 고려해주어야 한다.
(사실 어떤 데이터셋이 주어지냐에 따라서 더 큰 127까지 고려해주어야 할 지도 모르겠다, 그러나 일단 해당 문제 TC들에 한해서는 63까지만으로 충분했다)

이 문제의 핵심 로직은 바로 2번 과정, 즉 어떤 노드의 자식을 구하는 부분이다.
일반적으로 binary tree를 표기할 때는 위에서부터 아래로, depth가 얕은 것부터 깊은 것 순으로 index 번호를 늘려가며 표현하며, 
이렇게 했을 때는 어떤 idx의 자식을 idx*2 + 1, idx*2 + 2와 같이 간편하게 구할 수 있다.

하지만 이 문제에서는 인덱스를 왼쪽에서부터 x축을 기준으로 번호를 늘려가기 때문에,
나는 어떤 idx 번호가 주어졌을 때 그 idx의 자식 idx를 구하는 공식을 새로 도출해야 했다.
그렇게 얻은 식이 getChildIdx()에 구현되어있는 식이다.

여기서 문제는 그냥 idx값만 있으면 바로 자식 idx를 구할 수 있던 기존의 Binary Tree 표기법과는 달리,
이 표현법에서는 자식 idx를 구하기 위해서는, 현재 idx의 깊이를 알아야 한다는 점이다.
따라서 현재 idx 깊이를 구하기 위해 getIdxDepth()라는 함수를 구현했다.
이 함수는 재귀적으로 subtree를 타고 내려가 총 몇 개의 subtree가 있는 지를 세는 방식으로 depth를 파악한다.

아무튼 이렇게 이제 idx값만 알면 해당 idx의 depth와 해당 idx의 자식의 idx들을 얻을 수 있게 되었다.
이걸 활용해 우리는 이제 어떤 Binary Tree의 모든 노드들을 방문하며 해당 노드의 자식 정보를 얻을 수 있고,
이는 다르게 말해 2번 과정도 구현했음을 의미한다.
*/
using namespace std;

int validNodeCnt[6] = {1,3,7,15,31,63}; // 1개가 될 수 있음에 주의

pair<vector<int>, int> decToBin(long long dec)
{
    // 반환: 이진수 벡터, 트리 노드의 갯수
    vector<int> binaries(64,0);
    int nodeCnt = 0;
    for (int i=0;dec>0;++i)
    {
        if (dec % 2) binaries[i] = 1;
        dec /= 2;
        nodeCnt++;
    }
    // 58을 넣으면 여기선 뒤집힌 꼴의 0101110이 나옴, 그러나 좌우반전 트리 결과는 동일하므로 상관없음
    
    // 더미노드 채워주기는 이미 되있으므로 안해도 됨
    // 단, 노드의 갯수와 벡터의 길이가 다르므로 이부분에 대한 조정이 필요함
    // nodeCnt는 반드시 2^k - 1꼴이어야 하므로 이걸 맞춰줘야 함. 가령 5라면 7, 2라면 3으로 맞춰줘야함.
    for (int i : validNodeCnt)
    {
        if (i>=nodeCnt)
        {
            nodeCnt = i; 
            break;
        }
    }
    return {binaries, nodeCnt};
}

int getIdxDepth(int idx, int nodeCnt)
{
    if (idx == nodeCnt/2 || nodeCnt == 1) return 0; // idx가 최상단 루트
    if (nodeCnt/2 > idx) // 좌측 subtree
    {
        return 1 + getIdxDepth(idx, nodeCnt/2);
    }
    else // 우측
    {
        return 1 + getIdxDepth(nodeCnt-1-idx, nodeCnt/2);
    }
}

pair<int,int> getChildIdx(int rootIdx, int nodeCnt)
{
    pair<int,int> funcRet;
    int rootDepth = getIdxDepth(rootIdx, nodeCnt);
    int treeDepth = log2(nodeCnt+1) - 1;
    if (rootDepth == treeDepth) return {-1,-1};
    
    funcRet.first = rootIdx - pow(2,(treeDepth - rootDepth - 1));
    funcRet.second = rootIdx + pow(2,(treeDepth - rootDepth - 1));
    return funcRet;
}

int check(pair<vector<int>, int> data)
{
    vector<int>& binaries = data.first;
    int nodeCnt = data.second;
    
    for (int i=0;i<nodeCnt;++i) // 트리는 0번부터 시작
    {
        pair<int,int> childs = getChildIdx(i,nodeCnt);
        if (childs.first == -1) continue; // 자식 없음
        if (binaries[i] == 0 && (binaries[childs.first] || binaries[childs.second])) 
        {
            return 0;
        }
    }
    return 1;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    for (long long& n : numbers)
    {
        answer.push_back(check(decToBin(n)));
    }    
    return answer;
}
