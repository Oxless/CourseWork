//Молотков В.Н. 19ВИ2 Тема: Автомагазин
//Чтение данных из входного файла, добавление, удаление, поиск элементов списка, составление подсписков.
//Содержимое файла: марка автомобиля, модель автомобиля, страна производитель, год выпуска, объем двигателя, расход топлива, стоимость, количество выпущенных экземпляров.
//Дополнительные функции: поиск по марке автомобиля, по модели автомобиля, поиск стоимости автомобиля по году выпуска. 
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Car {
    string name, model, country;
    int year, mileage, price, amount;
    double engine;
    Car* next;
};

void ReadFile();
void WriteFile();
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
    ReadFile();
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
    if(cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        goto Choice;
    }
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
            WriteFile();
            goto Choice;
        default:
            ClearElements();
            return 0;
    }
}

void ReadFile() {
    ifstream inData("D:/cpp/car-shop.txt");
    while(!inData.eof()) {
        Car* temp = new Car;
        inData >> temp->name;
        inData >> temp->model;
        inData >> temp->country;
        inData >> temp->year;
        inData >> temp->engine;
        inData >> temp->mileage;
        inData >> temp->price;
        inData >> temp->amount;
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

void WriteFile() {
    ofstream outData("D:/cpp/car-shop.txt");
    Car* first = firstElement;
    while(first) {
        outData << first->name << "\n" << first->model << "\n" << first->country << "\n";
        outData << first->year << "\n" << first->engine << "\n" << first->mileage << "\n";
        outData << first->price << "\n" << first->amount << endl;
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
    cin.ignore(32767, '\n');
}

void AddElement() {
    Input:
    Car* temp = new Car;
    cin.exceptions(cin.failbit | cin.badbit);
    try {
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
    } catch(ios_base::failure e) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Одна из характеристик введена некорректно. Попробуйте снова." << endl;
        goto Input;
    }
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
    Input:
    cout << "Введите год выпуска автомобиля: ";
    cin >> year;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Вы ввели некорректное значение года выпуска." << endl;
        goto Input;
    }
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
