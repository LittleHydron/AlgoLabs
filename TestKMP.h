#ifndef ALGOLABS_TESTKMP_H
#define ALGOLABS_TESTKMP_H

namespace test {
    enum statusCode{PASSED, FAILED};
    class TestResult;
    class TestKMP;
}

class test::TestKMP{
public:
    static TestResult testForRightness(std::string &data, std::string &pattern);
};

class test::TestResult{
private:
    statusCode result;
    double executionTime;
public:
    [[nodiscard]]double getExecutionTime() const {return executionTime;}
    TestResult(bool, double);
    void printLog(std::ofstream&);
};
#include "TestKMP.cpp"
#endif //ALGOLABS_TESTKMP_H
