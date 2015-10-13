/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
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

bool Compare(vector<int> &curr, vector<int> &target) {
	//compares a location by only looking at the first 3 numbers
	//how the water is distributed
	unsigned int i = 0;
	for(i = 0; i < 3 && curr[i] == target[i]; i++) {
		;
	}
	if(i == 3) {
		return true;
	}
	return false;
}

vector<int> pourJugs(vector<int> curr, vector<int> size,
		int from, int to, int order) {
	//returns the next status according to the order given
	if(curr[from] > (size[to] - curr[to])) {
		curr[4] = (size[to] - curr[to]);
		curr[from] = curr[from] - (size[to] - curr[to]);
		curr[to] = size[to];
		curr[3] = order;
	} else {
		curr[4] = curr[from];
		curr[to] = curr[to] + curr[from];
		curr[from] = 0;
		curr[3] = order;
	}
	return curr;
}

bool BFS_helper(vector<int> &curr, int capa, int capb, int capc,
		vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) {
	//enques all unvisited adjacent possibilities
	//returns true if the target is found, enques then returns
	vector<int> next;
	vector<int> size;
	size.push_back(capa);
	size.push_back(capb);
	size.push_back(capc);
	bool available = false;
	if(curr[2] > 0 && curr[0] < capa) {
		next = pourJugs(curr, size, 2, 0, 1);
		//exiting after finding
		if(Compare(next, target)) {
			search.push(next);
			return true;
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			search.push(next);
			available = false;
		}
		next.clear();
	}
	if(curr[1] > 0 && curr[0] < capa) {
		next = pourJugs(curr, size, 1, 0, 2);
		if(Compare(next, target)) {
			search.push(next);
			return true;
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			search.push(next);
			available = false;
		}
		next.clear();
	}

	if(curr[2] > 0 && curr[1] < capb) {
		next = pourJugs(curr, size, 2, 1, 3);
		if(Compare(next, target)) {
			search.push(next);
			return true;
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			search.push(next);
			available = false;
		}
		next.clear();
	}

	if(curr[0] > 0 && curr[1] < capb) {
		next = pourJugs(curr, size, 0, 1, 4);
		if(Compare(next, target)) {
			search.push(next);
			return true;
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			search.push(next);
			available = false;
		}
		next.clear();
	}

	if(curr[1] > 0 && curr[2] < capc) {
		next = pourJugs(curr, size, 1, 2, 5);
		if(Compare(next, target)) {
			search.push(next);
			return true;
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			search.push(next);
			available = false;
		}
		next.clear();
	}

	if(curr[0] > 0 && curr[2] < capc) {
		next = pourJugs(curr, size, 0, 2, 6);
		if(Compare(next, target)) {
			search.push(next);
			return true;
		}
		if(visited[next[0]][next[1]] == 0) {
			available = true;
			visited[next[0]][next[1]] = 1;
		}
		if(available) {
			search.push(next);
			available = false;
		}
		next.clear();
	}

	return false;
	//1) Pour from C to A 2) Pour from B to A 3) Pour from C to B 4) Pour from A to B 5) Pour from B to C 6) Pour from A to C
}

vector< vector<int> > BFS(vector<int> &curr,int capa, int capb, int capc,
		vector<int> &target, vector< vector<int> > &visited, queue< vector<int> > &search) {
	//returns a 2D vector the entire BFS or up to the target
	vector< vector<int> > bfs;
	search.push(curr);
	if(Compare(curr, target)) {
		bfs.push_back(search.front());
		search.pop();
		return bfs;
	} else {
		while(search.empty() == 0) {
			bfs.push_back(search.front());
			BFS_helper(search.front(), capa, capb, capc, target, visited, search);
			if(Compare(target, search.back())) {
				search.pop();
				while(search.empty() != 1) {
					bfs.push_back(search.front());
					search.pop();
				}
				return bfs;
			} else {
				search.pop();
			}
		}
		return bfs;
	}
}

void before(vector< vector<int> > &bfs, vector<int> &target) {
	//pops the end of the vector until the target is at the end
	if(Compare(bfs[bfs.size()-1], target)) {
		return;
	}
	bfs.pop_back();
	before(bfs, target);
	return;
}

