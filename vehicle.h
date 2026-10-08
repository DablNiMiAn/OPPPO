#pragma once

#include <string>
#include <iostream>

// Общая функция сравнения, чтобы не дублировать код в классах
bool compareValues(int actual, const std::string& op, int expected);

// Базовый класс для транспорта
class Vehicle {
protected:
    int power;
    std::string country;

public:
    Vehicle(int p, const std::string& c);
    virtual ~Vehicle() = default;

    virtual void print() const = 0;
    virtual bool check(const std::string& parameter, const std::string& operation, int value) const;
    virtual bool checkCountry(const std::string& operation, const std::string& value) const;
};

// Грузовик
class Truck : public Vehicle {
private:
    int load;

public:
    Truck(int p, int l, const std::string& c);
    void print() const override;
    bool check(const std::string& parameter, const std::string& operation, int value) const override;
};

// Автобус
class Bus : public Vehicle {
private:
    short passengers;

public:
    Bus(int p, short pass, const std::string& c);
    void print() const override;
    bool check(const std::string& parameter, const std::string& operation, int value) const override;
};

// Легковой автомобиль
class PassengerCar : public Vehicle {
private:
    int doors;
    int maxSpeed;

public:
    PassengerCar(int p, int d, int s, const std::string& c);
    void print() const override;
    bool check(const std::string& parameter, const std::string& operation, int value) const override;
};