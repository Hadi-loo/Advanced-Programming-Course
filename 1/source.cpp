#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <time.h>
using namespace std;
int main(void)
{
	int k, s, a;
	cin >> k >> a >> s;

	vector < vector<string> > names(k);
	vector < vector<int> > t_stat(k);
	vector <int> groups(k);
	vector <int> groups_p1;
	vector <int> groups_p2;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			names[i].push_back("");
			cin >> names[i][j];
			t_stat[i].push_back(0);
		}
		groups[i] = i;
	}

	srand((unsigned int)time(NULL));
	for (int i = 0; i < k - 1; i++)
	{
		int j = i + rand() % (k - i);
		swap(groups[i], groups[j]);
	}

	int groups_index = 0;
	int student_index;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < s; j++)
		{
			if (groups_index == k)
			{
				sort(groups.begin(), groups.end());
				sort(groups_p1.begin(), groups_p1.end());
				set_difference(groups.begin(), groups.end(), groups_p1.begin(), groups_p1.end(), back_inserter(groups_p2));
				srand((unsigned int)time(NULL));
				for (int l = 0; l < (int)groups_p2.size() - 1; l++)
				{
					int L = l + rand() % (groups_p2.size() - l);
					swap(groups_p2[l], groups_p2[L]);
				}
				srand((unsigned int)time(NULL));
				for (int l = 0; l < (int)groups_p1.size() - 1; l++)
				{
					int L = l + rand() % (groups_p1.size() - l);
					swap(groups_p1[l], groups_p1[L]);
				}
				groups_p2.insert(groups_p2.end(), groups_p1.begin(), groups_p1.end());
				groups = groups_p2;
				groups_p2.clear();
				groups_index = 0;
			}
			if ((t_stat[groups[groups_index]][0] == 1) && (t_stat[groups[groups_index]][1] == 1) && (t_stat[groups[groups_index]][2] == 1))
			{
				t_stat[groups[groups_index]][0] = 0;
				t_stat[groups[groups_index]][1] = 0;
				t_stat[groups[groups_index]][2] = 0;
			}
			do
			{
				student_index = rand() % 3;
			} while (t_stat[groups[groups_index]][student_index] != 0);
			cout << names[groups[groups_index]][student_index] << " ";
			groups_p1.push_back(groups[groups_index]);
			t_stat[groups[groups_index]][student_index] = 1;
			groups_index++;
		}
		cout << "\n";
		groups_p1.clear();
	}
	cout << "\n";
	return 0;
}

