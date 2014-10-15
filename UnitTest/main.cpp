# include <unittest++/UnitTest++.h>

class MyClass {
    public:
        double addition(double a, double b) {
            return a+b;
        }
};

TEST(MyMath) {
    MyClass my;
    CHECK(my.addition(3, 4) == 7);
}

int main() {
    return UnitTest::RunAllTests();
}
