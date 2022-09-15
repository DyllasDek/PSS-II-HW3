#include <string>
#include "../Access level/red_level.h"
#include "../Access level/yellow_level.h"
#include "../Access level/green_level.h"
#include "../Access level/blue_level.h"
#include "../Access level/no_level.h"
#include "user.h"

using namespace std;

class Table{

private:
    int count;
    int admin_count = 1;

public:
    bool Alarm = false;

    red_level admin;
    yellow_level prof_dir;
    green_level labEmp;
    blue_level guest;
    no_level student;
    vector<User> table;

    //Default constructor
    Table() {
        table.push_back(User("Admin","Admin",0,"A",123,admin.access_to()));
        map<int,bool> test_dir = prof_dir.access_to();
        test_dir[550] = true;
        map<int,bool> prof = prof_dir.access_to();
        prof[500] = true;
        map<int,bool> lab = labEmp.access_to();
        lab[401] = true;
        table.push_back(User("Danila","Korneenko",20,"D",123,test_dir));
        table.push_back(User("Danila","Korneenko1",20,"P",123,prof));
        table.push_back(User("Danila","Korneenko2",20,"L",123,lab));
        table.push_back(User("Danila","Korneenko3",20,"G",123,guest.access_to()));
        table.push_back(User("Danila","Korneenko4",20,"S",123,student.access_to()));
        count = 6;
    }

    //Input user to table
    void input_user(){
        try{

            string name,surname,type;
            int age,password;
            map<int,bool> access;
            int room;

            cout << "Input an user like: Name Surname Age Type Password" << endl;
            cin >> name >> surname >> age >> type >> password;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Incorrect input. Please try again." << endl;

            } else {
                //Checking type of person
                if (type == "A") {
                    access = admin.access_to();
                    admin_count++;

                } else if (type.compare("P") == 0) {
                    access = prof_dir.access_to();
                    room = prof_dir.new_prof();
                    access[room] = true;

                } else if (type.compare("D") == 0) {
                    access = prof_dir.access_to();
                    room = prof_dir.new_dir();
                    access[room] = true;

                } else if (type.compare("L") == 0) {
                    access = labEmp.access_to();
                    room = labEmp.new_lab();
                    access[room] = true;

                } else if (type.compare("G") == 0) {

                    access = guest.access_to();

                } else if (type.compare("S") == 0) {

                    access = student.access_to();

                } else { throw (1); }
                table.push_back(User(name, surname, age, type, password, access));
                table[count].room = room;
                cout << "Person have been added successfully!" << endl;
                count++;
            }
        } catch (int i) {cout << "Invalid type of person. Try again!" << endl;}
    }

    //Deleting user
    void delete_user(){
        try {
            int id;

            cout << "Write an ID of a person you want to delete." << endl;
            cin >> id;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Incorrect input. Please try again." << endl;

            } else {
                if (id >= 0 && id < table.size()) {
                    if (table[id].type == "A" && admin_count == 1) {
                        throw (1);
                    } else {
                        cout << "Are you sure you want to delete " + table[id].surname + " " + table[id].name + "? Y/N"
                             << endl;
                        string command;
                        cin >> command;
                        if (command == "Y") {
                            if (table[id].type == "D") {
                                prof_dir.busy_dir[table[id].room] = false;
                            } else if (table[id].type == "P") {
                                prof_dir.busy_prof[table[id].room] = false;
                            } else if (table[id].type == "L") {
                                labEmp.busy_lab[table[id].room] = false;
                            }
                            table.erase(table.begin() + id);
                            cout << "Person have been deleted successfully!" << endl;
                        } else {
                            cout << "Deletion prevented" << endl;
                        }
                    }
                } else {
                    throw (2);
                }
            }
            } catch (int i){
                switch (i) {
                    case 1:
                        cout << "You cannot delete last admin" << endl;
                        break;
                    case 2:
                        cout << "Invalid ID. Try again" << endl;
                        break;
                }
            }
        }

    //Granting access to user
    void grant_access(){
        int id,room;
        cout << "Write ID to who you want give access to ROOM like: ID ROOM" << endl;
        cin >> id >> room;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Incorrect input. Please try again." << endl;

        } else {
            if (id >= 0 && id < table.size()) {
                if (table[id].access.count(room)) {
                    if (table[id].access[room]) {
                        cout << "This person already have access to this room" << endl;
                    } else {
                        table[id].access[room] = true;
                        cout << "Successfully granted " + table[id].name + " " + table[id].surname +
                                " access to room " + to_string(room) << endl;
                    }
                } else {
                    cout << "Error. No such room in university" << endl;
                }
            } else {
                cout << "Invalid ID. Try again" << endl;
            }
        }
    }

    //Adding room to the system
    void add_room(){
        int room;
        cout << "Write number of the room you want to add" << endl;
        cin >> room;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Incorrect input. Please try again." << endl;

        } else {
            map<int, bool> all_rooms = admin.access_to();
            if (all_rooms.count(room)) {
                cout << "This room is already exist" << endl;
            } else {
                for (auto person : table) {
                    bool access;
                    if (person.type == "A") {
                        access = true;
                    } else {
                        access = false;
                    }

                    person.access.insert(pair<int, bool>(room, access));
                }
                cout << "Room successfully added to University system" << endl;
            }
        }
    }

    //Checking access to the room
    void check_access(int id,int room){
        if(Alarm){
            cout << table[id].name +" "+ table[id].surname + " can open room " + to_string(room);
        } else {
            if (table[id].access[room]) {
                cout << table[id].name + " " + table[id].surname + " can open room " + to_string(room);
            } else {
                cout << table[id].name + " " + table[id].surname + " cannot open room " + to_string(room);
            }
        }
    }

    //Engage emergency protocol
    void EEP(){
        if(Alarm){
            cout<<"Do you want to turn off an alarm? Write Y if you agree."<< endl;
            string command;
            cin >> command;
            if(command == "Y"){
                Alarm = false;
                cout << "Alarm was turned off." << endl;
            } else {
                cout << "Alarm is still working" << endl;
            }
        } else {
            cout << "Do you want to turn on an alarm? Everybody will have access to every room. Write Y if you agree." << endl;
            string command;
            cin >> command;
            if(command == "Y"){
                Alarm = true;
                cout << "Alarm was turned on." << endl;
            } else {
                cout << "Alarm is prevented" << endl;
            }
        }
    }
};