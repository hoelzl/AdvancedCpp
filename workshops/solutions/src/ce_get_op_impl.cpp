#include <cstdio>
#include <functional>
#include <stdexcept>

// Compile, e.g., with x86-64-clang 12.0.1 -std=c++2a -O3

enum class Op { add, mul };

std::function<int(int, int)> get_op_impl_1(Op op)
{
    switch (op) {
    case Op::add: return [](int m, int n) { return m + n; };
    case Op::mul: return [](int m, int n) { return m * n; };
    }
}

inline auto get_op_impl_2(Op op)
{
    return [op](int m, int n) {
        switch (op) {
        case Op::add: return m + n;
        case Op::mul: return m * n;
        }
    };
}

void print_result(Op op, int m, int n) {
    std::printf("%d\n", get_op_impl_2(op)(m, n));
}

int main() {
    std::printf("%d\n", get_op_impl_1(Op::add)(2, 3));
    std::printf("%d\n", get_op_impl_2(Op::add)(2, 3));
}