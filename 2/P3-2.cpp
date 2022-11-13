#include <iostream>
#include <vector>
using namespace std;

int row_delta[4] = { 1,0,-1,0 };
int col_delta[4] = { 0,1,0,-1 };
vector <int> final_road;

int solve(int& row, int& col, int i, int j, vector <vector<int>> &height, vector <vector<int>> jumped, vector<int> road)
{
	for (int k = 0; k < 4; k++)
	{
		int new_row = i + row_delta[k];
		int new_col = j + col_delta[k];
		if (((new_row < row) && (new_row >= 0)) &&
			((new_col < col) && (new_col >= 0)))
		{
			if (abs(height[i][j] - height[new_row][new_col]) == 1)
			{
				if (jumped[new_row][new_col] == 0)
				{
					jumped[new_row][new_col] = 1;
					road.push_back(height[new_row][new_col]);
					if (solve(row, col, new_row, new_col, height, jumped, road) == 1)
					{
						return 1;
					}
					jumped[new_row][new_col] = 0;
					road.pop_back();
				}
			}
		}
	}
	if (road.size() > final_road.size())
	{
		final_road = road;
	}
	return 0;
}

void show(vector <int> sample)
{
	for (int i = 0; i < sample.size(); i++)
		cout << sample[i] << " ";
}

int main()
{
	int col, row;
	cin >> col >> row;
	vector <vector<int>> height(row, vector<int>(col));
	vector <vector<int>> jumped(row, vector<int>(col, 0));
	vector <int> road;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> height[i][j];
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			road.clear();
			road.push_back(height[i][j]);
			jumped[i][j] = 1;
			solve(row, col, i, j, height, jumped, road);
			jumped[i][j] = 0;
		}
	}
	if (final_road.size() <= 1)
		cout << -1;
	else
		show(final_road);
	return 0;
}