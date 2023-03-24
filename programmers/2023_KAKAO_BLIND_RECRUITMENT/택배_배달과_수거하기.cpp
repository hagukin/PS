#include <string>
#include <vector>
#include <iostream>

/*
다 풀고 생각난건데 rMoves, dMoves 두 개 말고 하나만 쓰고 최대값만 저장하고,
만약 한 쪽이 끝났으면 그냥 바로 벡터에 push_back해주는 방식으로 메모리 절약할 수 있을 듯하다.
정답 구하는데 영향은 없으니 굳이 수정해주진 않겠다
*/

typedef long long ll;

using namespace std;

int dEnd = -1, rEnd = -1; // [dEnd+1,n-1]까지 배송 완료되었음을 의미 즉 dEnd부터 배송해줘야함

ll solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    ll answer = 0;
    /*
    if rEnd < dEnd:
        dEnd까지 이동하며 택배 전달
        dEnd 도착 시점에는 트럭 빔
        시작까지 돌아오는 과정에서 rEnd를 거치므로 그냥 돌아오면서 보이는 족족 수거하면됨
    else: (dEnd < rEnd)
        dEnd까지 이동하며 택배전달
        dEnd 도착 시점에는 트럭 빔
        dEnd~rEnd까지 빈 상태로 이동
        시작까지 돌아오는 과정에서 보이는 족족 수거하면됨
    결국 로직은 동일
    */
    for (int i=n-1;i>=0;--i)
    {
        if (dEnd == -1 && deliveries[i] != 0) dEnd = i;
        if (rEnd == -1 && pickups[i] != 0) rEnd = i;
    }
    
    vector<int> dMoves;
    vector<int> rMoves;
    dMoves.push_back(dEnd);
    rMoves.push_back(rEnd);
    
    int cCap = 0;
    for (int i=n-1;i>=0;)
    {
        if (cCap + deliveries[i] <= cap)
        {
            cCap += deliveries[i];
            deliveries[i] = 0;
            --i;
        }
        else
        {
            deliveries[i] -= (cap - cCap); // 꽉 채움
            cCap = 0;
            dMoves.push_back(i); // i부터 해야함
        }
    }
    
    cCap = 0;
    for (int i=n-1;i>=0;)
    {
        if (cCap + pickups[i] <= cap)
        {
            cCap += pickups[i];
            pickups[i] = 0;
            --i;
        }
        else
        {
            pickups[i] -= (cap - cCap); // 꽉 채움 (이미 꽉차있을 수도 있음)
            cCap = 0;
            rMoves.push_back(i); // i부터 해야함
        }
    }
    
    // 답 구하기
    int vMaxSize = max(dMoves.size(), rMoves.size());
    int vMinSize = min(dMoves.size(), rMoves.size());
    for (int i=0;i<vMinSize;++i)
    {
        answer += max(dMoves[i]+1, rMoves[i]+1) * 2;
    }
    
    vector<int>& longerV = dMoves;
    if (rMoves.size() > dMoves.size()) longerV = rMoves;
    
    for (int i=vMinSize;i<vMaxSize;++i)
    {
        answer += (longerV[i]+1) * 2;
    }
    
    return answer;
}
