#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void solve(int& max, int& min, int cur, int&k, vector <int> &nums)
{
	if ((cur < max) && (cur >= min))
	{
		nums.push_back(cur);
		return;
	}
	if (((cur % 10) - k >= 0) && ((cur % 10) - k <= 9))
		solve(max, min, (cur * 10) + ((cur % 10) - k), k, nums);

	if ((((cur % 10) + k >= 0) && ((cur % 10) + k <= 9)) && (k!=0))
		solve(max, min, (cur * 10) + ((cur % 10) + k), k, nums);

}

void put_first_digit(int&k, int&min, int&max, vector <int> &nums, int i = 1)
{
	if (i > 9)
		return;
	solve(max, min, i, k, nums);
	put_first_digit(k, min, max, nums, ++i);
}

void show_nums(vector<int>& nums, int vector_size, int index = 0)
{
	if (index >= vector_size)
		return;
	cout << nums[index] << endl;
	show_nums(nums, vector_size, ++index);
}

int main()
{
	int n, k;
	cin >> n >> k;
	int max, min;
	vector <int> nums;
	max = (int)pow(10, n);
	min = (int)pow(10, n - 1);
	put_first_digit(k, min, max, nums);
	show_nums(nums, nums.size());
	return 0;
}