vector< vector<int> > find_way(vector< vector<int> > &bfs, vector<int> &target, vector<int> &start) {
	//returns the path from start to target of a BFS by tracing
	//backwards, using the path taken with water poured to find
	//what it should have come from
	vector<int> curr;
	vector<int> next;
	vector< vector<int> > reverse;
	vector< vector<int> > way;
	if(Compare(bfs[bfs.size()-1], target)) {
		curr = bfs[bfs.size()-1];
		while(!Compare(curr, start)) {
			next.clear();
			reverse.push_back(bfs[bfs.size()-1]);
			if(curr[3] == 1) {
				next.push_back(curr[0]-curr[4]);
				next.push_back(curr[1]);
				next.push_back(curr[2]+curr[4]);
			}
			if(curr[3] == 2) {
				next.push_back(curr[0]-curr[4]);
				next.push_back(curr[1]+curr[4]);
				next.push_back(curr[2]);
			}
			if(curr[3] == 3) {
				next.push_back(curr[0]);
				next.push_back(curr[1]-curr[4]);
				next.push_back(curr[2]+curr[4]);
			}
			if(curr[3] == 4) {
				next.push_back(curr[0]+curr[4]);
				next.push_back(curr[1]-curr[4]);
				next.push_back(curr[2]);
			}
			if(curr[3] == 5) {
				next.push_back(curr[0]);
				next.push_back(curr[1]+curr[4]);
				next.push_back(curr[2]-curr[4]);
			}
			if(curr[3] == 6) {
				next.push_back(curr[0]+curr[4]);
				next.push_back(curr[1]);
				next.push_back(curr[2]-curr[4]);
			}
			before(bfs, next);
			curr = bfs[bfs.size()-1];
		}
		reverse.push_back(bfs[0]);
		while(!reverse.empty()) {
			way.push_back(reverse.back());
			reverse.pop_back();
		}
		return way;
	} else {
		next.push_back(-1);
		way.push_back(next);
		return way;
	}
}

void display(vector< vector<int> > &way) {
	unsigned int i;
	if(way[0][0] == -1) {
		cout << "No solution.";
		return;
	} else {
		cout << "Initial state. (" << way[0][0] << ", " << way[0][1] << ", " << way[0][2] << ")";
		for(i = 1; i < way.size(); i++) {
			cout << endl;
			if(way[i][4] == 1) {
				cout << "Pour 1 gallon from ";
			} else {
				cout << "Pour " << way[i][4] << " gallons from ";
			}
			if(way[i][3] == 1) {
				cout << "C to A. (";
			}
			if(way[i][3] == 2) {
				cout << "B to A. (";
			}
			if(way[i][3] == 3) {
				cout << "C to B. (";
			}
			if(way[i][3] == 4) {
				cout << "A to B. (";
			}
			if(way[i][3] == 5) {
				cout << "B to C. (";
			}
			if(way[i][3] == 6) {
				cout << "A to C. (";
			}
			cout << way[i][0] << ", " << way[i][1] << ", " << way[i][2] << ")";
		}
	}
}

int main(int argc, char * const argv[]) {
	//array[ array[bool] ] visited
	/*Jugs *test = new Jugs(1, 3, 5);
	cout << test->first() << endl;
	*/
	//cap a, cap b, cap c, goal a, goal b, goal c
	int a, b, c, capa, capb, capc;
	if(argc != 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
		return 1;
	}
	istringstream iss;
	iss.str(argv[1]);
	if((!(iss >> capa))||(capa <= 0)) {
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A.";
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if((!(iss >> capb))||(capb <= 0)) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B.";
		return 1;
	}
	iss.clear();
	iss.str(argv[3]);
	if((!(iss >> capc))||(capc <= 0)) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C.";
		return 1;
	}
	iss.clear();
	iss.str(argv[4]);
	if((!(iss >> a))||(a < 0)) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A.";
		return 1;
	}
	iss.clear();
	iss.str(argv[5]);
	if((!(iss >> b))||(b < 0)) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B.";
		return 1;
	}
	iss.clear();
	iss.str(argv[6]);
	if((!(iss >> c))||(c < 0)) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C.";
		return 1;
	}
	if(a > capa) {
		cerr << "Error: Goal cannot exceed capacity of jug A.";
		return 1;
	}
	if(b > capb) {
		cerr << "Error: Goal cannot exceed capacity of jug B.";
		return 1;
	}
	if(c > capc) {
		cerr << "Error: Goal cannot exceed capacity of jug C.";
		return 1;
	}
	if((a + b + c) != capc) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
		return 1;
	}
	vector<int> start;
	start.push_back(0);
	start.push_back(0);
	start.push_back(capc);
	start.push_back(0);
	start.push_back(0);
	vector<int> target;
	target.push_back(a);
	target.push_back(b);
	target.push_back(c);
	vector< vector<int> > visited;
	vector<int> fill;
	for(int i = 0; i <= capb; i++) {
		fill.push_back(0);
	}
	for(int j = 0; j <= capc; j++) {
		visited.push_back(fill);
	}
	//the beggining is already visited
	visited[0][0] = 1;
	queue< vector<int> > search;
	vector< vector<int> > bfs;
	vector< vector<int> > way;
	bfs = BFS(start, capa, capb, capc, target, visited, search);
	way = find_way(bfs, target, start);
	display(way);
	return 0;
}
