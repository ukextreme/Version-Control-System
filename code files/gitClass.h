#pragma once
#include <string>

class gitClass {
public:
    void gitInit();
    void gitAdd();
    void gitAdd(std::string files[], int arrSize);
    void gitCommit(std::string msg);
    void gitRevert(std::string commitHash);
    void gitLog();
};
