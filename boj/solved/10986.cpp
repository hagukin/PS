#include<iostream>
using namespace std;

int N, M;
long long leftover[1001];
long long sum, ans;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	int x;
	for (int i = 0; i < N; i++) {
		cin >> x;
		sum += x;
		leftover[sum % M]++;
	}

	for (int i = 0; i <= 1000; i++) {
		ans += leftover[i] * (leftover[i] - 1) / 2;
	}
	cout << leftover[0] + ans;
}
