/*******************************************************************************
 * Name        : waterjug.cpp
 * Author      : Justin Tsang
 * Date        : October 8, 2015
 * Description : List the most efficient path to reach target jug amounts
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

/* What we need:
 * BFS
 * visit each adjacent
 * return vec of vec
 * Display
 */

vector<int> pourJugs(vector<int> curr, vector<int> &sizes, int from, int to, int order)
{
	/*
	for (vector<int>::iterator it = curr.begin(); it != curr.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	for (vector<int>::iterator it = sizes.begin(); it != sizes.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << from << " " << to << endl;
	*/
	if ((curr[to] + curr[from]) <= sizes[to])
	{
		curr[to] = curr[to] + curr[from];
		curr[from] = 0;
	}
	else
	{
		curr[from] = curr[from] - sizes[to] - curr[to];
		curr[to] = sizes[to];
	}
	curr[3] = order;
	/*
	for (vector<int>::iterator it = curr.begin(); it != curr.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	*/
	return curr;
}

vector< vector<int> > getAdjacents(vector<int> curr, vector<int> &sizes)
{
	vector< vector<int> > ways;
	if ((curr[2] > 0) && (curr[0] < sizes[0]))
	{
		ways.push_back(pourJugs(curr, sizes, 2, 0, 1));
	}
	if ((curr[1] > 0) && (curr[0] < sizes[0]))
	{
		ways.push_back(pourJugs(curr, sizes, 1, 0, 2));
	}
	if ((curr[2] > 0) && (curr[1] < sizes[1]))
	{
		ways.push_back(pourJugs(curr, sizes, 2, 1, 3));
	}
	if ((curr[0] > 0) && (curr[1] < sizes[1]))
	{
		ways.push_back(pourJugs(curr, sizes, 0, 1, 4));
	}
	if ((curr[1] > 0) && (curr[2] < sizes[2]))
	{
		ways.push_back(pourJugs(curr, sizes, 1, 2, 5));
	}
	if ((curr[0] > 0) && (curr[2] < sizes[2]))
	{
		ways.push_back(pourJugs(curr, sizes, 0, 2, 6));
	}
	return ways;
}

//vector< vector<int> >
void BFS(
		vector<int> curr, vector<int> &jarSizes, vector<int> &target, 
		vector< vector<bool> > &isVisited, queue< vector<int> > &searches)
{
	//Current vertex
	for (vector<int>::iterator it = curr.begin(); it != curr.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	
	//If reach target
	if (equal(curr.begin(), curr.begin() + 3, target.begin()))
	{
		cout << "Done" << endl;
	}
	if (!(isVisited[curr[0]][curr[1]]))
	{
		searches.push(curr);
		isVisited[curr[0]][curr[1]] = true;
		// Show all visited list
		cout << "Visited" << endl;
		for (vector< vector<bool> >::const_iterator it = isVisited.begin(); it != isVisited.end(); ++it)
		{
			for (vector<bool>::const_iterator its = (*it).begin(); its != (*it).end(); ++its)
			{
				cout << (*its) << " ";
			}
			cout << endl;
		}
		
		vector< vector<int> > paths = getAdjacents(curr, jarSizes);
		
		//All possible adjacent paths of cuurent vertex
		cout << "Branches" << endl;
		for (vector< vector<int> >::const_iterator it = paths.begin(); it != paths.end(); ++it)
		{
			for (vector<int>::const_iterator its = (*it).begin(); its != (*it).end(); ++its)
			{
				cout << (*its) << " ";
			}
			cout << endl;
		}
		cout << endl;
		
		for (vector< vector<int> >::iterator it = paths.begin(); it != paths.end(); ++it)
		{
			searches.push(*it);
			//BFS((*it), jarSizes, target, isVisited, searches);
		}
	}
}

bool parseArg(vector<int> &jarSizes, vector<int> &target)
{
	int counter = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (target[i] > jarSizes[i])
		{
			switch (i)
			{
				case (0):
					cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
					return false;
				case (1):
					cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
					return false;
				case (2):
					cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
					return false;
			}
		}
		counter += target[i];
	}
	if (counter != jarSizes[2])
	{
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return false;
	}
	return true;
}



int main(int argc, char * const argv[]) 
{
	if (argc != 7)
	{
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	//Create two vectors initial and target in main function
	istringstream iss;
	vector<int> curr(4);
	vector<int> jarSizes(3);
	vector<int> target(3);
	queue< vector<int> > BFS_queue;
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
					cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
					return 1;
				}
				jarSizes[0] = val;
				break;
			case (2):
				if ((!(iss >> val)) || (val <= 0))
				{
					cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
					return 1;
				}
				jarSizes[1] = val;
				break;
			case (3):
				if ((!(iss >> val)) || (val <= 0))
				{
					cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
					return 1;
				}
				jarSizes[2] = val;
				break;
			case (4):
				if ((!(iss >> val)) || (val < 0))
				{
					cerr << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
					return 1;
				}
				target[0] = val;
				break;
			case (5):
				if ((!(iss >> val)) || (val < 0))
				{
					cerr << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
					return 1;
				}
				target[1] = val;
				break;
			case (6):
				if ((!(iss >> val)) || (val < 0))
				{
					cerr << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
					return 1;
				}
				target[2] = val;
				break;
		}
		iss.clear();
	}
	//In parseArg, have two parameters that take vector<int>
	if (parseArg(jarSizes, target))
	{
		vector< vector<bool> > visited(jarSizes[0] + 1, vector<bool>(jarSizes[1] + 1));
		/*
		for (vector< vector<bool> >::const_iterator it = visited.begin(); it != visited.end(); ++it)
		{
			for (vector<bool>::const_iterator its = (*it).begin(); its != (*it).end(); ++its)
			{
				cout << (*its) << " ";
			}
			cout << endl;
		}
		*/
		curr[2] = jarSizes[2];
		BFS_queue.push(curr);
		//vector< vector<int> > path = 
		BFS(curr, jarSizes, target, visited, BFS_queue);
		cout << endl << endl;
	}
	
	//delete [] visited;
	return 0;
}