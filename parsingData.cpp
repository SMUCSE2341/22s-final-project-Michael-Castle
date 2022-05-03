//
// Created by Michael Castle on 4/10/22.
//
#include "parsingData.h"
#include "vectorHelper.h"
#include <dirent.h>
#include <sys/stat.h>
#include <filesystem>
#include "fstream"
#include "sstream"
#include "stemmerGiveUp.h"
#include <algorithm>


using namespace std;
namespace fs = std::filesystem;


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
            //cout << filepath <<endl; //else print out the name of the file
        }
    }
    closedir(dp); // closing the directory
}

void Directory::open_dir_using_filesystem(const string& directory){
    for (const auto & entry : fs::recursive_directory_iterator(directory)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                ParseData(filename);
                //std::cout << filename << std::endl;
            }
        }
    }
}

void Directory::createStopMap() {
    istringstream tempstr("able about above abroad according accordingly across actually adj after afterwards again against ago ahead ain't all allow allows almost alone along alongside already also although always am amid amidst among amongst an and another any anybody anyhow anyone anything anyway anyways anywhere apart appear appreciate appropriate are aren't around as a's aside ask asking associated at available away awfully back backward backwards be became because become becomes becoming been before beforehand begin behind being believe below beside besides best better between beyond both brief but by came can cannot cant can't caption cause causes certain certainly changes clearly c'mon co co. com come comes concerning consequently consider considering contain containing contains corresponding could couldn't course c's currently dare daren't definitely described despite did didn't different directly do does doesn't doing done don't down downwards during each edu eg eight eighty either else elsewhere end ending enough entirely especially et etc even ever evermore every everybody everyone everything everywhere ex exactly example except fairly far farther few fewer fifth first five followed following follows for forever former formerly forth forward found four from further furthermore get gets getting given gives go goes going gone got gotten greetings had hadn't half happens hardly has hasn't have haven't having he he'd he'll hello help hence her here hereafter hereby herein here's hereupon hers herself he's hi him himself his hither hopefully how howbeit however hundred i'd ie if ignored i'll i'm immediate in inasmuch inc inc. indeed indicate indicated indicates inner inside insofar instead into inward is isn't it it'd it'll its it's itself i've just k keep keeps kept know known knows last lately later latter latterly least less lest let let's like liked likely likewise little look looking looks low lower ltd made mainly make makes many may maybe mayn't me mean meantime meanwhile merely might mightn't mine minus miss more moreover most mostly mr mrs much must mustn't my myself name namely nd near nearly necessary need needn't needs neither never neverf neverless nevertheless new next nine ninety no nobody non none nonetheless noone no-one nor normally not nothing notwithstanding novel now nowhere obviously of off often oh ok okay old on once one ones one's only onto opposite or other others otherwise ought oughtn't our ours ourselves out outside over overall own particular particularly past per perhaps placed please plus possible presumably probably provided provides que quite qv rather rd re really reasonably recent recently regarding regardless regards relatively respectively right round said same saw say saying says second secondly see seeing seem seemed seeming seems seen self selves sensible sent serious seriously seven several shall shan't she she'd she'll she's should shouldn't since six so some somebody someday somehow someone something sometime sometimes somewhat somewhere soon sorry specified specify specifying still sub such sup sure take taken taking tell tends th than thank thanks thanx that that'll thats that's that've the their theirs them themselves then thence there thereafter thereby there'd therefore therein there'll there're theres there's thereupon there've these they they'd they'll they're they've thing things think third thirty this thorough thoroughly those though three through throughout thru thus till to together too took toward towards tried tries truly try trying t's twice two un under underneath undoing unfortunately unless unlike unlikely until unto up upon upwards us use used useful uses using usually v value various versus very via viz vs want wants was wasn't way we we'd welcome well we'll went were we're weren't we've what whatever what'll what's what've when whence whenever where whereafter whereas whereby wherein where's whereupon wherever whether which whichever while whilst whither who who'd whoever whole who'll whom whomever who's whose why will willing wish with within without wonder won't would wouldn't yes yet you you'd you'll your you're yours yourself yourselves you've zero");
    string str;
    while(tempstr >> str){
        stopWords[str] = true;
    }
}


