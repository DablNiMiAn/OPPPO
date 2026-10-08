#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


// Общий класс для транспорта
class Vehicle {
protected:
    int power;
    string country;

public:
    Vehicle(int p, const string& c)
        : power(p), country(c) {}

    virtual void print() {
        cout << "Power: " << power
            << ", Country: " << country;
    }

    virtual bool check(const string& parameter, const string& operation, int value) {
        return false;
    }

    virtual bool checkCountry(const string& operation, const string& value) {
        return false;
    }

    virtual ~Vehicle() {}
};


// Грузовик
class Truck : public Vehicle {
private:
    int load;

public:
    Truck(int p, int l, const string& c)
        : Vehicle(p, c), load(l) {}

    void print() override {
        cout << "Truck: "
            << "Power=" << power
            << ", Load=" << load
            << " kg, Country=" << country
            << endl;
    }

    bool check(const string& parameter, const string& operation, int value) override {

        int x = 0;

        if (parameter == "POWER")
            x = power;
        else if (parameter == "LOAD")
            x = load;
        else
            return false;

        if (operation == ">")
            return x > value;
        if (operation == "<")
            return x < value;
        if (operation == "==")
            return x == value;
        if (operation == ">=")
            return x >= value;
        if (operation == "<=")
            return x <= value;

        return false;
    }

    bool checkCountry(const string& operation, const string& value) override {
        if (operation == "==")
            return country == value;

        if (operation == "!=")
            return country != value;

        return false;
    }
};


// Автобус
class Bus : public Vehicle {
private:
    short passengers;

public:
    Bus(int p, short pass, const string& c)
        : Vehicle(p, c), passengers(pass) {}

    void print() override {
        cout << "Bus: "
            << "Power=" << power
            << ", Passengers=" << passengers
            << ", Country=" << country
            << endl;
    }

    bool check(const string& parameter, const string& operation, int value) override {

        int x = 0;

        if (parameter == "POWER")
            x = power;
        else if (parameter == "PASSENGERS")
            x = passengers;
        else
            return false;

        if (operation == ">")
            return x > value;
        if (operation == "<")
            return x < value;
        if (operation == "==")
            return x == value;
        if (operation == ">=")
            return x >= value;
        if (operation == "<=")
            return x <= value;

        return false;
    }

    bool checkCountry(const string& operation, const string& value) override {
        if (operation == "==")
            return country == value;

        if (operation == "!=")
            return country != value;

        return false;
    }
};


// Легковой автомобиль
class PassengerCar : public Vehicle {
private:
    int doors;
    int maxSpeed;

public:
    PassengerCar(int p, int d, int s, const string& c)
        : Vehicle(p, c), doors(d), maxSpeed(s) {}

    void print() override {
        cout << "Passenger car: "
            << "Power=" << power
            << ", Doors=" << doors
            << ", Max speed=" << maxSpeed
            << " km/h, Country=" << country
            << endl;
    }

    bool check(const string& parameter, const string& operation, int value) override {

        int x = 0;

        if (parameter == "POWER")
            x = power;
        else if (parameter == "DOORS")
            x = doors;
        else if (parameter == "SPEED")
            x = maxSpeed;
        else
            return false;

        if (operation == ">")
            return x > value;
        if (operation == "<")
            return x < value;
        if (operation == "==")
            return x == value;
        if (operation == ">=")
            return x >= value;
        if (operation == "<=")
            return x <= value;

        return false;
    }

    bool checkCountry(const string& operation, const string& value) override {
        if (operation == "==")
            return country == value;

        if (operation == "!=")
            return country != value;

        return false;
    }
};


// Контейнер
class Container {
private:
    vector<Vehicle*> vehicles;

public:

    // Добавить автомобиль
    void add(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }


    // Показать все автомобили
    void print() {
        for (size_t i = 0; i < vehicles.size(); i++) {
            vehicles[i]->print();
        }
    }


    // Удалить автомобили по числовому условию
    void remove(const string& parameter, const string& operation, int value) {

        for (size_t i = 0; i < vehicles.size(); ) {

            if (vehicles[i]->check(parameter, operation, value)) {

                delete vehicles[i];

                vehicles.erase(vehicles.begin() + i);
            }
            else {
                i++;
            }
        }
    }


    // Удалить автомобили по стране
    void removeCountry(const string& operation, const string& value) {

        for (size_t i = 0; i < vehicles.size(); ) {

            if (vehicles[i]->checkCountry(operation, value)) {

                delete vehicles[i];

                vehicles.erase(vehicles.begin() + i);
            }
            else {
                i++;
            }
        }
    }


    // Освободить память
    ~Container() {

        for (size_t i = 0; i < vehicles.size(); i++) {
            delete vehicles[i];
        }
    }
};


// Главная функция
int main() {

    ifstream file("commands.txt");

    if (!file.is_open()) {
        cout << "File not found!" << endl;
        return 1;
    }

    Container container;

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        string command;
        ss >> command;


        // ADD
        if (command == "ADD") {

            string type;
            ss >> type;


            // Добавляем грузовик
            if (type == "TRUCK") {

                int power;
                int load;
                string country;

                ss >> power >> load >> country;

                container.add(
                    new Truck(power, load, country)
                );
            }


            // Добавляем автобус
            else if (type == "BUS") {

                int power;
                short passengers;
                string country;

                ss >> power >> passengers >> country;

                container.add(
                    new Bus(power, passengers, country)
                );
            }


            // Добавляем легковой автомобиль
            else if (type == "CAR") {

                int power;
                int doors;
                int speed;
                string country;

                ss >> power >> doors >> speed >> country;

                if (doors == 2 ||
                    doors == 3 ||
                    doors == 4 ||
                    doors == 5) {

                    container.add(
                        new PassengerCar(
                            power,
                            doors,
                            speed,
                            country
                        )
                    );
                }
                else {
                    cout << "Wrong number of doors!" << endl;
                }
            }
        }


        // REM
        else if (command == "REM") {

            string parameter;
            string operation;
            string value;

            ss >> parameter >> operation >> value;


            if (parameter == "COUNTRY") {

                container.removeCountry(
                    operation,
                    value
                );
            }
            else {

                int number = stoi(value);

                container.remove(
                    parameter,
                    operation,
                    number
                );
            }
        }


        // PRINT
        else if (command == "PRINT") {

            container.print();
        }
    }

    file.close();

    return 0;
}