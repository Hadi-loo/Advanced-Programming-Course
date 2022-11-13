#include <iostream>
using namespace std;

int find_max_index(int x, int& max, int& max_index)
{
	if (x == 0)
		return max_index;

	int height;
	cin >> height;

	if (height > max)
	{
		max = height;
		max_index = x;
		return find_max_index(x - 1, max, max_index);
	}

	else
		return max_index;
}

int main(void)
{
	int n;
	int max = 0;
	int max_index = 0;
	cin >> n;
	cout << n - find_max_index(n , max, max_index) + 1 << endl;
	return 0;
}