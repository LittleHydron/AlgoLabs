#include "KnuthMorrisPratt.h"

test::TestResult test::TestKMP::testForRightness(std::string &data, std::string &pattern) {
    auto startTime = (double)clock();
    int KMP = KMP::KnuthMorrisPratt::numberOfReps(data, pattern);
    auto finishTime = (double)clock();
    auto n = (int)data.length();
    auto m = (int)pattern.length();
    for (int i=0; i+m-1 < n; ++ i){
        int j = 0;
        while(j < m && data[i+j] == pattern[j]) ++ j;
        if (j == m) -- KMP;
    }
    return {KMP == 0, finishTime - startTime};
}

test::TestResult::TestResult(bool ok, double time) {
    this->result = (ok ? PASSED : FAILED);
    this->executionTime = time;
}

void test::TestResult::printLog(std::ofstream &logFile) {
    logFile << "Test worked for " << this->executionTime / CLOCKS_PER_SEC << "s and ";
    if (this->result == PASSED){
        logFile << "passed successfully!\n";
    }else{
        logFile << "failed enormously!\n";
    }
}
