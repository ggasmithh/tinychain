#ifndef BLOCK_H
#define BLOCK_H
#pragma once
#include <string>
#include <functional>
#include <chrono>
#include <vector>

using namespace std;

class Block {
public:
	int index;
	int timestamp;
	vector<char> data;
	string previous_block_hash;
	string block_hash;
	
	Block(int index, vector<char> data, string previous_block_hash): index(index), data(data) {	
		timestamp = chrono::system_clock::now().time_since_epoch().count();

		hash<string> hasher;
		block_hash = hasher(to_string(index) + " " + to_string(timestamp) + " " + string(data.begin(), data.end()) + " " + previous_block_hash);
	}
};


#endif