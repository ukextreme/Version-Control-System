#pragma once
#include <string>

std::string gen_random(const int len);
std::string get_time();

class commitNode {
    std::string commitID, commitMsg, nextCommitID;
    commitNode* next;

    void createCommitNode();

public:
    commitNode();
    commitNode(std::string commitID, std::string commitMsg);
    commitNode(std::string commitId);

    void revertCommitNode(std::string fromHash);
    void readNodeInfo();
    void setCommitID(std::string id);
    void setCommitMsg(std::string msg);
    void setNext(commitNode* node);
    void setNextCommitID(std::string id);
    void writeNextCommitID(std::string id);
    std::string getCommitID();
    std::string getCommitMsg();
    commitNode* getNext();
    std::string checkNextCommitId();
    std::string getNextCommitId();
};

class commitNodeList {
    commitNode* HEAD;
    commitNode* TAIL;

    bool checkHead();

public:
    commitNodeList();
    void setHead(commitNode* node);
    void setTail(commitNode* node);
    commitNode* getHead();
    commitNode* getTail();
    void addOnTail(std::string msg);
    void revertCommit(std::string commitHash);
    void printCommitList();
};
