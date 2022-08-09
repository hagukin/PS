/*
10 15
5 1 3 5 10 7 4 9 2 8
o o o o o
합 S 이상이므로 좌측끝(i) 삭제 후 i++
 o o o o
여전히 합 S 이상이므로 동일
  o o o
   o o -> 최솟값 2 찾음
    o
    합 S 이하이므로 우측에 하나 추가
    o o -> 최솟값 2 또 찾음 (10+7)
    ...
*/

#include <iostream>

using namespace std;
int N, S, ret;
int arr[100001];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> S;
    for (int i=0;i<N;i++)
    {
        cin >> arr[i];
    }
    
    // solve
    int l = 0; int r = 0;
    // l=0일때 r찾기
    int sum = 0;
    for (int i=0;i<N;i++)
    {
        sum += arr[i];
        if (sum >= S) {r = i; ret = r-l+1; break;}
    }
    // 진행
    while (l<=r && r<N && l<N)
    {
        if (sum>=S)
        {
            ret = min(r-l+1, ret);
            sum-=arr[l]; 
            l++;
        }
        else{r++; sum+=arr[r];}
    }
    cout << ret << '\n';
    return 0;
}
