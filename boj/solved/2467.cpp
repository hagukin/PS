#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

int main(){
    int n;
    int arr[100000];
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    
    if (arr[0] >= 0 && arr[1] >= 0) cout << arr[0] << " " << arr[1];
    else if (arr[n-1]<= 0 && arr[n-2] <= 0) cout << arr[n-2] << " " << arr[n-1];
    else
    {
        int i = 0, j = n-1;
        int sum = abs(arr[i] + arr[j]); // 합의 절댓값을 저장
        int ret1 = arr[0], ret2 = arr[n-1];
        while (i<j)
        {
            if(abs(arr[i] + arr[j]) < sum )
            {
                ret1 = arr[i];
                ret2 = arr[j];
                sum = abs(arr[i]+arr[j]);
            }
            if(arr[i]+arr[j] == 0) break;
            else if (abs(arr[i]) > abs(arr[j])) i++;
            else if (abs(arr[i]) < abs(arr[j])) j--;
        }
        cout << ret1 << " " << ret2 << '\n';
    }
    return 0;
}
