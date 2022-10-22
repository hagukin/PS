/*
처음 접근법(오답):
가장 큰 원소부터 하나씩 정렬해나가므로
위치가 "잘못된" 원소들의 갯수를 구하고 거기에 1을 더하는 방식으로 접근했다.
테케를 다 통과하고 직접 만들어본 테케도 통과해서 혹시나 해서 넣어봤지만 오답...
시간 날때 반례를 찾아 틀린 이유를 제대로 검증해보자
#include <iostream>
#include <vector>
using namespace std;
int A[500005];
int N;

int solve()
{
    vector<int> v;
    int funcRet = 1;
    int i=1;
    while (i<=N)
    {
        if (v.empty() || v.back() <= A[i]) v.push_back(A[i]);
        else
        {
            v.pop_back();
            funcRet += 1;
            continue;
        }
        ++i;
    }
    return funcRet;
}

int main()
{
    cin >> N;
    for(int i=1;i<=N;++i)
    {
        cin >> A[i];
    }
    cout << solve() << endl;
    return 0;
}

올바른 접근법은 정렬 전의 각 값들의 인덱스(순서)가 정렬 후 얼마나 변했는지 그 차를 이용하는 데에 있다.
한 번의 "순회" 과정(버블 소트에서 하나의 i값에 대해 j값을 증가시키며 한번 for loop을 도는 것)에서 
어떤 숫자는 우측으로는 끝까지 갈 수 있지만, 좌측으로 최대 1칸밖에 이동할 수 없다는 점을 이용해
정렬 전후의 인덱스를 비교해 가장 많이 좌측으로 이동한 수의 인덱스차를 구해 답을 구할 수 있다.
참고: https://scarlettb.tistory.com/114
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
int N;

vector<pair<int,int>> v;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int tmp;
    for(int i=0;i<N;++i)
    {
        cin >> tmp;
        v.push_back(make_pair(tmp,i));
    }
    sort(v.begin(),v.end());
    int ret = INT_MIN;
    for(int i=0;i<N;++i)
    {
        ret = max(ret, v[i].second-i);
    }
    ret += 1;
    cout << ret << '\n';
    return 0;
}
