#include <bits/stdc++.h>
#include "TestKMP.h"

using namespace std;

tuple<string, string> generateWorstCaseOfLength(int textLength, int patternLength){
    string pattern;
    while(patternLength > 1){
        pattern += 'a';
        -- patternLength;
    }
    pattern += 'b';
    string text;
    while(text.length() + pattern.length() <= textLength){
        text += pattern;
    }
    while(text.length() < textLength){
        text += 'a';
    }
    return {text, pattern};
}

tuple<string, string> generateBestCaseOfLength(int textLength, int patternLength){
    string pattern = "a";
    patternLength --;
    while(patternLength --){
        pattern += char(int(pattern.back()) + 1);
    }
    string text;
    while(textLength --){
        text += 'b';
    }
    return {text, pattern};
}

tuple<string, string> generateRandomTest(int textLength, int patternLength, function<int()> &randInt){
    string text;
    while(textLength --){
        text += char('a' + (randInt()) % 26);
    }
    string pattern;
    while(patternLength --){
        pattern += char('a' + (randInt()) % 26);
    }
    return {text, pattern};
}

int main(){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> uniformDistr(0, 100001);
    function < int() > randInt = ([&]()->int{return uniformDistr(mt);});
    double worstAvg = 0, bestAvg = 0, randAvg = 0;
    int numberOfTests = 20;
    for (int tst = 0; tst < numberOfTests; ++ tst){
        int textLength = randInt();
        int patternLength = randInt()%textLength + 1;
        string pattern, text;
        tie(text, pattern) = generateBestCaseOfLength(textLength, patternLength);
        bestAvg += (test::TestKMP::testForRightness(text, pattern)).getExecutionTime();
        tie(text, pattern) = generateWorstCaseOfLength(textLength, patternLength);
        worstAvg += (test::TestKMP::testForRightness(text, pattern)).getExecutionTime();
        tie(text, pattern) = generateRandomTest(textLength, patternLength, randInt);
        randAvg += (test::TestKMP::testForRightness(text, pattern)).getExecutionTime();
    }
    cout << fixed << setprecision(6);
    cout << "Best case average time:   " << (bestAvg / (double(numberOfTests))) / CLOCKS_PER_SEC << "s\n";
    cout << "Worst case average time:  " << (worstAvg / (double(numberOfTests))) / CLOCKS_PER_SEC << "s\n";
    cout << "Random test average time: " << (randAvg / (double(numberOfTests))) / CLOCKS_PER_SEC << "s\n";
    return 0;
}