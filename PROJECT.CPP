#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
    int option = 0, n = 0;

    while (option != 6)
    {
        cout << "Options:\n";
        cout << "1. Add New Students\n";
        cout << "2. Student Login\n";
        cout << "3. Faculty Login\n";
        cout << "4. Proctor Login\n";
        cout << "5. Admin View\n";
        cout << "6. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        if (option == 1)
        {
            cout << "How many students you want to add? ";
            cin >> n;

            ofstream fout("Example.txt", ios::app);
            for (int i = 0; i < n; i++)
            {
                string regno, name, proctor, ds_mark = "00", os_mark = "00";

                cout << "\nEnter registration number: ";
                cin >> regno;
                cin.ignore();

                cout << "Enter name: ";
                getline(cin, name);

                cout << "Enter proctor ID: ";
                cin >> proctor;

                fout << left << setw(10) << regno
                     << setw(20) << name
                     << setw(5) << ds_mark
                     << setw(5) << os_mark
                     << setw(10) << proctor << endl;
            }
            fout.close();
            cout << "\nStudent(s) added successfully!\n";
        }

        else if (option == 2)
        {
            string regno, reg, name, ds, os, pid;
            bool found = false;

            cout << "Enter your registration number: ";
            cin >> regno;

            ifstream fin("Example.txt");
            while (fin >> reg >> ws && getline(fin, name, '\t') && fin >> ds >> os >> pid)
            {
                if (reg == regno)
                {
                    cout << "\nRegistration Number: " << reg << endl;
                    cout << "Name: " << name << endl;
                    cout << "Data Structures: " << ds << endl;
                    cout << "Operating System: " << os << endl;
                    cout << "Proctor ID: " << pid << endl;
                    found = true;
                    break;
                }
            }
            fin.close();

            if (!found)
            {
                cout << "No such registration number found!\n";
            }
        }

        else if (option == 3)
        {
            cout << "1. Add marks\n2. View marks\nChoose: ";
            int sub_option;
            cin >> sub_option;

            if (sub_option == 1)
            {
                vector<string> updated_lines;
                string reg, name, ds, os, pid;

                ifstream fin("Example.txt");
                while (fin >> reg >> ws && getline(fin, name, '\t') && fin >> ds >> os >> pid)
                {
                    string new_ds, new_os;
                    cout << "\nEnter Data Structures mark for " << reg << ": ";
                    cin >> new_ds;

                    cout << "Enter Operating System mark for " << reg << ": ";
                    cin >> new_os;

                    ostringstream oss;
                    oss << left << setw(10) << reg
                        << setw(20) << name
                        << setw(5) << new_ds
                        << setw(5) << new_os
                        << setw(10) << pid;
                    updated_lines.push_back(oss.str());
                }
                fin.close();

                ofstream fout("Example.txt", ios::trunc);
                for (const auto &line : updated_lines)
                {
                    fout << line << endl;
                }
                fout.close();

                cout << "\nMarks updated successfully!\n";
            }

            else if (sub_option == 2)
            {
                string reg, name, ds, os, pid;
                cout << "\nRegNo     DS   OS\n";

                ifstream fin("Example.txt");
                while (fin >> reg >> ws && getline(fin, name, '\t') && fin >> ds >> os >> pid)
                {
                    cout << left << setw(10) << reg
                         << setw(5) << ds
                         << setw(5) << os << endl;
                }
                fin.close();
            }

            else
            {
                cout << "Invalid sub-option!\n";
            }
        }

        else if (option == 4)
        {
            string procid, reg, name, ds, os, pid;
            bool found = false;

            cout << "Enter your proctor ID: ";
            cin >> procid;

            ifstream fin("Example.txt");
            while (fin >> reg >> ws && getline(fin, name, '\t') && fin >> ds >> os >> pid)
            {
                if (pid == procid)
                {
                    cout << "\nRegNo: " << reg;
                    cout << "\nName: " << name;
                    cout << "\nData Structures: " << ds;
                    cout << "\nOperating System: " << os << "\n";
                    found = true;
                }
            }
            fin.close();

            if (!found)
                cout << "No such proctor ID found!\n";
        }

        else if (option == 5)
        {
            string pass;
            cout << "Enter admin password: ";
            cin >> pass;

            if (pass == "admin")
            {
                string reg, name, ds, os, pid;
                cout << "\n"
                     << left
                     << setw(10) << "RegNo"
                     << setw(20) << "Name"
                     << setw(5) << "DS"
                     << setw(5) << "OS"
                     << setw(10) << "ProctorID" << endl;

                ifstream fin("Example.txt");
                while (fin >> reg >> ws && getline(fin, name, '\t') && fin >> ds >> os >> pid)
                {
                    cout << left
                         << setw(10) << reg
                         << setw(20) << name
                         << setw(5) << ds
                         << setw(5) << os
                         << setw(10) << pid << endl;
                }
                fin.close();
            }
            else
            {
                cout << "Wrong password!\n";
            }
        }

        else if (option != 6)
        {
            cout << "Invalid option! Please try again.\n";
        }
    }

    cout << "\nExiting program. Goodbye!\n";
    return 0;
}
