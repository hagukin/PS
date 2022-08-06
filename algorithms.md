# 수학
## 정수론
### 에라토스테네스의 체
최적화된 풀이  
```c++
#include<cstring>
constexpr int MAX=1000001;
bool prime[MAX];
void eratosthenes(){
    memset(prime, false, MAX);//배열을 초기화한다.
    prime[2]=true;//2는 소수다. 이러면 3 이상의 홀수만 판별하면 된다.
    for(int i=3;i<MAX;i+=2)
        prime[i]=true;
    for(int i=3;;i+=2)//2씩 더해 굳이 짝수를 검색하지 않아도 된다.
        if(prime[i]==true){
            int j=i*i;
            if(j>=MAX) break;
            for(i*=2;j<MAX;j+=i){//i를 2배로 하여 i의 짝수곱을 굳이 검색하지 않게 한다. 짝수들인 이미 다 false로 제거되었다.
	    // i는 이미 필터링된 수이기 때문에 무조건 홀수인데, j = i*i이고, j+=(i*2)는 i*i+=(i*2), 이는 i * (i+2)이므로 i의 홀수배임을 알 수 있다. (i+2가 홀수이기 때문) 
	    // 때문에 2*i씩 더해주는 것으로 홀수들만 살펴볼 수 있다.
                prime[j]=false;
            }
            i/=2;//i 원상복구
        }
}
```  
  
최적화된 풀이 직접 구현  
```c++
#include <cstring>
#include <iostream>
using namespace std;
constexpr int MAXN = 1001;
int N;
int isPrime[MAXN];

void solve()
{
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0]=false; isPrime[1]=false;
    for (int i=4;i<=N;i+=2) {isPrime[i]=false;}
    for(int i=3;i<=N;i+=2)
    {
        if (isPrime[i])
        {
            int j=i*i;
            if (j>N) break;
            for(i*=2;j<=N;j+=i)
            {
                isPrime[j]=false;
            }
            i/=2;
        }
    }
}

void printPrime()
{
    for (int i=0;i<=N;i++)
    {
        if (isPrime[i]) cout << i << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    solve();
    printPrime();
    return 0;
}
```  

### 유클리드 호제법 / 유클리드 알고리즘
어떤 두 수의 최대공약수를 구하는 알고리즘  
방법1: https://tmdgus.tistory.com/45?category=244962  
세가지 성질을 이용해 풀이  
* GCD(a, b) = GCD(a-b, b)
* GCD(a, b) = GCD(b, a)
* GCD(x, 0) = x

방법2: https://namu.wiki/w/유클리드%20호제법  
위에 적은 성질들 + 몫,나머지를 이용해 풀이  
![image](https://user-images.githubusercontent.com/63915665/178215907-f35ae61a-e7d8-43c7-bec0-b7812dcf69a0.png)  
**손으로 계산할 때는 제수와 피제수의 값 크기를 비교해서 적절하게 배열하지만 수식이나 코드로 나타낼 때는 신경쓰지 않아도 되는데, a<b일 때 a mod b ≡ a이므로 Gcd(a,b)는 Gcd(b,a)를 호출한다. 즉 재귀 과정에서 자연스럽게 큰 값이 a로, 작은 값이 b로 들어간다.**  
(참고: 모듈러 연산 - https://ko.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/what-is-modular-arithmetic)
```c++
int Euclidean(int a, int b)
{
    int r = a % b;
    if (r == 0) return b;
    return Euclidean(b, r);
}
```

## 계산기하
### Convex hull (볼록 껍질)
일반화된 풀이
long double을 사용하지만 테스트케이스에 따라 double이나 심지어는 float로도 풀릴 수도 있다.
단 cmp 시 만약 atan2를 사용한다면 long double의 사용이 불가하다.

```c++
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

typedef pair<double, double> P;
typedef pair<P, P> PP;
vector<P> v;
vector<int> st;
int startPoint,res;
int x, y;

bool cmp(const P a, const P b) {
	if ((x - b.first)*(y - a.second) == (x - a.first)*(y - b.second))
	{
		if (a.second == b.second)
			return a.first < b.first;
		else
			return a.second < b.second;
	}
	else 
	{
		return (x - b.first)*(y - a.second) < (x - a.first)*(y - b.second);	// dy/dx 비교
	}
}

/*
//atan2 사용 가능
//long double일때 불가능함에 유의

bool cmp(const P a, const P b) {
    double aa = atan2(a.second - y, a.first - x);
    double bb = atan2(b.second - y, b.first - x);
    
	if (aa == bb) 
	{
		if (a.second == b.second)
			return a.first < b.first;
		else
			return a.second < b.second;
	}
	else return aa < bb;
}
*/


double ccw(PP a,P b) {
	P a1 = a.first,a2=a.second;
	double ccw11 = (a1.first*a2.second + a2.first*b.second + b.first*a1.second)
		- (a2.first*a1.second + b.first*a2.second + a1.first*b.second);

	return ccw11;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	int q, w;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> q >> w;
		v.push_back({ q,w });
		if (v[startPoint].second > w ||(v[startPoint].second==w && v[startPoint].first > q)) {
			startPoint = i;
		}
	}
	
	x = v[startPoint].first;
	y = v[startPoint].second;
	
	sort(v.begin(), v.end(), cmp);
	
	st.push_back(0);
	st.push_back(1);
	int t = 1; // top
	int idx = 2;
	
	while (idx < n) {
		double ccwV = ccw(make_pair(v[st[t-1]], v[st[t]]), v[idx]);
		if (ccwV>0) {
			st.push_back(idx);
			idx++;
			t++;
		}
		else if (ccwV == 0) {
			st.pop_back();
			st.push_back(idx);
			idx++;
		}
		else {
			st.pop_back();
			t--;
		}
	}
	
    /********
    필요에 맞게 코드 작성
    ********/
    
	return 0;
}
```
