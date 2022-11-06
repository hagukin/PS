#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
int A[100001];
int tmp2[100001]; // tmp2[i] = i라는 숫자가 B에서 몇번 idx에 있는가
int bIdx[100001]; // bIdx[i] = A[i]라는 숫자가 B에서 몇번 idx에 있는가

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i=0;i<N;++i)
    {
        cin >> A[i];
    }
    int tmp;
    for (int i=0;i<N;++i)
    {
        cin >> tmp;
        tmp2[tmp] = i; // 메모리 최적화를 위해 B[i] 배열은 기록하지 않는다 (필요가 없음)
    }
    for (int i=0;i<N;++i)
    {
        bIdx[i] = tmp2[A[i]];
    }
    
    /*
    인풋:
    5
    3 1 4 2 5
    1 3 5 2 4
    
    3 1 4 5 2 기준으로 idx 나열시
    3 1 4 5 2 는 그대로
    0 1 2 3 4
    
    1 3 5 2 4 는
    1 0 4 3 2 로 표현 가능
    (3의 idx=1), (1의 idx=0), (4의 idx=4) ...
    
    A의 인덱스는 증가하는 수열 0 1 2 3 4니까 
    1 0 4 2 3에서 LIS를 찾는다는 것은
    B의 인덱스와 A의 인덱스 양쪽 모두가 증가하는 방향의 최대 길이의 수열을 찾는 것을 의미
    => 우리가 구하려는 LCS가 바로 이거!
    
    최종적으로 1 0 4 2 3의 LIS를 구하면 끝
    */
    
    // LIS
    vector<int> lis;
    lis.push_back(bIdx[0]);
    for (int i=0;i<N;++i)
    {
        int curr = bIdx[i];
        auto ub = lower_bound(lis.begin(), lis.end(), curr);
        if (ub == lis.end()) lis.push_back(curr);
        else lis[ub-lis.begin()] = curr;
    }
    cout << lis.size() << '\n';
    return 0;
}
