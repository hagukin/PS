#include <iostream>
#include <algorithm>

using namespace std;
int N, M;
int A[10001];
int ret = 0; int lptr = 0;

int main()
{
    cin >> N >> M;
    int sum = 0;
    for (int i=0;i<N;i++)
    {
        cin >> A[i];
        sum += A[i];
        while (sum > M) sum -= A[lptr++];
        ret += sum == M;
    }
    cout << ret;
    return 0;
}
// 입력과 동시에 풀이하며, 코드 곳곳에서 최적화를 위한 부분들이 보인다.
// 정말 깔끔한 코드라고 생각한다.
