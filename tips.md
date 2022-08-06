* lambda sort
```c++
std::sort(s.begin(), s.end(), [](int a, int b) {
    return a > b;
});
```
* memset(arr, -1, sizeof(arr)) 도 가능하다 (-1 가능)
