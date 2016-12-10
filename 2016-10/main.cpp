#include <fstream>
#include "bots.h"

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::string line;
	Factory factory;
	while (std::getline(input, line)) {
		std::cout << line << std::endl;
		factory.execute(line);
	}
	return 0;
}
