int g_x { 5 };

int main()
{
    constexpr int& ref1 { g_x }; // ok, can bind to global

    static int s_x { 6 };
    constexpr int& ref2 { s_x }; // ok, can bind to static local

    int x { 6 };
    // constexpr int& ref3 { x };
    // compile error: can't bind to non-static object beacuse it's address known at compile time

    return 0;
}