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

<<<<<<< HEAD
bool Compare(vector<int> &curr, vector<int> &target) {
	unsigned int i = 0;
	for(i = 0; i < curr.size() && curr[i] == target[i]; i++) 
	{
		;
	}
	if(i == 3) 
	{
		return true;
=======
/*class Jugs {
public:
	Jugs(int a, int b, int c) :
			distribution_(new int[3]), first_(a), second_(b), third_(c) {
		set();
	}
	~Jugs() {
		delete[] distribution_;
	}
	inline int* distribution() const {
		return distribution_;
>>>>>>> parent of c50bf2d... Main function changed
	}
	return false;
}

void BFS(vector<int> &curr,int capa, int capb, int capc,
		vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) {
	if(Compare(curr, target)) {
		return;
	}
}

void BFS_helper(vector<int> &curr, int capa, int capb, int capc,
		vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) {
	//this should really be a helper function, where the main function calls this to queue up more things and then looks at the next one
	//available adds a specific case to the queue and is set to false so we can check if we can use that possibility or if we have
	vector<int> next;
	bool progress = false;
	bool available = false;
	if(curr[2] > 0 && curr[0] < capa) {
		if(curr[2] > (capa - curr[0])) {
			next.push_back(capa);
			next.push_back(curr[1]);
			next.push_back(curr[2]-(capa-curr[0]));
			next.push_back(1);
			next.push_back(capa - curr[0]);
		} else {
			next.push_back(curr[0] + curr[2]);
			next.push_back(curr[1]);
			next.push_back(0);
			next.push_back(1);
			next.push_back(curr[2]);
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			progress = true;
			search.push(next);
			available = false;
		}
		//if at any time next == target it should break all of these if statements
	}

	if(curr[1] > 0 && curr[0] < capa) {
		if(curr[1] > (capa - curr[0])) {
			next.push_back(capa);
			next.push_back(curr[1]-(capa-curr[0]));
			next.push_back(curr[2]);
			next.push_back(2);
			next.push_back(capa-curr[0]);
		} else {
			next.push_back(curr[0] + curr[1]);
			next.push_back(0);
			next.push_back(curr[2]);
			next.push_back(2);
			next.push_back(curr[1]);
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			progress = true;
			search.push(next);
			available = false;
		}
	}

	if(curr[2] > 0 && curr[1] < capb) {
		if(curr[2] > (capb - curr[1])) {
			next.push_back(curr[0]);
			next.push_back(capb);
			next.push_back(curr[2] - (capb-curr[1]));
			next.push_back(3);
			next.push_back(capb-curr[1]);
		} else {
			next.push_back(curr[0]);
			next.push_back(curr[1] + curr[2]);
			next.push_back(0);
			next.push_back(3);
			next.push_back(curr[2]);
		}
		if(visited[next[0]][next[1]]) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			progress = true;
			search.push(next);
			available = false;
		}
	}
<<<<<<< HEAD

	if(curr[0] > 0 && curr[1] < capb) {
		if(curr[0] > (capb - curr[1])) {
			next.push_back(curr[0] - (capb - curr[1])));
			next.push_back(capb);
			next.push_back(curr[2]);
			next.push_back(4);
			next.push_back(capb - curr[1]);
		} else {
			next.push_back(0);
			next.push_back(curr[0] + curr[1]);
			next.push_back(curr[2]);
			next.push_back(4);
			next.push_back(curr[0]);
		}
		if(visited[next[0]][next[1]]) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			progress = true;
			search.push(next);
			available = false;
		}
	}
}

/*
void BFS(vector<int> &curr, vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) 
{
	cout << curr[2] << endl;

	if(curr[1] > 0 && curr[2] < capc) {
		if(curr[1] > (capc - curr[2])) {
			next.push_back(curr[0]);
			next.push_back(curr[1] - (capc - curr[2]));
			next.push_back(capc);
			next.push_back(5);
			next.push_back(capc - curr[2]);
		} else {
			next.push_back(curr[0]);
			next.push_back(0);
			next.push_back(curr[1] + curr[2]);
			next.push_back(5);
			next.push_back(curr[1]);
		}
		if(visited[next[0]][next[1]]) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			progress = true;
			search.push(next);
			available = false;
		}
	}

	if(curr[0] > 0 && curr[2] < capc) {
		if(curr[0] > (capc - curr[2])) {
			next.push_back(curr[0] - (capc - curr[2]));
			next.push_back(curr[1]);
			next.push_back(capc);
			next.push_back(6);
			next.push_back(capc-curr[2]);
		} else {
			next.push_back(0);
			next.push_back(curr[1]);
			next.push_back(curr[2] + curr[0]);
			next.push_back(6);
			next.push_back(curr[0]);
		}
		if(visited[next[0]][next[1]]) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			progress = true;
			search.push(next);
			available = false;
		}
	}
	//when broken early the result should be a vector with the queue in BFS, the only check is the last item since it is the target
	//if found will break early, or not because it never found it.
	return;
=======
};
*/
void BFS(vector<int> &curr, vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) {
	cout << curr[2] << endl;
>>>>>>> parent of c50bf2d... Main function changed
	//base case curr == target
	//check if curr is visited
		//if yes end
		//if no
			//recursively call
	/*
	 * 1) Pour from C to A 2) Pour from B to A 3) Pour from C to B 4) Pour from A to B 5) Pour from B to C 6) Pour from A to C
	 */
}
int main(int argc, char * const argv[]) {
	//array[ array[bool] ] visited
	/*Jugs *test = new Jugs(1, 3, 5);
	cout << test->first() << endl;
	*/
<<<<<<< HEAD
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
=======
>>>>>>> parent of c50bf2d... Main function changed
	vector<int> test;
	test.push_back(0);
	test.push_back(0);
	test.push_back(8);
	test.push_back(0);
	vector<int> target;
	target.push_back(3);
	target.push_back(5);
	target.push_back(0);
<<<<<<< HEAD
	vector< vector<bool> > visited;
	
	queue< vector<int> > search;
	BFS(test, target, visited, search);
	//queue< vector<int> > result;
	BFS(test, target,visited, search);
	*/
=======
	vector< vector<int> > visited;
	queue< vector<int> > search;
	BFS(test, target,visited, search);
>>>>>>> parent of c50bf2d... Main function changed
	return 0;
}




