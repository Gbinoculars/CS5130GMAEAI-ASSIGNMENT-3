/*!
* \file PathFinding.h
* \Assignment 2 of Game AI: PathFinding 
*
*
* \Jiaqiang Guo E-mail:guo.jiaqia@husky.neu.edu
* \2,FEB,2020
*/

#pragma once
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>

//struct of Node
struct Node {
	int x; 
	int y; 
	int distance; 
	int preX; //the x coodinate of parent Node
	int preY; //the y coodiante of parent Node
	int totalCost; 
	int basicCost;
};

/*
brief judge the neighbor Node whether or not is legal 
return bool
*/
bool judge(Node nextNode, std::vector<std::vector<int>> evaluatedNode, std::vector<std::vector <int>> arr);
/*
brief count the cost of moving from next node to destination, 
return a int
*/
int countHeuristicCost(Node start, Node destination, Node nextNode);
/*
brief print path from start to destination
return a 2D vector
*/
std::vector<std::vector<int>> printPath(std::vector<std::vector<Node>> path, Node start, Node destination);
/*
brief find the node with min cost from the vector of waitForEvaluate
return the index of the node
*/
int findMinCost(std::vector<Node> waitForEvaluate);
/*
brief open the map of path finding
return a 2D vector
*/
std::vector<std::vector<int>> openJsonF(std::string inputDir);
/*
brief A*algorithm of pathfinding
return a 2D vector
*/
std::vector<std::vector<int>> pathFind(std::vector<std::vector <int>> arr, std::vector<int> startNode, std::vector<int> destinationNode);
/*
brief write the path track to json file
return void
*/
void writeJsonF(std::vector<std::vector<int>>finalPathTrack, std::string outputDir);
