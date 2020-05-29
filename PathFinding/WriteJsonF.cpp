#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include "PathFinding.h"

void writeJsonF(std::vector<std::vector<int>> finalPathTrack, std::string outputDir) {
	Json::Value root;
	std::ofstream ofs;
	ofs.open(outputDir);
	//ofs << "[";
	for (int i = 0; i < finalPathTrack.size(); i++) {
	std::string str = "[" + std::to_string(finalPathTrack[i][0]) + "," + 
			std::to_string(finalPathTrack[i][1]) + "]";
	Json::Value vct;
	//	ofs << "[" << finalPathTrack[i][0] << "," << finalPathTrack[i][1] << "]" << "\n";
	vct[0] = finalPathTrack[i][0];
	vct[1] = finalPathTrack[i][1];
	//	//std::cout<<str;
	//	//int vctInt[2] = { ,};
	//	//std::cout << vct;
	root.append(str);
	}
	////Json::StreamWriterBuilder sw;
	////std::ofstream ofs;
	////ofs.open("Solusion1.json");
	ofs << root;
	//ofs << "]";
	ofs.close();
	//Json::Value root;
	//Json::StreamWriterBuilder builder;
	//const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	//writer->write(root);
	//return EXIT_SUCCESS;
}