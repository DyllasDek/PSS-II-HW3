#pragma once
#include "red_level.h"
using namespace std;
class yellow_level : public red_level {

protected:
    map<int,bool> yel_l;


public:
    map<int,bool> busy_prof;
    map<int,bool> busy_dir;
//Default constructor of yellow level
    yellow_level(){
        for (auto rooms : {lec_r,business_r, class_r, con_r, lab_cab, prof_cab, dir_cab}) {
            for (auto room : rooms) {
                yel_l.insert(pair<int,bool>(room,true));
            }
        }
        for (auto rooms : {lab_cab,prof_cab,dir_cab}) {
            for (auto room : rooms ) {
                yel_l[room] = false;
            }
        }
        for (auto room:dir_cab){
            busy_dir.insert(pair<int,bool>(room,false));
        }
        for (auto room:prof_cab){
            busy_prof.insert(pair<int,bool>(room,false));
        }
    }
// Personal access to each professor
    int new_prof(){
        map<int,bool> personal_access = yel_l;
        for (auto[room, access] : busy_prof){
            if (!access){
                personal_access[room] = true;
                busy_prof[room] = true;
                return room;
            }
        }
    }
// Personal access to each director
    int new_dir(){
        map<int,bool> personal_access = yel_l;
        for (auto[room, access] : busy_dir){
            if (!access){
                personal_access[room] = true;
                busy_dir[room] = true;
                return room;
            }
        }
    }
};