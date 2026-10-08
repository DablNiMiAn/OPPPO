#include "vehicle.h"

// Универсальное сравнение чисел
bool compareValues(int actual, const std::string& op, int expected) {
    if (op == ">")  return actual > expected;
    if (op == "<")  return actual < expected;
    if (op == "==") return actual == expected;
    if (op == ">=") return actual >= expected;
    if (op == "<=") return actual <= expected;
    return false;
}

// Vehicle
Vehicle::Vehicle(int p, const std::string& c)
    : power(p), country(c) {}

bool Vehicle::check(const std::string& parameter, const std::string& operation, int value) const {
    if (parameter == "POWER") {
        return compareValues(power, operation, value);
    }
    return false;
}

bool Vehicle::checkCountry(const std::string& operation, const std::string& value) const {
    if (operation == "==") return country == value;
    if (operation == "!=") return country != value;
    return false;
}

// Truck
Truck::Truck(int p, int l, const std::string& c)
    : Vehicle(p, c), load(l) {}

void Truck::print() const {
    std::cout << "Truck: Power=" << power << ", Load=" << load
        << " kg, Country=" << country << '\n';
}

bool Truck::check(const std::string& parameter, const std::string& operation, int value) const {
    if (Vehicle::check(parameter, operation, value)) return true;
    if (parameter == "LOAD") return compareValues(load, operation, value);
    return false;
}

// Bus
Bus::Bus(int p, short pass, const std::string& c)
    : Vehicle(p, c), passengers(pass) {}

void Bus::print() const {
    std::cout << "Bus: Power=" << power << ", Passengers=" << passengers
        << ", Country=" << country << '\n';
}

bool Bus::check(const std::string& parameter, const std::string& operation, int value) const {
    if (Vehicle::check(parameter, operation, value)) return true;
    if (parameter == "PASSENGERS") return compareValues(passengers, operation, value);
    return false;
}

// PassengerCar
PassengerCar::PassengerCar(int p, int d, int s, const std::string& c)
    : Vehicle(p, c), doors(d), maxSpeed(s) {}

void PassengerCar::print() const {
    std::cout << "Passenger car: Power=" << power << ", Doors=" << doors
        << ", Max speed=" << maxSpeed << " km/h, Country=" << country << '\n';
}

bool PassengerCar::check(const std::string& parameter, const std::string& operation, int value) const {
    if (Vehicle::check(parameter, operation, value)) return true;
    if (parameter == "DOORS") return compareValues(doors, operation, value);
    if (parameter == "SPEED") return compareValues(maxSpeed, operation, value);
    return false;
}