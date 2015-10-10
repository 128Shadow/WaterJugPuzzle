/*******************************************************************************
 * Name        : waterjug.cpp
 * Author      : Luis Meneses
 * Date        : October 8, 2015
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my Honor I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <deque>
#include <list>
#include <queue>

using namespace std;

/*class Jugs {
public:
	Jugs(int a, int b, int c) :
			distribution_(new int[3]), first_(a), second_(b), third_(c) {
		set();
	}
	~Jugs() 
	{
		delete[] distribution_;
	}
	inline int* distribution() const {
		return distribution_;
	}
	inline int first() const {
		return first_;
	}
	inline int second() const {
		return second_;
	}
	inline int third() const {
		return third_;
	}
private:
	int * const distribution_;
	int const first_, second_, third_;

	void set() {
		distribution_[0] = first_;
		distribution_[1] = second_;
		distribution_[2] = third_;
	}
};
*/

/*
void BFS(vector<int> &curr, vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) 
{
	cout << curr[2] << endl;
	//base case curr == target
	if (!(visited[curr[0], curr[1]]))
	{
		visited[curr[0], curr[1]] = true;
		
	}
		
	//check if curr is visited
		//if yes end
		//if no
			//recursively call
}
*/

bool parseArg(vector<int> &jarSize, vector<int> &target)
{
	for (int i = 0; i < 3; ++i)
	{
		if (target[i] > jarSize[i])
		{
			cerr << "Goal cannot exceed capacity of jug" << endl;
			return false;
		}
	}
}

int main(int argc, char * const argv[])
{
	//array[ array[bool] ] visited
	/*Jugs *test = new Jugs(1, 3, 5);
	cout << test->first() << endl;
	*/
	if (argc != 7)
	{
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	//Create two vectors initial and target in main function
	istringstream iss;
	vector<int> jarSizes(3);
	vector<int> target(3);
	int val;
	string str;
	
	for (int i = 1; i < argc; ++i)
	{
		iss.str(argv[i]);
		
		switch (i)
		{
			case (1):
				if ((!(iss >> val)) || (val <= 0))
				{
					cerr << "Invalid capacity '" << argv[i] << "' for jug A." << endl;
					return 1;
				}
				jarSizes[0] = val;
				break;
			case (2):
				if ((!(iss >> val)) || (val <= 0))
				{
					cerr << "Invalid capacity '" << argv[i] << "' for jug B." << endl;
					return 1;
				}
				jarSizes[1] = val;
				break;
			case (3):
				if ((!(iss >> val)) || (val <= 0))
				{
					cerr << "Invalid capacity '" << argv[i] << "' for jug C." << endl;
					return 1;
				}
				jarSizes[2] = val;
				break;
			case (4):
				if ((!(iss >> val)) || (val < 0))
				{
					cerr << "Invalid goal '" << argv[i] << "' for jug A." << endl;
					return 1;
				}
				target[0] = val;
				break;
			case (5):
				if ((!(iss >> val)) || (val < 0))
				{
					cerr << "Invalid goal '" << argv[i] << "' for jug B." << endl;
					return 1;
				}
				target[1] = val;
				break;
			case (6):
				if ((!(iss >> val)) || (val < 0))
				{
					cerr << "Invalid goal '" << argv[i] << "' for jug C." << endl;
					return 1;
				}
				target[2] = val;
				break;
		}
		iss.clear();
	}
	//In parseArg, have two parameters that take vector<int>
	parseArg(jarSizes, target);
	/*
	istringstream iss;
	int val;
	string str;
	for (int i = 1; i < argc; ++i)
	{
		iss.str(argv[i]);
		iss >> str;
		if (i <= 3)
		{
			if ((!(iss >> val))|| (val <= 0))
			{
				switch (i)
				{
					case (1):
						cerr << "Invalid goal '" << str << "' for jug A." << endl;
						return 1;
					case (2):
						cerr << "Invalid goal '" << str << "' for jug B." << endl;
						return 1;
					case (3):
						cerr << "Invalid goal '" << str << "' for jug C." << endl;
						return 1;
				}
			}
		}
		else
		{
			if (!(iss >> val) && (val < 0))
			{
				cerr << "Invalid capacity for " << endl;
				return 1;
			}
		}
		iss.clear();
	}
	*/
		/*
	vector<int> test;
	test.push_back(0);
	test.push_back(0);
	test.push_back(8);
	vector<int> target;
	target.push_back(3);
	target.push_back(5);
	target.push_back(0);
	vector< vector<bool> > visited;
	
	queue< vector<int> > search;
	BFS(test, target, visited, search);
	*/
	return 0;
}




