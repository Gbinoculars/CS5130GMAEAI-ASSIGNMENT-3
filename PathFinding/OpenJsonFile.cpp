#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include "PathFinding.h"

// open the map use a 2D vector to hold the map
std::vector<std::vector<int>> openJsonF(std::string inputDir) {
    
    Json::Value root;
    std::ifstream ifs;
    ifs.clear();
    ifs.open(inputDir);
    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
    }
    //if file = null return empty arr
    if (root.isNull()) {
        std::vector<std::vector<int>> empty;
        return empty;
    }

    Json::Value map = root["Map"];
    Json::Value start = root["Start"];
    Json::Value destination = root["Destination"];
    //startV hold the coodinate of start
    std::vector<int> startV(2, 0);
    startV[0] = start[0].asInt();
    startV[1] = start[1].asInt();
    //destinationV hold the coodinate of destination
    std::vector<int> destinationV(2, 0);
    destinationV[0] = destination[0].asInt();
    destinationV[1] = destination[1].asInt();
    int numrow = map.size();
    std::string string0 = map[0].asString();
    int numcol = string0.length();
    //arr hold the map
    std::vector<std::vector<int>> arr(numrow, std::vector<int>(numcol, 0));
    std::string currentRow;
    //change the map from type of Json velue to type of int
    for (int i = 0; i < (numrow); i++) {
        currentRow = map[i].asString();
        for (int i1 = 0; i1 < (numcol); i1++) {
            if ((currentRow[i1]) == 'X') {
                arr[i][i1] = 0;
            }
            else {
                arr[i][i1] = currentRow[i1] - '0';
            }
        }
    }
    int x = 0;
    int y = 0;
    //correct the coodinate.
    //uncorrect: arr[arr.size()][0] is coodinate [0,0]
    //after correct: arr[0][0] is coodinate[0][0]
    std::vector<std::vector<int>> rearr(numcol, std::vector<int>(numrow, 0));
    for (int xcoordinate = 0; xcoordinate < numcol; xcoordinate++) {
        for (int ycoordinate = numrow - 1; ycoordinate >= 0; ycoordinate--) {
            rearr[x][y] = arr[ycoordinate][xcoordinate];
            y++;
        }
        x++;
        y = 0;
    }
    //append coodinate of start to the rearr
    rearr.push_back(startV);
    //append coodinate of destination to the rearr
    rearr.push_back(destinationV);

    return rearr;
}
