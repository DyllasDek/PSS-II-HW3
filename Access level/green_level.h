#pragma once
#include "yellow_level.h"
class green_level : public yellow_level{

protected:
    map<int,bool> gr_l;

public:
    map<int,bool> busy_lab;
//Default constructor of green level
    green_level() {
        for (auto rooms : {lec_r, business_r, class_r, con_r, lab_cab, prof_cab, dir_cab}) {
            for (auto room : rooms) {
                gr_l.insert(pair<int, bool>(room, true));
            }
        }
        for (auto rooms : {lab_cab, prof_cab, dir_cab, con_r}) {
            for (auto room : rooms) {
                gr_l[room] = false;
            }
        }
        for (auto room:lab_cab){
            busy_lab.insert(pair<int,bool>(room,false));
        }
    }

//Personal access to each Lab Employee
    int new_lab(){
        map<int,bool> personal_access = gr_l;
        for (auto[room, access] : busy_lab){
            if (!access){
                personal_access[room] = true;
                busy_lab[room] = true;
                return room;
            }
        }
    }
};