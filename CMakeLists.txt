cmake_minimum_required(VERSION 3.16.0)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)



add_executable( 22s_final_proj main.cpp catch_setup.cpp DSAvlTree.h parsingData.cpp parsingData.h wordObject.cpp wordObject.h stemmerGiveUp.h HashTable.h vectorHelper.cpp vectorHelper.h DSDocument.cpp DSDocument.h)


