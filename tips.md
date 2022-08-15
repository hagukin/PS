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
