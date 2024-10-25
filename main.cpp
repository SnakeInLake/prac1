#include "sql_parser.h"
#include "schema_creator.h" 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    if (!loadSchema("schema.json")) {
        cerr << "Ошибка загрузки схемы" << endl;
        return 1;
    }

    string schema_name = schema_data["name"];
    if (!createSchema("schema.json", schema_name)) {
        cerr << "Ошибка создания схемы" << endl;
        return 1;
    }

    string sql_query;

    while (true) {
        cout << "SQL> ";
        getline(cin, sql_query);

        if (sql_query == "exit") {
            break;
        }

        stringstream ss(sql_query);
        string command;
        ss >> command;

        if (command == "INSERT") {
            if (executeInsert(sql_query)) {
                cout << "Запрос INSERT выполнен успешно." << endl;
            }
        } else if (command == "DELETE") {
            if (executeDelete(sql_query)) {
                cout << "Запрос DELETE выполнен успешно." << endl;
            }
        } else if (command == "SELECT") {
            if (executeSelect(sql_query)) {
                cout << "Запрос SELECT выполнен успешно." << endl;
            }
        } else {
            cerr << "Ошибка: неизвестный тип запроса." << endl;
        }
    }

    return 0;
}
