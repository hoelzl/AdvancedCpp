constexpr auto max_lambda_1 = [](auto x, auto y) {
    return y < x ? x : y;
};

constexpr auto max_fun(auto x, auto y)
{
    return y < x ? x : y;
}

auto res1 = max_fun(3, 7);
auto res2 = max_lambda_1.operator()<int, int>(3, 7);
auto res3 = [](int x, int y) { return max_lambda_1(x, y);}(3, 7);

int f1(int x, int y) {
    return max_fun(x, y);
}

int f2(int x, int y) {
    return max_lambda_1(x, y);
}

int f3(int x, int y) {
    return [](int a, int b) {
        return max_lambda_1.operator()<int, int>(a, b);
    }(x, y);
}
