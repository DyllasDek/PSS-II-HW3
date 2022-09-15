#pragma once
#include "green_level.h"
class blue_level : public green_level{

protected:
    map<int,bool> b_l;

public:
    blue_level(){
        for (auto rooms : {lec_r,business_r, class_r, con_r, lab_cab, prof_cab, dir_cab}) {
            for (auto room : rooms) {
                b_l.insert(pair<int,bool>(room,true));
            }
        }
        for (auto rooms : {lab_cab,prof_cab,dir_cab,con_r,class_r}) {
            for (auto room : rooms ) {
                b_l[room] = false;
            }
        }
    }

    map<int, bool> access_to(){
        return b_l;
    }
};