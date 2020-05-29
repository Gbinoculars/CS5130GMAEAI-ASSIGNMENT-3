#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include "PathFinding.h"


int main()
{
    std::string inputDir;
    std::cout << "Input the name of input file: ";
    std::cin >> inputDir;
   
    //call openJsonF function
    std::vector<std::vector<int>> arr = openJsonF(inputDir);
    //extract destination coodinate 
    if (!arr.empty()) {
        std::string outputDir;
        std::cout << "Input the name of output file: ";
        std::cin >> outputDir;
        std::vector<int> destinationNode = arr[arr.size() - 1];
        //delete destination coodiante from arr
        arr.pop_back();
        //extract start coodiante 
        std::vector<int> startNode = arr[arr.size() - 1];
        //delete start coodiante
        arr.pop_back();
        //call pathFind function then call writeJsonF function
        writeJsonF(pathFind(arr, startNode, destinationNode),outputDir);
    }
    else {
        std::cout << "file is empty or could not be found" << std::endl;
    }
    return 0;
}
