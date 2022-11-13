#include <iostream>
#include <string>
using namespace std;

int main()
{
	int s;
	int m;
	int n;
	int previous;
	int current;
	int result;
	string pass = "";
	cin >> s >> m;
	cin >> n;
	cin >> previous;
	for (int i = 1; i < n; i++)
	{
		cin >> current;
		for (int j = 97; j < 123; j++)
		{
			if (((j + previous)*s) % m == current)
			{
				pass = pass + (char)j;
				break;
			}
		}
		previous = current;
	}
	cout << pass;
	return 0;
}