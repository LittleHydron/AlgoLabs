int KMP::KnuthMorrisPratt::numberOfReps(std::string& data, std::string& pattern) {
    int ans = 0;
    int pi[pattern.length()];
    pi[0] = 0;
    for (int i=1; i<pattern.length(); ++ i){
        int j = pi[i-1];
        while(j > 0 && pattern[j] != pattern[i]){
            j = pi[j-1];
        }
        if (pattern[i] == pattern[j]){
            pi[i] = j+1;
        }else{
            pi[i] = 0;
        }
    }
    int j = 0;
    for (char &i : data){
        while(j == pattern.length() || (j > 0 && pattern[j] != i)){
            j = pi[j-1];
        }
        if (i == pattern[j]){
            ++ j;
            if (j == pattern.length()){
                ++ ans;
            }
        }else{
            j = 0;
        }
    }
    return ans;
}
