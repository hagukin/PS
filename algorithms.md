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

## 선형대수
### 행렬의 N 거듭제곱  
A^8을 구하기 위해서는 A * A를 8번 계산하는 O(N) 풀이도 있지만,  
A^10 = (A^4)^2라는 성질을 이용해 더 빠르게 구할 수 있다.  
A^4는 (A^2)^2 이므로, 우리는 log2(8) = 3회의 행렬곱 연산으로 구할 수 있다.  
MxM 행렬의 행렬곱 연산 1회에는 O(M^3)이 소요되므로(구현해보면 알 수 있다), 총 시간복잡도는 O(M^3 * logN)이다.  
N이 짝수가 아닌 경우 A^(N-1)을 먼저 구한 후 A를 마지막에 한번 더 곱해주면 된다.  

이를 코드로 구현할 때 그냥 O(log2)에 구현할 수도 있지만 비트연산을 사용해 더 최적화할 수 있다.  
[참고](https://greeksharifa.github.io/algorithm%20&%20data%20structure/2018/07/04/algorithm-matrix-power/)  

```c++
TODO
```

### 행렬 멱법(Matrix Exponentiation)  
선행 알고리즘: 행렬의 N 거듭제곱  
![image](https://user-images.githubusercontent.com/63915665/195061740-0c46b7a3-a213-49d1-92f9-697f4887151f.png)  
**위 사진과 같은 형태의 재귀되는 수열의 n번째 항을 구할 때 행렬 멱법을 사용하면 O(log N)에 구할 수 있다. 피보나치 수열이 대표적이다. (DP로는 O(N)이 최선이다)** (예제 - 백준 7677, 14440)  

한줄 요약:  
F(n) = a1 * F(n-1) + a2 * F(n-2) + ... ak * F(n-k) 라는 재귀식으로 표현가능한 수열의 n(=F(n))을 빠르게 구하는 알고리즘이다.  
구하는 값들 n개를 좌변 행렬에 두고, 구하는 값에 필요한 값 n개를 우변 행렬에 둔 뒤 가운데 nxn 행렬을 직접 규칙에 맞게 정해둔 후  
행렬곱을 n번 가량 처리하면 F(n)을 구할 수 있다.  
행렬곱을 n번 하는 것, 즉 행렬의 N 거듭제곱을 구할 때는 log2에 구할 수 있는 행렬거듭제곱 알고리즘을 사용한다.  
![image](https://user-images.githubusercontent.com/63915665/195066304-9c24da71-3fcf-45ee-9b3d-c4e070bd6e68.png)  
사진: 피보나치 수열 구하는 과정 (O(logN))  
[1 1]\[1 0] 행렬을 구하는 방법은 어렵지 않은데, 그냥 잘 생각해보면 구할 수 있다. F(n) = 1\*F(n-1) + 1\*F(n-2)이므로 첫째 행에는 1 1이 들어가고, F(n-1) = 1\*F(n-1) + 0\*F(n-2)이므로 둘째 행에는 1 0이 들어간다.  

[참고글1](https://ohgym.tistory.com/1)  
[참고글2](https://zzonglove.tistory.com/31)  
위 글에는 크게 잘못된 부분 (피보나치 수열은 F(n) =F(n-1)+F(n-2)인데 여기서는 F(n) = F(n-1)+F(n-2)+F(n-3)으로 구하는 중임) 이 있으니 알고리즘의 원리 자체를 이해하는 데에만 사용할 것.  

### 행렬의 거듭제곱들의 합 (A^1 + ... A^N)  
S(N) = (A^1 + ... + A^N)이라 하자.  

N이 짝수일 때:  
S(N)  
= (A^1 + ... A^(N/2)) * A^(N/2) + (A^1 + ... A^(N/2))  
= (A^1 + ... A^(N/2)) * (A^(N/2) + I)  
= S(N/2) * (A^(N/2) + I)  
이를 재귀적으로 하면 log2로 단축할 수 있다.  

N이 홀수일 때:  
S(N)  
= S(N-1) + A^N  
단 S(0)은 0이다.  

A^K를 구할 때는 행렬의 N 거듭제곱 알고리즘을 사용해 O(M^3 * logN)에 구한다.  
행렬거듭제곱을 logN번 가량 해야 하므로 총 시간복잡도는 대략 O(M^3 * (logN)^2)이다.  

[참고1](https://memoacmicpc.tistory.com/entry/%EB%B0%B1%EC%A4%80-13246%EB%B2%88-%ED%96%89%EB%A0%AC-%EC%A0%9C%EA%B3%B1%EC%9D%98-%ED%95%A9)  
[참고2](https://blog.naver.com/PostView.naver?blogId=jinhan814&logNo=222383870866&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView)  

```c++
TODO
```

### 슈트라센 알고리즘 (NxN 행렬간의 곱을 O(N^3)보다 빠른 O(N^2.38)에 풀이 가능)  
TODO  

# 이분탐색  
## Lower_bound vs Upper_bound  
![image](https://user-images.githubusercontent.com/63915665/185752220-2f6d3103-82a4-41d1-99c5-b575168554ff.png)  
