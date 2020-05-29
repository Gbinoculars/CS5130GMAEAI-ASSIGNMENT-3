#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include "PathFinding.h"


//struct Node {
//	int x;
//	int y;
//	int distance;
//	int preX;
//	int preY;
//	int totalCost;
//	int basicCost;
//}; 

//int countFCost(Node currentNode, Node start, Node destination);
//bool judge(Node nextNode, std::vector<std::vector<int>> evaluatedNode, std::vector<std::vector <int>> arr);
//int countTotalCost(Node start, Node destination, Node nextNode);
//std::vector<std::vector<int>> printPath(std::vector<std::vector<Node>> path,Node start, Node destination);
//int findMinCost(std::vector<Node> waitForEvaluate);

// function of pathFind
std::vector<std::vector<int>> pathFind(std::vector<std::vector <int>> arr, std::vector<int> startNode, std::vector<int> destinationNode) {
	
	int numX = arr.size();
	int numY = arr[0].size();
	//create a vector is used to hold the nodes which wait evaluate
	std::vector<Node>waitForEvaluate;
	//create a vector is used to hold the nodes which were evaluated 
	std::vector<std::vector<int>> evaluatedNode(numX,std::vector<int>(numY,0));
	Node initial;
	//create a vector is used to hold the path which is found
	std::vector<std::vector<Node>> path(numX, std::vector<Node>(numY,initial));
	//create a start node
	Node start;
	//initial the start node
	start.x = startNode[0];
	start.y = startNode[1];
	start.distance = arr[start.x][start.y];
	start.basicCost = 0;
	path[start.x][start.y] = start;
	//create a destination node
	Node destination;
	//initial the destination node
	destination.x = destinationNode[0];
	destination.y = destinationNode[1];
	destination.distance = arr[start.x][start.y];
	//the four direstion can move to
	int moveDirectX[] = { 1,-1,0,0 };
	int moveDirectY[] = { 0,0,1,-1 };
	//create a current node
	Node currentNode;
	//add start to the vector of waiting for evaluate
	waitForEvaluate.insert(waitForEvaluate.begin(),start);
	//set the start node as evaluated 
	evaluatedNode[start.x][start.y] = 1;

	//traverse the vector of waiting for evaluate
	while (!waitForEvaluate.empty()) {
		//call the function of findMinCost to find the min cost node in the vector
		int minIndex = findMinCost(waitForEvaluate);
		//set the current node which wait for evaluate as the min cost node
		currentNode = waitForEvaluate[minIndex];
		//is the current node destination?
		if (currentNode.x == destination.x && currentNode.y == destination.y) {
			break;
		}
		//delete the current node from vector of waitForEvaluate
		waitForEvaluate.erase(waitForEvaluate.begin() + minIndex);
		//set current node as evaluated
		evaluatedNode[currentNode.x][currentNode.y] = 1;

		//find the four next node
		for (int i = 0; i < 4; i++) {
			//create a next node
			Node nextNode;
			nextNode.x = currentNode.x + moveDirectX[i];
			nextNode.y = currentNode.y + moveDirectY[i];
			
			//judge the next node whether or not is legal
			if (judge(nextNode, evaluatedNode, arr)) {
				//create a bool to judge the nextnode whether or not in the vector of waiting for evalate
				bool isInWaitList = false;
				//traverse the vector of waitForEvaluate
				for (int i = 0; i < waitForEvaluate.size(); i++) {
					if (nextNode.x == waitForEvaluate[i].x && nextNode.y == waitForEvaluate[i].y) {
						isInWaitList = true;
						nextNode = waitForEvaluate[i];
						break;
					}
				}
				nextNode.distance = arr[nextNode.x][nextNode.y];
				//call the function to count the cost of next node
				int hueristicCost = countHeuristicCost(start, destination, nextNode);
				
				//set the property of next node
				//for the node was added into waitlist
				if(isInWaitList){
					//count the cost of moving from nextNode to start
					int throughCurrentbasicCost = nextNode.distance*(abs(nextNode.x-start.x)+abs(nextNode.y-start.y)) + currentNode.basicCost;
					//if the cost of moving from start 
					//through current node to next node shorter than previous path 
					if (nextNode.basicCost > throughCurrentbasicCost) {
						//std::cout << nextNode.x << "," << nextNode.y << "\n";
						//std::cout << currentNode.x << "," << currentNode.y << "\n";
						nextNode.totalCost = hueristicCost + throughCurrentbasicCost;
						nextNode.basicCost = throughCurrentbasicCost;
						nextNode.preX = currentNode.x;
						nextNode.preY = currentNode.y;
						//nextNode.distance = arr[nextNode.x][nextNode.y];
					}
				}
				// for the node was not added in waitlist
				if (!isInWaitList) {
					int nextBasicCost = currentNode.basicCost + nextNode.distance * (abs(nextNode.x - start.x) + abs(nextNode.y - start.y));
					nextNode.totalCost = nextBasicCost + hueristicCost;
					nextNode.basicCost = nextBasicCost;
					nextNode.preX = currentNode.x;
					nextNode.preY = currentNode.y;
					path[nextNode.x][nextNode.y] = nextNode;
					//add next node to vector of waiting for evaluate
					waitForEvaluate.insert(waitForEvaluate.begin(), nextNode);
				}
				//int totalCost = countTotalCost(start, destination, nextNode);
				//nextNode.totalCost = totalCost;
				//evaluatedNode[nextNode.x][nextNode.y] = 1;
				
			}
		}
	}
	return printPath(path,start,destination);
}

