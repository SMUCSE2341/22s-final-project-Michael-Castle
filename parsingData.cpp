//
// Created by Michael Castle on 4/10/22.
//

#include "parsingData.h"
#include <dirent.h>
#include <sys/stat.h>
#include <filesystem>
#include "fstream"
#include "sstream"

using namespace std;
namespace fs = std::__fs::filesystem;


void Directory::open_dir_using_dirent(const string& directory) {
    string filepath;
    DIR *dp;
    struct dirent *dirp; // the directory file
    struct stat filestat;
    dp = opendir(directory.c_str()); // open the directory
    if (dp == nullptr) // check and see if there was an error opening a given directory
    {
        cout << "Error(" << errno << ") opening " << directory << endl;
    }

    int i = 0;
    while ((dirp = readdir(dp)) != nullptr) // while files exist in the directory
    {
        if(i == 1 || i == 0) { // this is necessary because the first 2 lines that it tries to read are <directory>/. and <directory>/..
            i++;
            continue;
        }

        filepath = directory + "/" + dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it
        if (stat(filepath.c_str(), &filestat)) continue;
        if (S_ISDIR(filestat.st_mode))  { //If the file is a directory, recursive call to this function
            open_dir_using_dirent(filepath);
        } else {
            cout << filepath <<endl; //else print out the name of the file
        }
    }
    closedir(dp); // closing the directory
}

void Directory::open_dir_using_filesystem(const string& directory){
    for (const auto & entry : fs::recursive_directory_iterator(directory)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();



                std::cout << filename << std::endl;
            }
        }
    }
}


void Directory::ParseData(const string& filename) {

    ifstream file(filename);
    rapidjson::IStreamWrapper wrapper(file);
    rapidjson::Document d;
    d.ParseStream(filename);




//    file.open(filename);
//    if(file.is_open()){
//        while(!file.eof()){
//            file.getline(buffer, 1000, '\n');
//            str = string(buffer);
//        }
//    }

//    file.close();
//    cout << str;


}