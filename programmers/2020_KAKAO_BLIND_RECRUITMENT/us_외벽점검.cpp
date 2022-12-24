#include <string>
#include <vector>
#include <iostream>
#include <memory.h>

using namespace std;

/*
느낌 상 그리디인데 원형 테두리 상에서 진행되는 그리디 느낌
원형 테두리 구현할 때 % 활용하는 것보다 직관적으로 하는 법이 생각났는데, 
어차피 친구 한명이 갈 수 있는 최대 거리는 100이므로 199에서 출발한다고 해도 299까지밖에 못가고
0에서 출발해도 -100까지밖에 못감.
이걸 이용해서 -100 ~ 299 즉 길이 400짜리 배열 하나를 만들고 (n이 200이라 할떄) -1번과 199번을 같은 포인터로 설정해두면 비교적 쉽게 그리디 구현이 가능하지 않을까 싶음.

이번엔 실제로 최소명수를 구할 방법을 고민해보자.
무조건 이동거리가 긴 친구부터 사용하는 게 이득이므로
앞서 말한 방법대로 원형 테두리를 하나의 어레이로 표현한 이후
인덱스 0부터 끝까지 돌면서 길이 d인 막대가 최대한 많은 취약지점을 덮는 경우가 언제인지를 구한다.
그후 덮인 지점 및 그 덮인 지점과 같은 포인터를 공유하는 지점들을 제거해주고
같은 과정을 반복하면 답이 나올 듯 하다.

친구 8명에 for loop, 커봐야 O(40000)이니까 충분히 가능.
*/


int solution(int n, vector<int> weak, vector<int> dist) 
{
    int answer = 0;
    
    bool walls[201] = {false,}; // 취약할 경우 true
    int wallIdx[401] = {0,}; // i번 도착지점이 벽의 몇번 지점과 맵핑되는지
    memset(wallIdx, -1, sizeof(wallIdx));
    
    // 반시계 이동
    for (int j=100;j>=0;j-=n)
    {
        for (int i=0;i<n;++i)
        {
            if (j-i<0) break;
            if (i==0) wallIdx[j-i] = 0;
            else wallIdx[j-i] = n-i;
        }
    }
    
    // 시계 이동
    for (int j=100;j<401;j+=n)
    {
        for (int i=0;i<n;++i)
        {
            if (j+i>=401) break;
            wallIdx[j+i] = i;
        }
    }
    
    // solve
    // 다른 풀이로 접근해야할 듯, 그리디 반례가 있을거라는 느낌이 강하게 듬
    // 사지방 시간상 반례찾는건 나중으로
//     int maxRepCnt = 0;
//     vector<int> repaired;
//     for (int i=0;i<401;++i)
//     {
//         for (int j=0;j<n;++j)
//         {
//             int repairCnt = 0;
//             vector<int> tmp;
//             if (wallIdx[i+j] != -1)
//             {
//                 repairCnt++;
//                 tmp.push_back(wallIdx[i+j]);
//             }
//         }
//         if (repairCnt > maxRepCnt)
//         {
            
//         }
//     }
    
    
    // 테스트
    // for (int i=0;i<401;++i)
    // {
    //     cout << i << " " << wallIdx[i] << endl;
    // }
    
    
    return answer;
}
