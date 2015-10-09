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
	~Jugs() {
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
void BFS(vector<int> &curr, vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) {
	cout << curr[2] << endl;
	//base case curr == target
	//check if curr is visited
		//if yes end
		//if no
			//recursively call
}
int main(int argc, char * const argv[]) {
	//array[ array[bool] ] visited
	/*Jugs *test = new Jugs(1, 3, 5);
	cout << test->first() << endl;
	*/
	vector<int> test;
	test.push_back(0);
	test.push_back(0);
	test.push_back(8);
	vector<int> target;
	target.push_back(3);
	target.push_back(5);
	target.push_back(0);
	vector< vector<int> > visited;
	queue< vector<int> > search;
	BFS(test, target,visited, search);
	return 0;
}




