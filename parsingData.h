//
// Created by Michael Ramenofsky on 4/10/22.
//

#ifndef INC_22S_FINAL_PROJ_PARSINGDATA_H
#define INC_22S_FINAL_PROJ_PARSINGDATA_H
#include "unordered_map"
#include "wordObject.h"
#include "iostream"
#include "DSAvlTree.h"
#include "hashtable.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "DSDocument.h"

class Directory {
public:
    unordered_map<string, bool> documentWords;
    string tmpWord;
    string tmps;
    word wordObj;
    int i;
    char s[100];
    string idString;
    string textString;
    unordered_map<string, bool> stopWords;
    DSTree<word> index;
    DSTree<word> org_index;
    DSTree<word> person_index;
    HashTable orgHash;
    HashTable personHash;
    DSTree<DSDocument> documentTree;
    void createStopMap();

    void open_dir_using_filesystem(const std::string &directory);

    void open_dir_using_dirent(const std::string &directory);

    void ParseData(const std::string &filename);

    vector<string> SearchWord(const word searchword);

    vector<string> SearchPerson(const word searchword);

    vector<string> SearchOrg(const word searchword);

    string getText(string uuid);

    string stemWord(const string unstemedWord);

    vector<string> searchAnd(vector<string> words, vector<string> persons, vector<string> orgs, vector<string> notWords, vector<string> notPersons, vector<string> notOrgs);
    vector<string> searchOr(vector<string> words, vector<string> persons, vector<string> orgs, vector<string> notWords, vector<string> notPersons, vector<string> notOrgs);

    vector<string> Ranking(vector<string> DocIds, vector<string> words);

};
#endif //INC_22S_FINAL_PROJ_PARSINGDATA_H
