#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

struct record
{
    string user;
    string pass;
    int q;
    string ans;
};

class auth
{
    public:

    auth(){ srand(time(0)); }

    void menu();
    void login();
    void registration();
    void forgot();

};

void auth :: menu()
{
    int c;
    cout << "\nAuthentication\n";
    cout << "1. Login\n";
    cout << "2. Registration\n";
    cout << "3. Forgot Password\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> c;
    system("cls");
    switch(c)
    {
        case 1: login();
                break;

        case 2: registration();
                break;

        case 3: forgot();
                break;

        case 4: exit(0);

        default: cout << "Ooop's Wrong Choice!!\n";
               
    }
}

void auth :: login()
{
    int q;
    string name,pass,user,p,ans;
    bool found = false;
    cout << "Enter your username: \n";
    cin >> name;
    cout << "Enter your password: \n";
    cin >> pass;
    ifstream read ("records.txt",ios :: in);
    if(!read)
    {
        cout << "errorr!!\n";
        return;
    }
    while(read >> user >> p >> q >> ans)
    {
        if((user == name) && (pass == p))
        {
            found = true;
            break;
        }
    }

    if(found == true)
    {
        system("cls");
        cout << name << " Login successful\n\n";
        menu();
    }
    else
    {            
        system("cls");
        cout << "username or password not available!!\nTry again\n\n";
        menu();
    }
    read.close();
}

void auth :: registration()
{
    vector <string> quest = {"What's your birth year", "What's your principal name", "What's your hobby", "What's your grand parents name", "What's your nickname"};
    int q = rand() % quest.size();
    string name, pass, ans;
    string user, p, a;
    int i;
    cout << "Enter username: \n";
    cin >> name;
    
    vector <record> records;
    ifstream search("records.txt");
    while(search >> user >> p >> i >> a)
    {
        records.push_back({user, p, i, a});
    }
    search.close();
    bool found = false;
    for(auto &rec : records)
    {
        if(rec.user == name)
        {
            found = true;
        }
    }
    if(found)
    {
        cout << "username not available!!\n\n";
        menu();
        return;
    }
    else
    {
        cout << "Enter password: \n";
        cin >> pass;
        cout << quest[q] << endl;
        cin >> ans;
    }
    
    ofstream write("records.txt", ios :: app);
    if(!write)
    {
        cout << "errorr!!\n";
        system("cls");
    }
    else
    {
        write << name << "   " << pass << "   " << q << "   " << ans << endl;
        system("cls");
        cout << "Registration is successful!!\n\n";
    }
    
    write.close();
    menu();
}

void auth :: forgot()
{
    vector <string> quest = {"What's your birth year", "What's your principal name", "What's your hobby", "What's your grand parents name", "What's your nickname"};
    int q;
    string name, a, neww;
    cout << "Enter your username: ";
    cin >> name;
    string pass, ans, user;
   
    vector <record> records;
    //idher username se vo uska question dhundega then vo quest print karke ans match karna he then give a chance to reset pass
  
    ifstream search("records.txt");
    while(search >> user >> pass >> q >> ans)
    {
        records.push_back({user, pass, q, ans});
    }
    search.close();

    bool found = false;
    for(auto &rec : records)
    {
        if(rec.user == name)
        {
            found = true;
            cout << quest[rec.q] << ": " << endl;
            cin >> a;
            if(rec.ans == a)
            {
                system("cls");
                cout << "Security test successful!!\n";
                cout << "Reset your password: \n";
                cin >> neww;
                rec.pass = neww;
                system("cls");
                cout << "Password changed successfullyy\n";
            }
            else
            {
                system("cls");
                cout << "Security test failed!!\n";
            }
            break;
        }
    }

    if(!found)
    {
        system("cls");
        cout << "Username not found!!\n";
    }

    ofstream write("records.txt");
    for(const auto &rec : records)
    {
        write << rec.user << "   " << rec.pass << "   " << rec.q << "   " << rec.ans <<endl;
    }
    write.close();
    
    menu();
}

int main()
{
    auth a;
    a.menu();
}

