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

[그 외 참고하면 좋은 팁들](https://kswims.tistory.com/137)
