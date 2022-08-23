#include <iostream>

using namespace std;

int t;

long long gcd(int a, int b) // a >= b
{
    if (!(a%b)) return b;
    return gcd(b, a%b);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> t;
    int arr[101];
    for (int tc=0;tc<t;tc++)
    {
        int n; long long ret = 0;
        cin >> n;
        for (int i=0;i<n;i++)
        {
            cin >> arr[i];
        }
        for (int j=0;j<n;j++)
        {
            for (int k=j+1;k<n;k++)
            {
                ret += gcd(arr[j],arr[k]);
            }
        }
        cout << ret << '\n';
    }
    return 0;
}
