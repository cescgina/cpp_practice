#include <string>
#include <iostream>
#include <cstring>

int count_occurrences(const std::string& str, const std::string & search){
    int oc=0;
    std::string::size_type pos=0;
    while (pos < str.size()-1){
        pos = str.find(search, pos);
        if (pos != std::string::npos) oc++;
        else break;
        pos++;
    }
    return oc;
}

int count_occurrences_cstyle(const char* str, const char* search){
    int oc=0, size_str=strlen(str), size_search=strlen(search), match_sz=0;
    for (int i=0; i<size_str; i++){
        match_sz = 0;
        for (int j=0; j<size_search; j++){
            if (str[i+j] == search[j]) match_sz++;
        }
        if (match_sz == size_search) oc++;
    }
    return oc;
}

int main(){
    std::string haystack="xabaacbaxabb";
    std::cout << count_occurrences(haystack, "ab") << std::endl;
    char chaystack[]="xabaacbaxabb";
    char cneedle[] = "ab";
    std::cout << count_occurrences_cstyle(chaystack, cneedle) << std::endl;
}
