#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
using namespace std;

struct Car {
    string name, model, country;
    int year, mileage, price, amount;
    double engine;
    Car* next;
};

void ReadCSV();
void WriteCSV();
void ShowElements(Car* first);
void AddElement();
void ClearElements();
Car* FindByName();
Car* FindByModel();
Car* FindByYear();
void PriceByYear();

Car* firstElement;
Car* lastElement;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ReadCSV();
    int cmd;
    Choice:
    cout << "Меню:" << endl;
    cout << "1. Вывести все записи." << endl;
    cout << "2. Добавить запись." << endl;
    cout << "3. Удалить все записи." << endl;
    cout << "4. Поиск по марке автомобиля." << endl;
    cout << "5. Поиск по модели автомобиля." << endl;
    cout << "6. Стоимость автомобилей по году." << endl;
    cout << "7. Сохранить записи." << endl;
    cout << "0. Выход." << endl;
    cout << "Выберите функцию по номеру: ";
    cin >> cmd;
    switch(cmd) {
        case 1:
            ShowElements(firstElement);
            goto Choice;
        case 2:
            AddElement();
            goto Choice;
        case 3:
            ClearElements();
            goto Choice;
        case 4:
            ShowElements(FindByName());
            goto Choice;
        case 5:
            ShowElements(FindByModel());
            goto Choice;
        case 6:
            PriceByYear();
            goto Choice;
        case 7:
            WriteCSV();
            goto Choice;
        default:
            ClearElements();
            return 0;
    }
}

void ReadCSV() {
    ifstream inData("D:/cpp/car-shop.csv");
    string data;
    while(getline(inData, data)) {
        stringstream str(data);
        string split;
        vector<string> carData;
        while(getline(str, split, ';')) {
            carData.push_back(split);
        }
        Car* temp = new Car;
        temp->name = carData.at(0);
        temp->model = carData.at(1);
        temp->country = carData.at(2);
        temp->year = stoi(carData.at(3));
        temp->engine = stod(carData.at(4));
        temp->mileage = stoi(carData.at(5));
        temp->price = stoi(carData.at(6));
        temp->amount = stoi(carData.at(7));
        temp->next = nullptr;
        if(!firstElement) {
            firstElement = temp;
        } else {
            lastElement->next = temp;
        }
        lastElement = temp;
    }
    inData.close();
}

void WriteCSV() {
    ofstream outData("D:/cpp/car-shop.csv");
    Car* first = firstElement;
    while(first) {
        outData << first->name << ";" << first->model << ";" << first->country << ";";
        outData << first->year << ";" << first->engine << ";" << first->mileage << ";";
        outData << first->price << ";" << first->amount << endl;
        first = first->next;
    }
    outData.close();
}

void ShowElements(Car* first) {
    if ((!first) == 1) {
        cout << "------------" << endl;
        cout << "Записей нет." << endl;
    } else {
        while (first) {
            cout << "------------" << endl;
            cout << "Марка: " << first->name << endl;
            cout << "Модель: " << first->model << endl;
            cout << "Страна: " << first->country << endl;
            cout << "Год выпуска: " << first->year << endl;
            cout << "Объем двигателя: " << first->engine << " л" << endl;
            cout << "Расход топлива: " << first->mileage << " л на 100 км" << endl;
            cout << "Стоимость: " << first->price << endl;
            cout << "Количество: " << first->amount << endl;
            first = first->next;
        }
    }
    cout << "------------" << endl;
    cout << "Введите любой символ, чтобы продолжить..." << endl;
    char next;
    cin >> next;
}

void AddElement() {
    Car* temp = new Car;
    cout << "Введите марку: ";
    cin >> temp->name;
    cout << "Введите модель: ";
    cin >> temp->model;
    cout << "Введите страну производитель: ";
    cin >> temp->country;
    cout << "Введите год выпуска: ";
    cin >> temp->year;
    cout << "Введите объем двигателя: ";
    cin >> temp->engine;
    cout << "Введите расход топлива: ";
    cin >> temp->mileage;
    cout << "Введите стоимость: ";
    cin >> temp->price;
    cout << "Введите количество: ";
    cin >> temp->amount;
    temp->next = nullptr;
    if(!firstElement) {
        firstElement = temp;
    } else {
        lastElement->next = temp;
    }
    lastElement = temp;
}

void ClearElements() {
    while(firstElement) {
        Car* temp = firstElement;
        firstElement = firstElement->next;
        delete temp;
    }
}

Car* FindByName() {
    Car* first = firstElement;
    Car* firstSublist = nullptr;
    Car* lastSublist;
    string name;
    cout << "Введите марку автомобиля: ";
    cin >> name;
    while(first) {
        if(first->name == name) {
            if(!firstSublist) {
                firstSublist = first;
            } else {
                lastSublist->next = first;
            }
            lastSublist = first;
        }
        first = first->next;
    }
    return firstSublist;
}

Car* FindByModel() {
    Car* first = firstElement;
    Car* firstSublist = nullptr;
    Car* lastSublist;
    string model;
    cout << "Введите модель автомобиля: ";
    cin >> model;
    while(first) {
        if(first->model == model) {
            if(!firstSublist) {
                firstSublist = first;
            } else {
                lastSublist->next = first;
            }
            lastSublist = first;
        }
        first = first->next;
    }
    return firstSublist;
}

Car* FindByYear() {
    Car* first = firstElement;
    Car* firstSublist = nullptr;
    Car* lastSublist;
    int year;
    cout << "Введите год выпуска автомобиля: ";
    cin >> year;
    while(first) {
        if(first->year == year) {
            if(!firstSublist) {
                firstSublist = first;
            } else {
                lastSublist->next = first;
            }
            lastSublist = first;
        }
        first = first->next;
    }
    return firstSublist;
}

void PriceByYear() {
    bool has = false;
    Car* first = FindByYear();
    if(!first) {
        cout << "Нет автомобилей этого года выпуска." << endl;
    } else {
        cout << "Цены на автомобили данного года выпуска:" << endl;
        while(first) {
            cout << "- " << first->price << endl;
            first = first->next;
        }
    }
    cout << "------------" << endl;
}
