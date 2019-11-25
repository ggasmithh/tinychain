#include "block.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_DATA_CHUNK_SZ = 2;

Block next_block(Block *previous_block, vector<char> data, int data_size) {
	int new_index = previous_block->index + 1;

	return Block(new_index, data, previous_block->block_hash);
}

int get_file_size(ifstream &in_file) {
	
	int size;

	if (!in_file.is_open()) {
		return -1;
	}

	in_file.seekg(0, in_file.end);
	size = in_file.tellg();
	in_file.seekg(0, in_file.beg);

	return size;
}

int get_next_chunk_size(int current_file_position, int file_size) {
	return min(MAX_DATA_CHUNK_SZ, file_size - current_file_position);
}

int main(int, char **argv) {
	int file_size;
	int chunk_size;
	vector<char> buffer;

	ifstream in_file(argv[1], ios::in | ios::binary);
	//ifstream in_file("test.jpg", ios::in | ios::binary);

	file_size = get_file_size(in_file);
	chunk_size = get_next_chunk_size(0, file_size);

	Block genesis(-1, buffer , "");
	vector<Block> blockchain = { genesis };

	int next_chunk_size = MAX_DATA_CHUNK_SZ;
	// Putting data into the blockchain
	for (int i = 0; i < file_size; i += next_chunk_size) {
		next_chunk_size = get_next_chunk_size(i, file_size);
		buffer.resize(next_chunk_size);
		in_file.read(&buffer[0], next_chunk_size);
		Block new_block = next_block(&blockchain.back(), buffer, next_chunk_size);
		blockchain.push_back(new_block);
	}

	// Getting data out of the blockchain
	ofstream output("output.jpg", ios_base::trunc | ios::binary | ios::out);
	for (int i = 1; i < blockchain.size(); i++) {
		output << string(blockchain[i].data.begin(), blockchain[i].data.end());
	}

	output.close();

	return 0;
}

