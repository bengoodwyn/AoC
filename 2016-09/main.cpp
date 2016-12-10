#include <fstream>
#include <iostream>
#include <sstream>
#include "decompress.h"

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::stringstream output;
	Decompressor decompressor;
	while (decompressor.run(input, output)) {
	}
	std::cout << output.str().length() << std::endl;
	return 0;
}