void Directory::ParseData(const string& filename) {

    ifstream file(filename);
    rapidjson::IStreamWrapper wrapper(file);
    rapidjson::Document d;
    d.ParseStream(wrapper);

    rapidjson::Value &text = d["text"];
    rapidjson::Value &persons = d["entities"]["persons"];
    rapidjson::Value &organizations = d["entities"]["organizations"];
    rapidjson::Value &uuid = d["uuid"];

    idString = uuid.GetString();
    vector<string> personsString;
    vector<string> orgString;
    for(int i = 0; i < persons.Size(); i++) {
        personsString.push_back(persons[i]["name"].GetString());
    }
    for(int i = 0; i < organizations.Size(); i++) {
        orgString.push_back(organizations[i]["name"].GetString());
    }
    for (int i = 0; i < personsString.size(); i++) {
        vector<string>* vectorPoint = personHash.findPoint(personsString.at(i));
        if(vectorPoint == nullptr) {
            vector<string> tmpV;
            tmpV.push_back(idString);
            //cout << personsString.at(i) << endl;
            personHash.insertElement(personsString.at(i), tmpV);
            vectorPoint = personHash.findPoint(personsString.at(i));
        }
        else {
            //cout << idString << endl;
            personHash.appendID(personsString.at(i), idString);
        }

        //personsString.push_back(persons[i]["name"].GetString());
    }
    for (int i = 0; i < orgString.size(); i++) {
        vector<string>* vectorPoint = orgHash.findPoint(orgString.at(i));
        if(vectorPoint == nullptr) {
            vector<string> tmpV;
            tmpV.push_back(idString);
            orgHash.insertElement(orgString.at(i), tmpV);
        }
        else {
            orgHash.appendID(orgString.at(i), idString);
        }
    }
    textString = text.GetString();
    istringstream textStream(textString);

    DSDocument tmpDocument;
    tmpDocument.ID = idString;
    tmpDocument.text = textString;
    documentTree.insert(tmpDocument);


    while (textStream >> tmpWord) {
        if (stopWords[tmpWord]) {
// || tmpWord.size() < 3
        } else {
            i = tmpWord.size() - 1;
            for (int j = 0; j < i + 1; j++) {
                tmpWord[j] = tolower(tmpWord[j]);
                if (!isalpha(tmpWord[j])) {
                    tmpWord.resize(j);
                    break;
                }
            }
            i = tmpWord.size() - 1;
            tmps = tmpWord;

            strcpy(s, tmps.c_str());
            i = stem(s, 0, i);
            tmpWord.resize(i + 1);

            wordObj.id = tmpWord;
            DSNode<word> *location;
            index.insert(wordObj);
            location = index.findValue(wordObj);

            if (tmpWord != "" && tmpWord != "iraqi") {
                location->data.documents.push_back(idString);
            }
            //cout << tmpWord << endl;
        }

    }
    for(string wholeName : orgString) {
        istringstream orgStream(wholeName);
        while (orgStream >> tmpWord) {
            if (stopWords[tmpWord]) {
// || tmpWord.size() < 3
            } else {
                i = tmpWord.size() - 1;
                for (int j = 0; j < i + 1; j++) {
                    tmpWord[j] = tolower(tmpWord[j]);
                    if (!isalpha(tmpWord[j])) {
                        tmpWord.resize(j);
                        break;
                    }
                }
                wordObj.id = tmpWord;
                DSNode<word> *location;
                org_index.insert(wordObj);
                location = org_index.findValue(wordObj);

                if (tmpWord != "") {
                    location->data.documents.push_back(idString);
                }
                //cout << tmpWord << endl;
            }

        }
    }


    for(string wholeName : personsString) {
    istringstream personStream(wholeName);
        while (personStream >> tmpWord) {
            if (stopWords[tmpWord]) {
// || tmpWord.size() < 3
            } else {
                i = tmpWord.size() - 1;
                for (int j = 0; j < i + 1; j++) {
                    tmpWord[j] = tolower(tmpWord[j]);
                    if (!isalpha(tmpWord[j])) {
                        tmpWord.resize(j);
                        break;
                    }
                }
                wordObj.id = tmpWord;
                DSNode<word> *location;
                person_index.insert(wordObj);
                location = person_index.findValue(wordObj);

                if (tmpWord != "") {
                    location->data.documents.push_back(idString);
                }
                //cout << tmpWord << endl;
            }

        }
    }

    file.close();

}

vector<string> Directory::SearchWord(const word searchword) {
    vectorHelper myHelp;
    vector<string> returnVector;
    cout << searchword.id << endl;
    DSNode<word>* tmpWord = index.findValue(searchword);
    if(tmpWord != nullptr) {
        vector<string> locations = tmpWord->data.documents;
        for (int i = 0; i < locations.size(); i++) {
            returnVector.push_back(locations[i]);
        }
        myHelp.pruneVector(&returnVector);
    }
    return returnVector;

}
 vector<string> Directory::SearchPerson(const word searchword) {
    string tmp = searchword.id;
    for(int i = 0; i < tmp.size(); i++) {
        tmp[i] = tolower(tmp[i]);
    }
    return personHash.find(tmp);
}

vector<string> Directory::SearchOrg(const word searchword) {
    string tmp = searchword.id;
    for(int i = 0; i < tmp.size(); i++) {
        tmp[i] = tolower(tmp[i]);
    }
    return orgHash.find(tmp);
}

