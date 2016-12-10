#include <fstream>
#include <iostream>
#include <sstream>
#include "decompress.h"

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::stringstream output;
	int decompressedLength = 0;
	Decompressor decompressor;
	while (decompressor.run(input, output)) {
		decompressedLength += output.str().length();
		output.str(std::string());
	}
	decompressedLength += output.str().length();
	std::cout << decompressedLength << std::endl;
	return 0;
}
