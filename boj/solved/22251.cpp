#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int n, k, p, x;
int arr[10][10] = { 0 }; // arr[i][j] = i번 숫자가 j번 숫자가 되기 위해 반전시켜야하는 전등의 최소 갯수
string str;

int dfs(int depth, int cnt) // depth: 현재 수정하려는 인덱스
{
	if (depth >= str.length()) 
	{
		if (stoi(str) == x) return 0; // 변환 전후가 같은 경우는 생각하지 않는다.
		if (stoi(str) <= n && stoi(str) >= 1) return 1; // 범위가 1~N인 경우만 고려
		return 0;
	}

	int sum = 0;
	int cur = str[depth] - '0'; // char을 int로 (0~9이므로 성립)
	for (int i=0; i<10; i++)
	{
		if ((cur != i) && (cnt-arr[cur][i] >= 0)) // 같은 숫자로의 변환 방지 + 변환 횟수 초과하지 않게 확인
		{
			str[depth] = i + '0'; // str 변환 (int를 char로)
			sum += dfs(depth+1, cnt-arr[cur][i]);
			str[depth] = cur + '0'; // 변환한거 다시 복구 (백트래킹)
		}
		if (cur == i) sum += dfs(depth+1, cnt); // 변환을 안하는 경우 (같은 숫자 그대로)
	}
	return sum;
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
	int num[] = { 0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011 }; // 이진수로 초기화
	/*
	. 0 .
	5 . 1
	. 6 .
	4 . 2
	. 3 .
	*/
	cin >> n >> k >> p >> x;
	
	// 캐시 생성
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) 
		{
		    // XOR을 이용해 서로 다른 전등의 갯수를 구한다.
			int diff = num[i]^num[j];
			while (diff != 0) 
			{
			    // XOR해서 나온 값이 0이 될때까지 (=모든 1에 대하여) 연산
			    // 연산의 횟수가 곧 1의 갯수, 즉 다른 전등의 갯수
				if (diff & 1) arr[i][j]++;
				diff >>= 1; // 우로 한칸 이동
			}
		}
	}

	str = to_string(x);
	while(str.length() < k) str.insert(str.begin(), '0'); // 길이 k를 맞추기 위해 앞에 0 채워넣기
	cout << dfs(0,p) << '\n';
    return 0;
}
