#ifndef MAPS_H
#define MAPS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

bool processMap(const char mapName[], vector<vector<char>> &processedMap);
void renderMap(vector<vector<char>> processedMap);

#endif