#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

#define N 100

struct deposid {
    int account_number;
    string client_name;
    string client_surname;
    string client_patronymic;
    double amount;
    int date_day;
    int date_month;
    int date_year;
};

int i = 0;  // ���������� ����������, ������� ������ ��� �������� ���-�� ���������.
string check;  //  ��� ���������� ������ ��� �������� ����, ��� ��� ������������.
time_t now = time(0);
tm* localtm = localtime(&now);

string path = "file.txt";

void save(deposid* deps) {
    int k = 0;
    string msg;
    string tmp;
    fstream fs;
    fs.open(path, fstream::out);
    if (!fs.is_open()) {
        cout << "������ ������ �����!";
    }
    else {
        while (!fs.eof()) {
            tmp = "";
            getline(fs, tmp);
            for (int j = 0; j < i; j++) {
                stringstream ss;
                ss << deps[j].amount;
                msg = to_string(deps[j].account_number) + " " + deps[j].client_name + " " + deps[j].client_surname + " " + deps[j].client_patronymic + " " + ss.str() + " " + to_string(deps[j].date_day) + " " + to_string(deps[j].date_month) + " " + to_string(deps[j].date_year);
                if (tmp == msg) { k++; }
            }
        }
        for (int j = k; j < i; j++) {
            ofstream fout;
            fout.open(path, ofstream::app);
            stringstream ss;
            ss << deps[j].amount;
            msg = to_string(deps[j].account_number) + " " + deps[j].client_name + " " + deps[j].client_surname + " " + deps[j].client_patronymic + " " + ss.str() + " " + to_string(deps[j].date_day) + " " + to_string(deps[j].date_month) + " " + to_string(deps[j].date_year);
            fout << msg << "\n";
            fout.close();
        }
    }
    fs.close();
    k = 0;
}

