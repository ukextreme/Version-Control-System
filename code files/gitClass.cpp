#include "gitClass.h"
#include "commitNodeList.h"
#include <filesystem>
#include <iostream>

using namespace std;

commitNodeList list;

void gitClass::gitInit() {
    filesystem::create_directory(".git");
    filesystem::create_directory(".git/staging_area");
    filesystem::create_directory(".git/commits");
}

void gitClass::gitAdd() {
    const auto options = filesystem::copy_options::update_existing | filesystem::copy_options::recursive;

    for (const auto& dirEntry : filesystem::directory_iterator(filesystem::current_path())) {
        auto name = dirEntry.path().filename();
        if (name != ".git") {
            filesystem::copy(dirEntry, ".git/staging_area/" + name.string(), options);
        }
    }
}

void gitClass::gitAdd(string files[], int n) {
    const auto options = filesystem::copy_options::update_existing | filesystem::copy_options::recursive;

    for (int i = 0; i < n; ++i) {
        if (filesystem::exists(files[i])) {
            filesystem::copy(filesystem::path(files[i]), ".git/staging_area/" + files[i], options);
        } else {
            cout << "\x1B[31m" << files[i] << " does not exist!" << "\033[0m" << endl;
        }
    }
}

void gitClass::gitCommit(string msg) {
    list.addOnTail(msg);
}

void gitClass::gitRevert(string commitHash) {
    list.revertCommit(commitHash);
}

void gitClass::gitLog() {
    list.printCommitList();
}