string Directory::stemWord(string searchWord) {
    int i = 0;
    string tmps;
    char s[50];

    i = searchWord.size()-1;
    for(int j = 0; j < i+1; j++) {
        searchWord[j] = tolower(searchWord[j]);
        if(!isalpha(searchWord[j])) {
            searchWord.resize(j);
            break;
        }
    }
    i = searchWord.size()-1;
    tmps = searchWord;

    strcpy(s,tmps.c_str());
    i = stem(s, 0, i);
    searchWord.resize(i+1);
    return searchWord;
}

vector<string>
Directory::searchAnd(vector<string> words, vector<string> persons, vector<string> orgs, vector<string> notWords,
                     vector<string> notPersons, vector<string> notOrgs) {

    vector<string> returnVector;
    vector<string> tmpVector;
    vectorHelper myHelp;
    word tmpWord;
    tmpWord.id = words.at(0);
    returnVector = SearchWord(tmpWord);
    for(int i = 1; i < words.size(); i++) {
        tmpWord.id = words.at(i);
        tmpVector = SearchWord(tmpWord);
        returnVector = myHelp.combineAnd(&returnVector, &tmpVector);
    }
    for(int i = 0; i < persons.size(); i++) {
        tmpVector = SearchPerson(persons.at(i));
        returnVector = myHelp.combineAnd(&returnVector, &tmpVector);
    }
    for(int i = 0; i < orgs.size(); i++) {
        tmpVector = SearchOrg(orgs.at(i));
        returnVector = myHelp.combineAnd(&returnVector, &tmpVector);
    }

    for(string notWord : notWords) {
        tmpWord.id = notWord;
        tmpVector = SearchWord(tmpWord);
        returnVector = myHelp.combineNot(&returnVector, &tmpVector);
    }

    for(string notOrg : notOrgs) {
        tmpWord.id = notOrg;
        tmpVector = SearchOrg(tmpWord);
        returnVector = myHelp.combineNot(&returnVector, &tmpVector);
    }

    for(string notWord : notPersons) {
        tmpWord.id = notWord;
        tmpVector = SearchPerson(tmpWord);
        returnVector = myHelp.combineNot(&returnVector, &tmpVector);
    }

    return returnVector;
}


vector<string>
Directory::searchOr(vector<string> words, vector<string> persons, vector<string> orgs, vector<string> notWords,
                     vector<string> notPersons, vector<string> notOrgs) {

    vector<string> returnVector;
    vector<string> tmpVector;
    vectorHelper myHelp;
    word tmpWord;
    tmpWord.id = words.at(0);
    returnVector = SearchWord(tmpWord);
    for(int i = 1; i < words.size(); i++) {
        tmpWord.id = words.at(i);
        tmpVector = SearchWord(tmpWord);
        returnVector = myHelp.combineOr(&returnVector, &tmpVector);
    }
    for(int i = 0; i < persons.size(); i++) {
        tmpVector = SearchPerson(persons.at(i));
        returnVector = myHelp.combineOr(&returnVector, &tmpVector);
    }
    for(int i = 0; i < orgs.size(); i++) {
        tmpVector = SearchOrg(orgs.at(i));
        returnVector = myHelp.combineOr(&returnVector, &tmpVector);
    }

    for(string notWord : notWords) {
        tmpWord.id = notWord;
        tmpVector = SearchWord(tmpWord);
        returnVector = myHelp.combineNot(&returnVector, &tmpVector);
    }

    for(string notWord : notOrgs) {
        tmpWord.id = notWord;
        tmpVector = SearchOrg(tmpWord);
        returnVector = myHelp.combineNot(&returnVector, &tmpVector);
    }

    for(string notWord : notPersons) {
        tmpWord.id = notWord;
        tmpVector = SearchPerson(tmpWord);
        returnVector = myHelp.combineNot(&returnVector, &tmpVector);
    }
    return returnVector;
}




vector<string> Directory::Ranking(vector<string> DocIds, vector<string> words) {
    vector<pair<double, string>> uuidWithRankings;
    DSDocument tmp;
    vector<string> tempVec;
    vector<string> finalVec;
    vector<int> integerVec;
    string temp;
    double counter = 0;
    for(int i = 0; i < DocIds.size(); i++){
        temp = getText(DocIds.at(i));
        tempVec = tmp.putWordsInVec(temp);

        for (int j = 0; j < words.size(); j++) {
            for (int n = 0; n < tempVec.size(); n++) {
                tempVec.at(n) = stemWord(tempVec.at(n));
                if (tempVec.at(n) == words.at(j)){
                    counter++;
                }
            }
        }
        counter = counter/tempVec.size();
        uuidWithRankings.push_back(make_pair(counter, (DocIds.at(i))));
        counter = 0;
    }
    sort(uuidWithRankings.begin(), uuidWithRankings.end());

    for(int v = 0; v < 10 && v < uuidWithRankings.size(); v++){
        finalVec.push_back(uuidWithRankings.at(uuidWithRankings.size()-v-1).second);
    }

    return finalVec;
}



string Directory::getText(const string ID) {
    DSDocument tmp;
    tmp.ID = ID;
    return documentTree.findValue(tmp)->data.text;
}

