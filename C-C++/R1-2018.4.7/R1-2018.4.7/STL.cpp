#include<iostream>
using namespace std;

#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<functional>
#include<numeric>
#include<deque>
#include<time.h>

class Speaker
{
public:
	string	name;
	int		score[3];
};

void GenSpeaker(map<int, Speaker> &mapSpeaker, vector<int> &v)
{
	string Names = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";	
	random_shuffle(Names.begin(), Names.end());

	for (int i = 0; i < 24; i++)
	{
		Speaker tmp;
		tmp.name = "选手";
		tmp.name += Names[i];
		mapSpeaker.insert(pair<int, Speaker>(100 + i, tmp));

		v.push_back(100 + i);
	}

	cout << "参赛选手信息：" << endl;
	for (map<int, Speaker>::iterator it = mapSpeaker.begin(); it != mapSpeaker.end(); it++)
	{
		cout << it->first << "\t" << it->second.name << "\n";
	}
}

void DrawSpeaker(map<int,Speaker> &mapSpeaker, vector<int> &v)
{
	int index = 0, group = 1;
	cout <<endl<< "*****分组*****" << endl;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		if(index++%6 == 0)
		{
			cout << endl << "第" << group << "组分组情况:" << endl;
			group++;
		}
		cout << *it << "\t" <<mapSpeaker[*it].name<< "\n";
	}
}

void ContestSpeaker(int round,map<int, Speaker> &mapSpeaker, vector<int> &v_in, vector<int> &v_out)
{
	cout << endl << "*****比赛*****" << endl;
	int index = 0, group = 1;
	srand((unsigned)time(NULL));
	multimap<int, int, greater<int>>multimapGroup;

	for (vector<int>::iterator it = v_in.begin(); it != v_in.end(); it++)
	{
		index++;

		deque<int> dscore;
		for (int j = 0; j < 10; j++)
		{
			int score = 50 + 50*rand()/(RAND_MAX+1.0);
			dscore.push_back(score);
		}

		sort(dscore.begin(), dscore.end());
		dscore.pop_back();
		dscore.pop_front();

		int scoresum = accumulate(dscore.begin(), dscore.end(), 0);
		int scoreavg = scoresum / dscore.size();

		mapSpeaker[*it].score[round] = scoreavg;
		multimapGroup.insert(pair<int, int>(scoreavg, *it));

		if (index % 6 == 0)
		{
			cout << endl << "第" << group << "组得分情况：" << endl;
			group++;


			for (multimap<int, int, greater<int>>::iterator mit = multimapGroup.begin(); mit != multimapGroup.end(); mit++)
			{
				cout << mit->second << "\t" << mapSpeaker[mit->second].name << "\t" << mit->first << endl;
			}

			while (multimapGroup.size()>3)
			{
				multimap<int, int, greater<int>>::iterator it1 = multimapGroup.begin();
				v_out.push_back(it1->second);
				multimapGroup.erase(it1);
			}
			multimapGroup.clear();
		}
	}
}


void PrintSpeaker(int round, map<int, Speaker> &mapSpeaker, vector<int> &v)
{
	cout << endl << "*****第" << round + 1 << "轮比赛晋级名单*****" << endl;
	for (vector<int>::iterator it = v.begin();it!=v.end();it++)
	{
		cout << "参赛编号：" << *it << "\t" << mapSpeaker[*it].name << "\t" << mapSpeaker[*it].score[round] << endl;
	}
}





void main()
{
	map<int, Speaker> mapSpeaker;
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;

	GenSpeaker(mapSpeaker, v1);

	DrawSpeaker(mapSpeaker, v1);
	ContestSpeaker(0,mapSpeaker, v1, v2);
	PrintSpeaker(0,mapSpeaker, v2);

	DrawSpeaker(mapSpeaker, v2);
	ContestSpeaker(1,mapSpeaker, v2, v3);
	PrintSpeaker(1,mapSpeaker, v3);

	DrawSpeaker(mapSpeaker, v3);
	ContestSpeaker(2,mapSpeaker, v3, v4);
	PrintSpeaker(2,mapSpeaker, v4);

	system("pause");
}