//function of find the min cost node in the vector of waiting for evaluate 
int findMinCost(std::vector<Node> waitForEvaluate) {
	int minTotalCost = waitForEvaluate[0].totalCost;
	int minIndex = 0;
	//traverse the vector 
	for (int i = 0; i < waitForEvaluate.size(); i++) {
		if (waitForEvaluate[i].totalCost < minTotalCost) {
			minTotalCost = waitForEvaluate[i].totalCost;
			minIndex = i;
		}
	}
	//return the index of min cost node
	return minIndex;
}

//function of judge next node
bool judge(Node nextNode,std::vector<std::vector<int>> evaluatedNode, std::vector<std::vector <int>> arr) {
	//if the next node out of map
	if (nextNode.x < 0 || nextNode.y < 0) {
		return false;
	}
	else if (nextNode.x > arr.size() - 1 || nextNode.y > arr[nextNode.x].size() - 1) {
		return false;
	}
	//if the next node was evaluated
	else if (evaluatedNode[nextNode.x][nextNode.y] == 1) {
		return false;
	}
	//if the tile of the map cannot move on
	else if (arr[nextNode.x][nextNode.y] == 0) {
		return false;
	}
	else {
		return true;
	}
}

//the function of count heuristic cost
int countHeuristicCost(Node start, Node destination, Node nextNode) {
	//int basicCost;
	int heuristicCost;
	//int totalCost;
	//use Manhattan distance to count the cost 
	//basicCost = nextNode.distance * (abs(nextNode.x - currentBasicCost) + abs(nextNode.y - currentBasicCost)) + currentBasicCost;
	heuristicCost = nextNode.distance * (abs(nextNode.x - destination.x) + abs(nextNode.y - destination.y)) ;
	//totalCost =  basicCost + heuristicCost;
	//create a array to hold three values of cost 
	//std::vector<int>costList = { basicCost,heuristicCost,totalCost};

	return heuristicCost;
}

//the function of extract final path track from the path map and print them
std::vector<std::vector<int>> printPath(std::vector<std::vector<Node>> path, Node start,Node destination) {
	//create a vector to hold the path track
	std::vector<std::vector<int>> finalPathTrack;
	int x = destination.x;
	int y = destination.y;
	int buffer;
	while (1) {
		std::cout << "[" << path[x][y].x << "," << path[x][y].y << "]" << "\n";
		std::vector<int> coodinate(2, 0);
		coodinate[0] = path[x][y].x;
		coodinate[1] = path[x][y].y;
		finalPathTrack.insert(finalPathTrack.begin(), coodinate);
		if (x == start.x && y == start.y) {
			break;
		}
		buffer = path[x][y].preY;
		x = path[x][y].preX;
		y = buffer;
		
	}
	return finalPathTrack;
}