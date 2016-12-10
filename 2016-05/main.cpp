#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <openssl/md5.h>

constexpr std::uint8_t PASSWORD_LENGTH = 8;

std::string calculatePassword(std::string key) {
	std::stringstream password;
	std::uint64_t salt = 0;
	while (true) {
		std::string saltedKey = key + std::to_string(salt);
		unsigned char digest[16];
		MD5(reinterpret_cast<const unsigned char*>(saltedKey.data()), saltedKey.length(), digest);
		if (0 == (digest[0] | digest[1] | (digest[2] >> 4))) {
			password << std::hex << (digest[2] & 0x0FU);
			if (password.str().length() == PASSWORD_LENGTH) {
				return password.str();
			}
		}
		++salt;
	}
}

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::string line;
	std::getline(input, line);
	std::cout << calculatePassword(line) << std::endl;
	return 0;
}
