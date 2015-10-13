/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
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
 */

//Perform the pouring of water from one jug to other
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
		curr[4] = curr[from];
		curr[from] = 0;
	}
	else
	{
		curr[from] = curr[from] - sizes[to] - curr[to];
		curr[4] = sizes[to] - curr[to];
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

//Get all adjacent ways from current jug measurements
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
/*
//vector< vector<int> >
void BFS_helper(
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
			if (!(isVisited[(*it)[0]][(*it)[1]]))
			{
				searches.push(*it);
			}
			searches.pop();
			//BFS((*it), jarSizes, target, isVisited, searches);
		}
	}
}
*/

void BFS_helper(
		vector<int> curr, vector<int> &jarSizes, vector<int> &target, 
		vector< vector<bool> > &isVisited, queue< vector<int> > &searches,  
		vector< vector<int> > &result)
{
	//If reach target
	if (!(equal(curr.begin(), curr.begin() + 3, target.begin())))
	{
		if (!(isVisited[curr[0]][curr[1]]))
		{
			searches.push(curr);
			isVisited[curr[0]][curr[1]] = true;
			
			vector< vector<int> > paths = getAdjacents(curr, jarSizes);

			for (vector< vector<int> >::iterator it = paths.begin(); it != paths.end(); ++it)
			{
				if (!(isVisited[(*it)[0]][(*it)[1]]))
				{
					searches.push(*it);
					BFS_helper((*it), jarSizes, target, isVisited, searches, result);
					searches.pop();
				}
			}
		}
	}
	else
	{
		while (searches.size() > 0)
		{
			result.push_back(searches.front());
			searches.pop();
		}
	}
}

vector< vector<int> > BFS(vector<int> curr, vector<int> &jarSizes, vector<int> &target)
{
	vector< vector<int> > result;
	queue< vector<int> > searches;
	vector< vector<bool> > visitedJars(jarSizes[0] + 1, vector<bool>(jarSizes[1] + 1));;
	if (!(visitedJars[curr[0]][curr[1]]))
	{
		searches.push(curr);
		result.push_back(curr);
		visitedJars[curr[0]][curr[1]] = true;
		vector< vector<int> > paths = getAdjacents(curr, jarSizes);
		
		for (vector< vector<int> >::iterator it = paths.begin(); it != paths.end(); ++it)
		{
			if (!(visitedJars[(*it)[0]][(*it)[1]]))
			{
				searches.push(*it);
				BFS_helper((*it), jarSizes, target, visitedJars, searches, result);
				result.push_back(searches.front());
				searches.pop();
			}
		}
	}
	return result;
}

//Print path
void displayPath(vector< vector<int> > &way)
{
	for (vector< vector<int> >::iterator it = way.begin(); it != way.end(); ++it)
	{
		if (it == way.begin())
		{
			cout << "Initial state. (";
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
				{
					cout << (*it)[i];
				}
				else
				{
					cout << ", " << (*it)[i];
				}
			}
			cout << ")" << endl;
		}
		else
		{
			cout << "Pour " << (*it)[4] << " gallons from ";
			switch ((*it)[3])
			{
				case (1):
					cout << "C to A. (";
					break;
				case (2):
					cout << "B to A. (";
					break;
				case (3):
					cout << "C to B. (";
					break;
				case (4):
					cout << "A to B. (";
					break;
				case (5):
					cout << "B to C. (";
					break;
				case (6):
					cout << "A to C. (";
					break;
			}
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
				{
					cout << (*it)[i];
				}
				else
				{
					cout << ", " << (*it)[i];
				}
			}
			cout << ")" << endl;
		}
	}
}

//Check case on user input into command line
bool parseArg(vector<int> &jarSizes, vector<int> &target)
{
	int counter(0);
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
	vector<int> curr(5);
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
	if (!(parseArg(jarSizes, target)))
	{
		return 1;
	}
	curr[2] = jarSizes[2];
	vector< vector<int> > paths = BFS(curr, jarSizes, target);
	if (paths.size() <= 1)
	{
		cout << "No solution." << endl;
	}
	else
	{
		displayPath(paths);
	}
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
	/*
	Display Test
	curr[2] = jarSizes[2];
	queue< vector<int> > searches;
	searches.push(curr);
	BFS_helper(curr, jarSizes, target, visited, searches);
	vector< vector<int> > paths;
	vector<int> way;
	way.push_back(0);
	way.push_back(0);
	way.push_back(8);
	paths.push_back(way);
	way.clear();
	way.push_back(1);
	way.push_back(0);
	way.push_back(2);
	way.push_back(1);
	way.push_back(1);
	paths.push_back(way);
	cout << endl;
	displayPath(paths);
	*/
	
	/*
	vector< vector<int> > path = BFS(curr, jarSizes, target, visited, searches);
	if (path.size <= 0)
	{
		cout << "No solution." << endl;
		return 1;
	}
	displayPath(path);
	*/
	return 0;
}