bool check_deposid(deposid* deps, string buffer_name, string buffer_surname, string buffer_patronymic, int buffer_amount, int i) {
    for (int j = 0; j < i + 1; j++) {
        if ((string)buffer_name == (string)deps[j].client_name) {
            if ((string)buffer_surname == (string)deps[j].client_surname) {
                if ((string)buffer_patronymic == (string)deps[j].client_patronymic) {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }
        else { return false; }
    }
}

int create_deposid(deposid* deps, int buffer_account_number, string buffer_name, string buffer_surname, string buffer_patronymic, int buffer_amount, int buffer_date_day, int buffer_date_month, int buffer_date_year) {

    bool saved = false;

    cout << "�� ������ ������ �������� ��������. ��� ������ ������ ������� �������� ����� yes. ��� ����������� � ���� ������� menu." << endl;

    cin >> check;  //  � ���������� check ��������� ��, ��� ��� ������������.
    cout << endl;

    if (check == "yes" or check == "YES" or check == "Yes") {
        cout << "==============================" << endl;
        buffer_account_number = i + 1;
        buffer_date_day = localtm->tm_mday;
        buffer_date_month = localtm->tm_mon + 1;
        buffer_date_year = localtm->tm_year - 100;
        cout << "������� ���� ���: "; cin >> buffer_name; cin.ignore();
        cout << "������� ���� �������: "; cin >> buffer_surname; cin.ignore();
        cout << "������� ���� ��������: "; cin >> buffer_patronymic; cin.ignore();
        cout << "������� ����� ��������: "; cin >> buffer_amount; cin.ignore();
        for (int j = 0; j < to_string(buffer_amount).length(); j++) {
            if (!isdigit(to_string(buffer_amount)[j])) {
                cout << "�� ���������� ��������!" << endl << endl;
                return 1;
            }
        }
        cout << "==============================" << endl << endl;

        if (check_deposid(deps, buffer_name, buffer_surname, buffer_patronymic, buffer_amount, i)) {
            cout << "������� �� ����� �������� ����������. ������ ������� ����� ����?." << endl;
            cout << "� ������ �������������� ������ ������� yes, ���� ������� ��������� � ����, �� ������� menu." << endl;
            cin >> check;

            if (check == "yes" or check == "YES" or check == "Yes") {
                deps[i].account_number = buffer_account_number;
                deps[i].date_day = buffer_date_day;
                deps[i].date_month = buffer_date_month;
                deps[i].date_year = buffer_date_year;
                deps[i].client_name = buffer_name;
                deps[i].client_surname = buffer_surname;
                deps[i].client_patronymic = buffer_patronymic;
                deps[i].amount = buffer_amount;
                i++;
                cout << endl << "==============================" << endl << endl;
                if (!saved) {
                    save(deps);
                }
            }
            else { return 1; }
        }
        else {
            deps[i].account_number = buffer_account_number;
            deps[i].date_day = buffer_date_day;
            deps[i].date_month = buffer_date_month;
            deps[i].date_year = buffer_date_year;
            deps[i].client_name = buffer_name;
            deps[i].client_surname = buffer_surname;
            deps[i].client_patronymic = buffer_patronymic;
            deps[i].amount = buffer_amount;
            i++;
            if (!saved) {
                save(deps);
                saved = true;
            }
        }
        cout << endl;
    }
    else if (check == "menu" or check == "MENU" or check == "Menu") {
        saved = false;
        cin.clear();
        return 1;
    }
    else {
        cout << "�������� ����� �� �������. ���������� �����..." << endl;
        saved = false;
        cin.clear();
        return 1;
    }
    saved = false;
    cin.clear();
}

void show_deposid(deposid* deps, string name, string surname, string patronymic, int amount, int buffer_date_day, int buffer_date_month, int buffer_date_year) {
    int check_user = 0;  // ���-�� ��������� �������������.

    cout << "==============================" << endl;
    cout << "���: " << name << endl;
    cout << "�������: " << surname << endl;
    cout << "��������: " << patronymic << endl;

    for (int j = 0; j < i; j++) {
        if ((string)name == (string)deps[j].client_name) {
            if ((string)surname == (string)deps[j].client_surname) {
                if ((string)patronymic == (string)deps[j].client_patronymic) {
                    if (amount == deps[j].amount) {
                        check_user++;
                        cout << "����� ��������: " << deps[j].account_number << endl;
                        cout.precision(2);
                        cout << "����� ��������: " << fixed << deps[j].amount << " ���." << endl;
                        cout << "���� ��������: " << deps[j].date_day << "." << deps[j].date_month << "." << deps[j].date_year << endl;
                    }
                }
            }
        }
    }

    if (check_user == 0) {
        cout << "������� �� ����� �������� �� ������." << endl;
    }
    cout << "==============================" << endl << endl;
    cin.clear();
}

void find_amount_all(deposid* deps, int sum) {
    int count = 0;
    for (int j = 0; j < i; j++) {
        if (deps[j].amount >= sum) {
            cout << "����� ��������: " << deps[j].account_number << endl;
            cout << "���: " << deps[j].client_name << endl;
            cout << "�������: " << deps[j].client_surname << endl;
            cout << "��������: " << deps[j].client_patronymic << endl;
            cout.precision(2);
            cout << "����� ��������: " << fixed << deps[j].amount << " ���." << endl;
            cout << "���� ��������: " << deps[j].date_day << "." << deps[j].date_month << "." << deps[j].date_year << endl << endl;
            cout << "=======================================" << endl << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "��������� ���� ��������� ����� �� �������!" << endl;
    }

    count = 0;
    cin.clear();
}

void find_all_deposid(deposid* deps, string name, string surname, string patronymic) {
    cout << endl;
    cout << "==============================" << endl;
    cout << "���: " << name << endl;
    cout << "�������: " << surname << endl;
    cout << "��������: " << patronymic << endl;

    for (int j = 0; j < i; j++) {
        if ((string)name == (string)deps[j].client_name) {
            if ((string)surname == (string)deps[j].client_surname) {
                if ((string)patronymic == (string)deps[j].client_patronymic) {
                    cout << "--------------------" << endl;
                    cout << "����� ��������: " << deps[j].account_number << endl;
                    cout.precision(2);
                    cout << "����� ��������: " << fixed << deps[j].amount << " ���." << endl;
                    cout << "���� ��������: " << deps[j].date_day << "." << deps[j].date_month << "." << deps[j].date_year << endl << endl;
                    cout << "--------------------" << endl;
                }
            }
        }
    }
    cin.clear();
}

void menu(deposid* deps) {
    int sum;  // �����, ������ ������� ��������� ����� ������ �������� � ������� ��� ������� 3.
    int action;  // �����, ������� ����� ������������.

    int buffer_account_number = 0;                 // | � ��� ���������� ����� �������� ������, ������� ����� ������������.
    string buffer_name = "";          // | ����� ��������� �������� ���� �� � ����� �������� ������� � ����� �����.
    string buffer_surname = "";       // | ���� ������� ����, �� ��������� ��������� ������� ����� ���� � �����.
    string buffer_patronymic = "";   // | ���� � ������������ ��� ������ ������� � ���� �����, �� ������ � ���� ���������� ����� � ������ deps.
    int buffer_amount = 0;
    int buffer_date_day = 0;
    int buffer_date_month = 0;
    int buffer_date_year = 0;

    cout << "==============================" << endl;
    cout << "��������� ��������:" << endl;
    cout << "\t" << "1) �������� ����� ����." << endl;
    cout << "\t" << "2) ����������� ���������� � ����� � ��������� ����." << endl;
    cout << "\t" << "3) ���������� ��� ����� � ������ ������ ��������." << endl;
    cout << "\t" << "4) ����� ��� ����� ��������� ������� (�� ����� � �������)." << endl;
    cout << "\t" << "5) ����� �� ���������." << endl;
    cout << "==============================" << endl;
    cout << "������� ����� �� 1 �� 5: "; cin >> action;
    cout << "==============================" << endl << endl;

    if (action == 1) {
        if (create_deposid(deps, buffer_account_number, buffer_name, buffer_surname, buffer_patronymic, buffer_amount, buffer_date_day, buffer_date_month, buffer_date_year) == 1) {
            menu(deps);
        }
        menu(deps);
    }
    else if (action == 2) {
        cout << "������� ���, �������, �������� � ����� �������� ��� ������ ������." << endl;
        cout << "\t���: "; cin >> buffer_name; cin.ignore();
        cout << "\t�������: "; cin >> buffer_surname; cin.ignore();
        cout << "\t��������: "; cin >> buffer_patronymic; cin.ignore();
        cout << "\t����� ��������: "; cin >> buffer_amount; cin.ignore();
        cout << endl;
        show_deposid(deps, buffer_name, buffer_surname, buffer_patronymic, buffer_amount, buffer_date_day, buffer_date_month, buffer_date_year);
        menu(deps);
    }
    else if (action == 3) {
        cout << "������� �����, ���� ���� ������ ������� ���������� ����� ��������:" << endl;
        cout << "\t�����: "; cin >> sum; cin.ignore();
        find_amount_all(deps, sum);
        menu(deps);
    }
    else if (action == 4) {
        cout << "������� ���, ������� � �������� ��� ������ ������." << endl;
        cout << "���: "; cin >> buffer_name; cin.ignore();
        cout << "�������: "; cin >> buffer_surname; cin.ignore();
        cout << "��������: "; cin >> buffer_patronymic; cin.ignore();
        find_all_deposid(deps, buffer_name, buffer_surname, buffer_patronymic);
        menu(deps);
    }
    else if (action == 5) {
        cout << "���������� ���������..." << endl;
        exit(0);
    }
    else {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "�������� �� �������. ������� ���������� ��������..." << endl;
        menu(deps);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    system("chcp 1251");

    // ���-�� ����� � ����������� �����
    ifstream in(path);
    string s;
    while (in.peek() != EOF) {
        getline(in, s);
        i++;
    }

    int err_year = 0;

    deposid* deps = new deposid[N];  //  �������� ������, ���������� ��� ��������.

    int line_count = 0;
    string buffer; // ����� ��� ����� �� �����
    string tmp;
    int pos = 0;

    ifstream ff;
    ff.open(path);
    for (int j = 0; j < i; j++) {
        tmp = "";
        getline(ff, buffer);
        for (int k = 0; k < buffer.length(); k++) {
            if (!isspace(buffer[k])) {
                tmp += buffer[k];
                if (pos == 7) {
                    istringstream iss(tmp, istringstream::in);
                    iss >> deps[j].date_year;
                    err_year++;
                    if (err_year == 2) {
                        pos = 0;
                        tmp = "";
                        err_year = 0;
                    }
                }
            }
            else {
                if (pos == 0) {
                    istringstream iss(tmp, istringstream::in);
                    iss >> deps[j].account_number;
                    pos++;
                    tmp = "";
                }
                else if (pos == 1) {
                    deps[j].client_name = tmp;
                    pos++;
                    tmp = "";
                }
                else if (pos == 2) {
                    deps[j].client_surname = tmp;
                    pos++;
                    tmp = "";
                }
                else if (pos == 3) {
                    deps[j].client_patronymic = tmp;
                    pos++;
                    tmp = "";
                }
                else if (pos == 4) {
                    istringstream iss(tmp, istringstream::in);
                    iss >> deps[j].amount;
                    pos++;
                    tmp = "";
                }
                else if (pos == 5) {
                    istringstream iss(tmp, istringstream::in);
                    iss >> deps[j].date_day;
                    pos++;
                    tmp = "";
                }
                else if (pos == 6) {
                    istringstream iss(tmp, istringstream::in);
                    iss >> deps[j].date_month;
                    pos++;
                    tmp = "";
                }
            }
        }
    }

    ff.close();

    cout << endl << "����� ���������� � ��������� - ����." << endl << endl;

    menu(deps);

    delete[] deps;

    return 0;
}