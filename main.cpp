#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream> 
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "\n    Приветствую на игре 'Угадай число'!" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "    Как играть? Игра 'Угадай число' - компьютер" << endl;
    cout << "    загадывает число, пользователь пытается угадать." << endl;
    cout << "    При этом подсчитывается количество" << endl;
    cout << "    попыток и формируется таблица рекордов." << endl;
    cout << "------------------------------------------------\n" << endl;


    ifstream inFile("records.txt");
    string names[10];
    int attempts[10];
    int count = 0;
    
    if (inFile.is_open()) {
        while (inFile >> names[count] >> attempts[count] && count < 10) {
            count++;
        }
        inFile.close();
    }

    srand(time(nullptr));
    const int random_value = rand() % 100;
    int x;
    int attemptCount = 1; 
    string name;
    
    cout << "Введите ваше имя (на английском): ";
    cin >> name;
    cout << "Введите число: ";
    cin >> x;
    
    while (x != random_value) {
        if (x < random_value) {
            cout << "Больше чем " << x << endl;
            attemptCount++;
        } else {
            cout << "Меньше чем " << x << endl;
            attemptCount++;
        }
        cout << "Введите число: ";
        cin >> x;
    }
    
    cout << "Верно! Вы победили! Попыток: " << attemptCount << endl;
    
    names[count] = name;
    attempts[count] = attemptCount;
    count++;
    
    ofstream outFile("records.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < count; i++) {
            outFile << names[i] << " " << attempts[i] << endl;
        }
        outFile.close();
    }
    
    cout << "--------------------------" << endl;
    cout << "|   Таблица рекордов     |" << endl;
    cout << "--------------------------" << endl;
    
    for (int i = 0; i < count; i++) {
        cout << "| " << setw(10) << left << names[i] 
             << " | " << setw(9) << attempts[i] << " |" << endl;
    }
    
    cout << "---------------------------" << endl;

    return 0;
}

