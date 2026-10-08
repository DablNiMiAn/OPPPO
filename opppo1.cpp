#include "Vehicle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream file("commands.txt");

    if (!file.is_open()) {
        cout << "File not found!" << endl;
        return 1;
    }

    // Обычный список указателей на транспорт
    vector<Vehicle*> vehicles;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string command;
        ss >> command;

        // Команда ADD
        if (command == "ADD") {
            string type;
            ss >> type;

            if (type == "TRUCK") {
                int power, load;
                string country;
                ss >> power >> load >> country;
                vehicles.push_back(new Truck(power, load, country));
            }
            else if (type == "BUS") {
                int power;
                short passengers;
                string country;
                ss >> power >> passengers >> country;
                vehicles.push_back(new Bus(power, passengers, country));
            }
            else if (type == "CAR") {
                int power, doors, speed;
                string country;
                ss >> power >> doors >> speed >> country;

                if (doors >= 2 && doors <= 5) {
                    vehicles.push_back(new PassengerCar(power, doors, speed, country));
                }
                else {
                    cout << "Wrong number of doors!" << endl;
                }
            }
        }
        // Команда REM
        else if (command == "REM") {
            string parameter, operation, value;
            ss >> parameter >> operation >> value;

            if (parameter == "COUNTRY") {
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
            else {
                int number = stoi(value);
                for (size_t i = 0; i < vehicles.size(); ) {
                    if (vehicles[i]->check(parameter, operation, number)) {
                        delete vehicles[i];
                        vehicles.erase(vehicles.begin() + i);
                    }
                    else {
                        i++;
                    }
                }
            }
        }
        // Команда PRINT
        else if (command == "PRINT") {
            for (size_t i = 0; i < vehicles.size(); i++) {
                vehicles[i]->print();
            }
        }
    }

    file.close();

    // Очищаем оставшуюся память перед выходом
    for (size_t i = 0; i < vehicles.size(); i++) {
        delete vehicles[i];
    }

    return 0;
}