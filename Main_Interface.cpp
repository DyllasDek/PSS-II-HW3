#include <iostream>
#include <zconf.h>
#include "Users/Table_of_users.h"

void admin_commands(int command);

void unloggedText();

void user_commands(int command);

void show_admin_commands();

void show_user_commands();

Table unisys;

int id = -1;

int main() {

    bool alarm;
    bool running = true;
    bool logged = false;

    cout << "Welcome to the University Security system!" << endl;
    while (running) {
        if (logged) {
            if (unisys.table[id].type == "A") {
                cout << "Welcome admin " + unisys.table[id].name + "!" << endl << "Commands:";
                while (logged) {
                    show_admin_commands();
                    int command;
                    cin >> command;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Incorrect input. Please try again." << endl;
                        continue;
                    } else {
                        if (0 <= command && command < 5) {
                            admin_commands(command);
                        } else if (command == 5) {
                            logged = false;
                            id = -1;
                            cout << "You've logged out" << endl << endl;
                            break;
                        }
                    }
                }
            } else {
                cout << "Welcome " + unisys.table[id].name + " " + unisys.table[id].surname + "!" << endl;
                while (logged) {
                    show_user_commands();
                    int command = -1;
                    cin >> command;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Incorrect input. Please try again." << endl;
                        continue;
                    }
                    if (0 <= command && command < 3) {
                        user_commands(command);
                    } else if (command == 3) {
                        logged = false;
                        id = -1;
                        cout << "You've logged out" << endl << endl;
                    }
                }
            }
        } else {
            unloggedText();
            int command = -1;
            cin >> command;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Incorrect input. Please try again." << endl;
                continue;
            } else {
                switch (command) {
                    case 1:
                        while (!(logged)) {

                            cout << "Enter your login and password" << endl;

                            string Username;
                            int password;

                            cin >> Username >> password;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(256, '\n');
                                cout << "Incorrect input. Please try again." << endl;
                                continue;
                            }
                            for (auto user : unisys.table) {
                                id++;
                                if (user.login == Username & user.password == password) {
                                    cout << "Successfully logged in" << endl << endl;
                                    logged = true;
                                    break;
                                }
                            }
                            if (!logged) {
                                id = -1;
                                cout << "Invalid login or password" << endl;
                            }
                        }
                        break;
                    case 2:
                        return 0;
                }
            }
        }
    }
}

void show_admin_commands() {
    cout << endl << "1.Add user " << endl << "2.Delete User" << endl << "3.Give access to person" << endl
         << "4.Add room" << endl << "5.Logout" << endl << "0.Engage/Turn off emergency protocol"<< endl;
}

void show_user_commands(){
    cout << endl << "Commands:" << endl << "1.Check access" << endl << "2.Change password" << endl << "3.Loggout" << endl;
}

void user_commands(int command) {
    switch(command){
        case 1:
            cout << "Enter the room:" << endl;
            int room;
            cin >> room;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Incorrect input. Please try again." << endl;

            } else{unisys.check_access(id,room);}
            break;
        case 2:
            unisys.table[id].change_password();
            break;
    }
}

void unloggedText(){cout << "1. Log in" << endl << "2. Exit the program"<< endl;}

void admin_commands(int command) {
    switch (command) {
        case 0:
            unisys.EEP();
            break;
        case 1:
            unisys.input_user();
            break;
        case 2:
            unisys.delete_user();
            break;
        case 3:
            unisys.grant_access();
            break;
        case 4:
            unisys.add_room();
    }
}


