#pragma once

namespace AoC {
    class Vm {
    public:
        int read(char reg) {
            return a;
        }

        void load(std::stringstream& stream) {
            std::string instruction;
            while (!stream.eof()) {
                std::getline(stream, instruction);
                instructions.push_back(instruction);
            }
        }

        void execute() {
            a = instructions.size();
        }

    private:
        std::vector<std::string> instructions;
        int a{0};
    };
}
