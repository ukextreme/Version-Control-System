#include "commitNodeList.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include <vector>
using namespace std;
namespace fs = filesystem;

// Utility Functions
string gen_random(const int len) {
    srand(time(NULL) * getpid());
    static const char alphanum[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

string get_time() {
    time_t t = time(0);
    tm* now = localtime(&t);
    return to_string(now->tm_year + 1900) + "/" +
           to_string(now->tm_mon + 1) + "/" +
           to_string(now->tm_mday) + " " +
           to_string(now->tm_hour) + ":" +
           to_string(now->tm_min);
}

// commitNode implementation
commitNode::commitNode() { next = NULL; }

commitNode::commitNode(string id, string msg) {
    commitID = id;
    commitMsg = msg;
    next = NULL;
    createCommitNode();
}

commitNode::commitNode(string id) {
    commitID = id;
    next = NULL;
    checkNextCommitId();
}

void commitNode::createCommitNode() {
    fs::create_directories(".git/commits/" + commitID);
    ofstream write(".git/commits/" + commitID + "/commitInfo.txt");
    write << "1." << commitID << "\n"
          << "2." << commitMsg << "\n"
          << "3." << get_time() << "\n";

    fs::copy(".git/staging_area", ".git/commits/" + commitID + "/Data",
             fs::copy_options::recursive | fs::copy_options::update_existing);
}

void commitNode::revertCommitNode(string fromHash) {
    fs::create_directories(".git/commits/" + commitID + "/Data");
    fs::copy(".git/commits/" + fromHash + "/Data",
             ".git/commits/" + commitID + "/Data",
             fs::copy_options::recursive);
    ofstream write(".git/commits/" + commitID + "/commitInfo.txt");
    write << "1." << commitID << "\n"
          << "2." << commitMsg << "\n"
          << "3." << get_time() << "\n";
}

void commitNode::readNodeInfo() {
    ifstream file(".git/commits/" + commitID + "/commitInfo.txt");
    string line;
    while (getline(file, line)) {
        if (line[0] == '1') setCommitID(line.substr(2));
        if (line[0] == '2') setCommitMsg(line.substr(2));
    }
}

void commitNode::writeNextCommitID(string id) {
    nextCommitID = id;
    ofstream out(".git/commits/" + commitID + "/nextCommitInfo.txt");
    out << id;
}

string commitNode::checkNextCommitId() {
    ifstream in(".git/commits/" + commitID + "/nextCommitInfo.txt");
    if (in) getline(in, nextCommitID);
    return nextCommitID;
}

string commitNode::getNextCommitId() { return nextCommitID; }
string commitNode::getCommitID() { return commitID; }
string commitNode::getCommitMsg() { return commitMsg; }
void commitNode::setCommitID(string id) { commitID = id; }
void commitNode::setCommitMsg(string msg) { commitMsg = msg; }
void commitNode::setNext(commitNode* n) { next = n; }
commitNode* commitNode::getNext() { return next; }
void commitNode::setNextCommitID(string id) { nextCommitID = id; }

// commitNodeList implementation
bool commitNodeList::checkHead() {
    return fs::exists(".git/commits/0x1111");
}

commitNodeList::commitNodeList() {
    HEAD = NULL;
    TAIL = NULL;
    if (checkHead()) HEAD = new commitNode("0x1111");
}

void commitNodeList::addOnTail(string msg) {
    if (!checkHead()) {
        HEAD = new commitNode("0x1111", msg);
    } else {
        string newID = gen_random(8);
        commitNode* curr = HEAD;
        while (curr) {
            string nextID = curr->checkNextCommitId();
            if (nextID.empty()) {
                commitNode* newNode = new commitNode(newID, msg);
                curr->writeNextCommitID(newID);
                break;
            } else {
                curr = new commitNode(nextID);
            }
        }
    }
}

void commitNodeList::revertCommit(string hash) {
    if (!checkHead()) {
        cout << "Nothing to revert.\n";
        return;
    }

    bool found = false;
    string newID = gen_random(8);
    commitNode* curr = HEAD;
    commitNode* target = nullptr;

    while (curr) {
        if (curr->getCommitID() == hash) {
            target = curr;
            found = true;
        }

        string nextID = curr->checkNextCommitId();
        if (nextID.empty()) {
            if (found) {
                target->readNodeInfo();
                commitNode* newNode = new commitNode();
                newNode->setCommitID(newID);
                newNode->setCommitMsg(target->getCommitMsg());
                newNode->revertCommitNode(target->getCommitID());
                curr->writeNextCommitID(newID);
                cout << "Reverted to commit " << hash << endl;
            }
            break;
        } else {
            curr = new commitNode(nextID);
        }
    }

    if (!found) {
        cout << "No such commit found.\n";
    }
}

void commitNodeList::printCommitList() {
    commitNode* curr = HEAD;
    while (curr) {
        string path = ".git/commits/" + curr->getCommitID() + "/commitInfo.txt";
        ifstream file(path);
        string line;
        while (getline(file, line)) {
            if (line[0] == '1') cout << "Commit ID:   " << line.substr(2) << endl;
            if (line[0] == '2') cout << "Message:     " << line.substr(2) << endl;
            if (line[0] == '3') cout << "Timestamp:   " << line.substr(2) << endl;
        }
        cout << "===========================\n";
        string nextID = curr->checkNextCommitId();
        if (nextID.empty()) break;
        curr = new commitNode(nextID);
    }
}

commitNode* commitNodeList::getHead() { return HEAD; }
commitNode* commitNodeList::getTail() { return TAIL; }
void commitNodeList::setHead(commitNode* h) { HEAD = h; }
void commitNodeList::setTail(commitNode* t) { TAIL = t; }
