#include <iostream>
using namespace std;
int N;
int A[100001];
int B[100001];
int nPosA[100001]; // nPosA[i] = 숫자 i가 A에서 몇번 인덱스에 위치하는지
int nPosB[100001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i=0;i<N;++i)
    {
        cin >> A[i];
        nPosA[A[i]] = i;
    }
    for (int i=0;i<N;++i)
    {
        cin >> B[i];
        nPosB[B[i]] = i;
    }
    
    /*
    AB
    3 1 4 2 5
    1 3 5 2 4
    nPosAB
    - 1 3 0 2 4
    - 0 3 1 4 2
    
    LCS는 1,4
    1다음에 4가 나왔다. 양쪽의 nPos 1,4는
    각각 1,2 그리고 0,4이므로 둘다 증가한다.
    
    즉 이 문제는 nPosA, nPosB를 모두 고려한 LIS를 구하는 문제이다.
    (원래 LIS는 하나의 배열에 대해서만 구하는데, 
    대신 nPosA, nPosB 모두 증가해야만 Increase한다고 판정하는 것으로 답을 구할 수 있다.)
    */
    
    return 0;
}
