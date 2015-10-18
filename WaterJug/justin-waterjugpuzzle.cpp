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
		curr[from] = curr[from] - (sizes[to] - curr[to]);
		curr[4] = sizes[to] - curr[to];
		curr[to] = sizes[to];
	}
	curr[3] = order;
	
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

// Use visit check if push onto queue or not
void BFS_helper(
		vector<int> curr, vector<int> &jarSizes, vector<int> &target, 
		vector< vector<bool> > &visitedJars, queue< vector<int> > &searches)
{
	vector< vector<int> > paths = getAdjacents(curr, jarSizes);

	for (vector< vector<int> >::iterator it = paths.begin(); it != paths.end(); ++it)
	{
		if (!(visitedJars[(*it)[0]][(*it)[1]]))
		{
			visitedJars[(*it)[0]][(*it)[1]] = true;
			//cout << visitedJars[(*it)[0]][(*it)[1]] << " " << (*it)[0] << " " << (*it)[1] << endl;
			searches.push(*it);
		}
	}
	//BFS_helper((*it), jarSizes, target, isVisited, searches, result);
	//searches.pop();
}

// TODO: Find way to break when equal or no solution
vector< vector<int> > BFS(vector<int> curr, vector<int> &jarSizes, vector<int> &target)
{
	vector< vector<int> > result;
	/*
	if (!(equal(curr.begin(), curr.begin() + 3, target.begin())))
	{
		BFS_helper(curr, jarSizes, target, visitedJars, searches, result);
	}
	*/
	if (equal(curr.begin(), curr.begin() + 3, target.begin()))	
	{
		result.push_back(curr);
	}
	else
	{
		queue< vector<int> > searches;
		vector< vector<bool> > visitedJars(jarSizes[0] + 1, vector<bool>(jarSizes[1] + 1));
		
		searches.push(curr);
		visitedJars[0][0] = true;
		//vector<int> first_search = searches.front();
		while ((!(searches.empty())) && (!(equal(searches.front().begin(), searches.front().begin() + 3, target.begin()))))
		{
			/*
			cout << "Current queue" << endl;
			for (vector<int>::iterator it = searches.front().begin(); it != searches.front().end(); ++it)
			{
				cout << *it << " ";
			}
			cout << endl;
			*/
			BFS_helper(searches.front(), jarSizes, target, visitedJars, searches);
			result.push_back(searches.front());
			searches.pop();
			//first_search = searches.front();
		}
		if (searches.size() > 0)
		{
			result.push_back(searches.front());
		}
		else
		{
			result.clear();
		}
	}
	/*
	for (vector< vector<int> >::iterator its = result.begin(); its != result.end(); ++its)
	{
		for (vector<int>::iterator it = (*its).begin(); it != (*its).end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << endl;
	*/
	
	return result;
}

//TODO: Find solution to find the correct path in the vec of vec<int>
// Getting bad allocation
vector< vector<int> > findShortestPath(vector< vector<int> > &paths)
{
	vector< vector<int> > rightPath;
	vector<int> it;
	
	while (paths.size() > 1)
	{
		rightPath.push_back(paths.back());
		it = paths.back();
		/*
		for (vector<int>::iterator its = it.begin(); its != it.end(); ++its)
		{
			cout << *its << " ";
		}
		cout << endl;
		*/
		paths.pop_back();
		switch (it[3])
		{
			case (1):
				it[2] += it[4];
				it[0] -= it[4];
				break;
			case (2):
				it[1] += it[4];
				it[0] -= it[4];
				break;
			case (3):
				it[2] += it[4];
				it[1] -= it[4];
				break;
			case (4):
				it[0] += it[4];
				it[1] -= it[4];
				break;
			case (5):
				it[1] += it[4];
				it[2] -= it[4];
				break;
			case (6):
				it[0] += it[4];
				it[2] -= it[4];
				break;
		}
		/*
		for (vector<int>::iterator its = it.begin(); its != it.end(); ++its)
		{
			cout << *its << " ";
		}
		cout << endl << endl;
		*/
		
		while (!(equal(paths.back().begin(), paths.back().begin() + 2, it.begin())))
		{
			paths.pop_back();
		}
	}
	/*
	for (vector< vector<int> >::iterator it = paths.end(); it != paths.begin();)
	{
		rightPath.push_back((*it));
		
		switch ((*it)[3])
		{
			case (1):
				(*it)[2] += (*it)[4];
				(*it)[0] -= (*it)[4];
			case (2):
				(*it)[1] += (*it)[4];
				(*it)[0] -= (*it)[4];
			case (3):
				(*it)[2] +=  (*it)[4];
				(*it)[1] -= (*it)[4];
			case (4):
				(*it)[0] += (*it)[4];
				(*it)[1] -= (*it)[4];
			case (5):
				(*it)[1] += (*it)[4];
				(*it)[2] -= (*it)[4];
			case (6):
				(*it)[0] += (*it)[4];
				(*it)[2] -= (*it)[4];
		}
		
		for (vector< vector<int> >::iterator its = paths.begin(); its != paths.end(); ++its)
		{
			if ((((*its)[0]) == ((*it)[0])) && (((*its)[1]) == ((*it)[1])))
			{
				(*it) = (*its);
				break;
			}
		}
		*/
		rightPath.push_back(paths.front());
	/*
	for (vector< vector<int> >::iterator its = rightPath.begin(); its != rightPath.end(); ++its)
	{
		for (vector<int>::iterator it = (*its).begin(); it != (*its).end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	*/
	return rightPath;
}

//Print path
void displayPath(vector< vector<int> > &way)
{
	for (vector< vector<int> >::reverse_iterator it = way.rbegin(); it != way.rend(); ++it)
	{
		if (it == way.rbegin())
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
			if ((*it)[4] <= 1)
			{
				cout << "Pour " << (*it)[4] << " gallon from ";
			}
			else
			{
				cout << "Pour " << (*it)[4] << " gallons from ";
			}
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
	if (parseArg(jarSizes, target))
	{
		vector<int> curr(5);
		curr[2] = jarSizes[2];
		vector< vector<int> > paths = BFS(curr, jarSizes, target);
		if (paths.size() <= 0)
		{
			cout << "No solution." << endl;
			return 0;
		}
		vector< vector<int> > path = findShortestPath(paths);
		displayPath(path);
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