#pragma once

namespace AoC {
    class Vm {
    public:
        int read(char reg) {
            return a;
        }

        void load(std::stringstream& stream) {
        }

        void execute() {
            a = 1;
        }

    private:
        int a{0};
    };
}
