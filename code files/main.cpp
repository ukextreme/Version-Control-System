#include <iostream>
#include "gitClass.h"
using namespace std;

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define END  "\033[0m"

int main(int argc, char *argv[]) {
    gitClass gitClassObj;

    if (argc >= 2) {
        string argument = string(argv[1]);

        if (argument == "init") {
            gitClassObj.gitInit();
            cout << GRN "git repository initialized successfully!" END << endl;
        }
        else if (argument == "add") {
            if (argc == 2) {
                cout << RED "Missing arguments!\nUse: git add <'.' | 'file_name'>" END << endl;
            } else if (argc == 3) {
                string arg2 = string(argv[2]);
                if (arg2 == ".") {
                    gitClassObj.gitAdd();
                } else {
                    string files[] = { arg2 };
                    gitClassObj.gitAdd(files, 1);
                }
            } else {
                string files[argc - 2];
                for (int i = 0; i < argc - 2; ++i) {
                    files[i] = string(argv[i + 2]);
                }
                gitClassObj.gitAdd(files, argc - 2);
            }
        }
        else if (argument == "commit") {
            if (argc == 4 && string(argv[2]) == "-m") {
                gitClassObj.gitCommit(string(argv[3]));
                cout << GRN "Files committed successfully" END << endl;
            } else {
                cout << RED "Usage: git commit -m \"<message>\"" END << endl;
            }
        }
        else if (argument == "revert") {
            if (argc == 3) {
                gitClassObj.gitRevert(string(argv[2]));
            } else {
                cout << RED "Usage: git revert <'HEAD'|'commit_hash'>" END << endl;
            }
        }
        else if (argument == "log") {
            gitClassObj.gitLog();
        }
        else {
            cout << RED "Invalid command!" END << endl;
        }

    } else {
        cout << YEL "Usage:\n"
             << "git init\n"
             << "git add <'.'|'file_name'>\n"
             << "git commit -m \"<message>\"\n"
             << "git revert <commit_hash>\n"
             << "git log" END << endl;
    }

    return 0;
}
