#include <iostream>
#include <string>
using namespace std;

int main()
{
	int s;
	int m;
	int n;
	cin >> s >> m;
	cin >> n;
	int result = s;
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		result = (result+temp)*s;
		result %= m;
	}
	cout << result;
	return 0;
}