#include "block.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_DATA_CHUNK_SZ = 2;

Block next_block(Block *previous_block, char* data, int data_size) {
	int new_index = previous_block->index + 1;
	char* sized_data;
	sized_data = new char[data_size];

	memset(sized_data, 0, sizeof(sized_data));

	for (int i = 0; i < data_size; i++) {
		sized_data[i] = data[i];
	}

	return Block(new_index, sized_data, previous_block->block_hash);
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
	char buffer[MAX_DATA_CHUNK_SZ];
	int buffer_size = sizeof(buffer) / sizeof(buffer[0]);

	ifstream in_file(argv[1], ios::in | ios::binary);

	file_size = get_file_size(in_file);
	chunk_size = get_next_chunk_size(0, file_size);

	// this may not be necessary
	memset(&buffer, 0, sizeof(buffer));

	Block genesis(-1, buffer, "");
	vector<Block> blockchain = { genesis };

	int next_chunk_size = MAX_DATA_CHUNK_SZ;
	// Putting data into the blockchain
	for (int i = 0; i < file_size; i += next_chunk_size) {
		next_chunk_size = get_next_chunk_size(i, file_size);
		in_file.read(buffer, next_chunk_size);
		Block new_block = next_block(&blockchain.back(), buffer, next_chunk_size);
		blockchain.push_back(new_block);
	}

	// Getting data out of the blockchain
	ofstream output("output.txt", ios_base::trunc | ios::binary | ios::out);
	for (int i = 1; i < blockchain.size(); i++) {
		output << blockchain[i].data;
	}

	output.close();

	return 0;
}

