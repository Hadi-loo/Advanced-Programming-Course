#include <iostream>
#include <vector>
using namespace std;
int row_delta[4] = { 1,0,-1,0 };
int col_delta[4] = { 0,1,0,-1 };

int solve(int& row, int& col, int i, int j, vector <vector<int>> height, vector <vector<int>> jumped, vector<int> road, int lenght = 1)
{
	if (lenght == 3)
	{
		cout << road[0] << " " << road[1] << " " << road[2] << endl;
		return 1;
	}

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
					road[lenght] = height[new_row][new_col];
					if (solve(row, col, new_row, new_col, height, jumped, road, lenght + 1) == 1)
					{
						return 1;
					}
					jumped[new_row][new_col] = 0;
					road[lenght] = 0;
				}
			}
		}
	}
	return 0;
}

int main()
{
	int col, row;
	cin >> col >> row;
	vector <vector<int>> height(row, vector<int>(col));
	vector <vector<int>> jumped(row, vector<int>(col, 0));
	vector <int> road(3, 0);
	int check = 0;
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
			road = { height[i][j],0,0 };
			jumped[i][j] = 1;
			check = solve(row, col, i, j, height, jumped, road);
			if (check == 1)
				exit(0);
			jumped[i][j] = 0;
		}
	}
	if (check == 0)
		cout << -1;
	return 0;
}