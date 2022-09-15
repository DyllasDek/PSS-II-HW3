#include <string>

using namespace std;

class User{

public:
    string name;
    string surname;
    string login;
    int age;
    string type;
    int password;
    map <int, bool> access;
    int room; //Only for lab,prof and dir

    User(string Name,string Surname,int age, string type, int password,map<int,bool> access){
        this->name = Name;
        this->surname = Surname;
        this->age = age;
        this->password = password;
        this->type = type;
        this->access = access;
        this->login = string(1, Name[0]) + "." + Surname;
    }

    void change_password() {
        cout << "Enter your previous password:"<<endl;
        int prev_pass;
        cin >> prev_pass;
        cout << "Enter your new password:"<<endl;
        int new_password;
        cin >> new_password;
        if (prev_pass == password){
            password = new_password;
            cout << "Password have been changed successfully" << endl;
        } else {
            cout << "Wrong previous password" << endl;
        }
    }
};