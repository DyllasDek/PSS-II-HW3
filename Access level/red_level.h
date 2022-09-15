#pragma once
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class red_level{

protected:

    vector<int> lec_r = {105, 106, 107, 108};
    vector<int> business_r{110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125};
    vector<int> class_r = {300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 320};
    vector<int> con_r = {400};
    vector<int> lab_cab = {401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420};
    vector<int> prof_cab = {500,501,502,503,504,505,506,507,508,509,510,511,512,513,514,515,516,517,518,519,520};
    vector<int> dir_cab = {550,551,552,553,554,555,556,557,558,559,560};

    map <int, bool> Admin;

public:
    // Default constructor of red level
    red_level(){
        for (auto rooms : {lec_r,business_r, class_r, con_r, lab_cab, prof_cab, dir_cab}) {
            for (auto room : rooms) {
                Admin.insert(pair<int,bool>(room,true));
            }
        }
    }

    // Returning MAP of admin access
    virtual map<int,bool> access_to(){
        return Admin;
    }

};

