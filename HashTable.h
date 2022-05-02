//
// Created by Michael Castle on 5/1/22.
//

#ifndef INC_22S_FINAL_PROJ_HASHTABLE_H
#define INC_22S_FINAL_PROJ_HASHTABLE_H

//class HashTable{
//
//private:
//    std::list<std::pair<std::string,std::vector<int>>> table[10000];
//
//
//
//};

#include <iostream>
#include <list>

using namespace std;

class HashTable{
private:
    list<pair<string, vector<string>>> **table;
    int tableSize;
    double total_elements;
    float max_load_factor;

    // Hash function to calculate hash for a value:
    int hash(string key) {
        std::hash<string> hashString;
        int hashed_key = hashString(key);
        return abs(hashed_key % (int)total_elements);
    }

public:
    // Constructor to create a hash table with 'n' indices:
    HashTable(){
        max_load_factor = 0.7;
        total_elements = 100;
        tableSize = 0;
        table = new list<pair<string, vector<string>>>*[total_elements];
        list<pair<string, vector<string>>> tmpList;
        pair<string, vector<string>> tmpPair;
        tmpPair.first = "hello\0";
        vector<string> tmpV = {"1", "2"};
        tmpPair.second = tmpV;
        tmpList.push_back(tmpPair);
        table[2] = &tmpList;
        table[1] = &tmpList;
        table[0] = &tmpList;
        cout << table[2]->front().first << endl;
        cout << "finished";
        for(int i = 0; i < total_elements; i++) {
            table[i] = new list<pair<string, vector<string>>>;
        }

    }

    // Insert data in the hash table:
    void insertElement(string key, vector<string> value){
        pair<string, vector<string>> temp;
        temp.first = key;
        temp.second = value;
        table[hash(key)]->push_back(temp);
        tableSize++;
        if(tableSize/total_elements > max_load_factor){
            total_elements = total_elements * 3;
            list<pair<string, vector<string>>> **tmpTable;
            tmpTable = new list<pair<string, vector<string>>>*[(int)total_elements/3];
            for(int i = 0; i < total_elements/3; i++) {
                tmpTable[i] = table[i];
            }

            list<pair<string, vector<string>>>* oldList;
            int hashNum = hash(key);
            for(int i = 0; i < total_elements/3; i++){
                oldList = tmpTable[i];

                while(!oldList->empty()) {
                    insertElement(oldList->front().first,oldList->front().second);
                    oldList->remove(oldList->front());
                }
            }
        }
    }

    vector<string> find(string key){
        list<pair<string, vector<string>>> *tmpList;
        int hashNum = hash(key);
        tmpList = table[hashNum];
        while(tmpList->front().first!=key && !tmpList->empty()) {
            if(tmpList->front().first==key) {
                return tmpList->front().second;
            }
            tmpList->remove(tmpList->front());
        }
        vector<string> empty;
        return empty;
    }



    // Remove data from the hash table:
//    void remove(string key){
//        auto it = find(key);
//        if(it != table[hash(key)].end()){
//            table[hash(key)].erase(it);
//            total_elements--;
//        }
//    }

};



#endif //INC_22S_FINAL_PROJ_HASHTABLE_H
