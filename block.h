#ifndef BLOCK_H
#define BLOCK_H
#pragma once
#include <string>
#include <functional>
#include <chrono>

using namespace std;


class Block {
public:
	int index;
	int timestamp;
	char* data;
	string previous_block_hash;
	string block_hash;
	
	Block(int index, char* data, string previous_block_hash): index(index), data(data) {

		timestamp = chrono::system_clock::now().time_since_epoch().count();

		hash<string> hasher;
		block_hash = hasher(to_string(index) + " " + to_string(timestamp) + " " + string(data) + " " + previous_block_hash);
	}
};


#endif