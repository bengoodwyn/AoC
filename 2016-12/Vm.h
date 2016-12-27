#pragma once

#include <array>
#include <cctype>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <vector>

namespace AoC {
    class Vm {
    public:
        Vm() {
            microcode["inc"] = [this](std::istream& stream, int ip) -> int {
                std::string arg;
                stream >> arg;
                ++registers[arg[0]];
                return ip + 1;
            };

            microcode["dec"] = [this](std::istream& stream, int ip) -> int {
                std::string arg;
                stream >> arg;
                --registers[arg[0]];
                return ip + 1;
            };

            microcode["jnz"] = [this](std::istream& stream, int ip) -> int {
                std::string arg_cmp;
                stream >> arg_cmp;
                int value;
                if (std::isalpha(arg_cmp.at(0))) {
                    value = read(arg_cmp.at(0));
                } else {
                    value = std::stoi(arg_cmp);
                }
                if (0 != value) {
                    std::string arg_distance;
                    stream >> arg_distance;
                    return ip + std::stoi(arg_distance);
                } else {
                    return ip + 1;
                }
            };

            microcode["cpy"] = [this](std::istream& stream, int ip) -> int {
                std::string arg_src;
                std::string arg_tgt;
                stream >> arg_src >> arg_tgt;
                int value;
                if (std::isalpha(arg_src.at(0))) {
                    value = read(arg_src.at(0));
                } else {
                    value = std::stoi(arg_src);
                }
                registers[arg_tgt.at(0)] = value;
                return ip + 1;
            };
        }

        int read(char reg) {
            return registers[reg];
        }

        void load(std::istream& stream) {
            std::string instruction;
            while (!stream.eof()) {
                std::getline(stream, instruction);
                if (instruction.length() > 0) {
                    instructions.push_back(instruction);
                }
            }
        }

        void execute() {
            int ip = 0;
            while (ip < instructions.size()) {
                ip = execute(ip);
            }
        }

    private:
        int execute(int ip) {
            //printRegisters("before");
            //std::cerr << "\t" << ip << " " << instructions[ip] << std::endl;
            std::stringstream instruction(instructions[ip]);
            std::string opcode;
            instruction >> opcode;
            auto function = microcode.at(opcode);
            auto newip = function(instruction, ip);
            //printRegisters("after");
            return newip;
        }

        void printRegisters(std::string prefix) {
            std::cerr << prefix << ": " << registers['a'] << " " << registers['b'] << " " << registers['c'] << " "
                << registers['d'] << std::endl;
        }
        std::vector<std::string> instructions;
        std::array<int, 256> registers{{0}};
        std::unordered_map<std::string, std::function<int(std::istream&, int)>> microcode;
    };
}
