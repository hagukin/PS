* priority_queue
```c++
// 1. cmp 사용 시 (맘 편하게 그냥 항상 cmp를 구현해줘도 상관없다)
struct a{
    int start;
    int end;
    int value;
};
 
struct cmp{
    bool operator()(a t, a u){
        return t.value < u.value;
    }
};
priority_queue<a,vector<a>,cmp> pq;

// 2. greater 사용시 (int같은 기본 자료형의 오름차 정렬일 경우 cmp구현이 필요없다)
// priority_queue<int,vector<int>,less<int> > pq; -> 기본값
priority_queue<int,vector<int>,greater<int> > pq;
```
* lambda sort
```c++
std::sort(s.begin(), s.end(), [](int a, int b) {
    return a > b;
});
```
* memset(arr, -1, sizeof(arr)) 도 가능하다 (-1 가능)
* int arr[101] = {0, }; 로 일괄에 크기만큼 0으로 초기화 가능
* Vector 2D 초기화
```c++
int value = 1;
vector<vector<int>> matrix(M, vector<int>(N, value));
```
* 2진수 입력  
```c++
0b00111;
```
* Python의 a == b == c와 c++의 a == b == c를 혼동하지 말것!
* 파이썬에서는 세 값이 모두 같은지를 비교해주는 반면 c++에서는 (a == b) == c 순으로 처리한다.
```c++
// c++
(2 == 2 == 2); // false
//주의:
(1 == 1 == 1); // true
// (1 == 1)이 true인데 true == 1은 1 == 1로 typecast되어 true 반환.
```
```python
# Python3
(2 == 2 == 2) // True
(1 == 1 == 1) // True
```
* for loop bracket 생략하면서 여러 줄 쓰는법  
```c++
for (...)
    do_this(), do_that(), do_this_too();
```  
* auto& 사용  
```c++
for (auto& x : arr)
    cout << x << endl;
```  
* vector 정해진 값들로 초기화  
```c++
vector<int> v{1,2,3,4};
```  
* cmp 구현 시 조건이 true면 그냥 놔두고 false면 순서를 바꿔준다
```c++
// 오름차순 구현
bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first;
}
```
* make_pair와 rvalue
```c++
int A,B;
for (int i=0;i<N;++i)
{
    cin >> A >> B;
    v.push_back(make_pair<int,int>(A,B)); // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    
    // 해결법들
    v.push_back({A,B}); // 간단한 방법
    v.push_back(make_pair(A,B)); // 컴파일러에게 타입을 알아서 정하라고 하는 방법
    v.push_back(make_pair<int,int>(std::move(A),std::move(B)); // 수동으로 lvalue로 바꿔주는 방법
    
    // 참고
    pair<int, pair<int,int>> pp = {0, {1, 3}}; // 가능!
}
```
원인: https://stackoverflow.com/questions/68732574/insertion-in-map-using-array-error-cannot-bind-rvalue-reference-of-type-int  

* #\<algorithm\> lower_bound, upper_bound  
https://modoocode.com/298  

* char로 된 숫자를 int로  
```c++
char c = '5';
int ci = c - '0';
```
* std::gcd(a, b)  
#include \<numeric\>에 정의  
[그 외 참고하면 좋은 팁들](https://kswims.tistory.com/137)

* 조합의 경우(nCk) 재귀함수로 구현하는 게 통상적이나 k=3개정도까지는 N의 크기에 따라 그냥 for 중첩을 사용하는 것을 고려해보자.  
```c++
for i < N
  for j < i
    for k < j
```
