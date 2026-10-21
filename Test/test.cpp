#include "pch.h"
#include "C:\opppo1\opppo1\vehicle.h"
#include <sstream>

// Тестирование вспомогательной функции сравнения чисел
TEST(CompareValuesTest, ValidAndInvalidOperations) {
    // Корректные операции
    EXPECT_TRUE(compareValues(100, ">", 50));
    EXPECT_TRUE(compareValues(50, "<", 100));
    EXPECT_TRUE(compareValues(70, "==", 70));
    EXPECT_TRUE(compareValues(70, ">=", 70));
    EXPECT_TRUE(compareValues(40, "<=", 50));

    // Некорректные или неподдерживаемые операторы (проверка исключительных ситуаций)
    EXPECT_FALSE(compareValues(100, "!=", 50));
    EXPECT_FALSE(compareValues(100, "UNKNOWN", 100));
    EXPECT_FALSE(compareValues(100, "", 100));
}

// Тестирование фильтрации по стране (Vehicle::checkCountry)
TEST(VehicleCountryTest, CountryFilter) {
    Truck truck(300, 5000, "Germany");

    EXPECT_TRUE(truck.checkCountry("==", "Germany"));
    EXPECT_FALSE(truck.checkCountry("==", "France"));
    EXPECT_TRUE(truck.checkCountry("!=", "USA"));
    EXPECT_FALSE(truck.checkCountry("!=", "Germany"));

    // Ошибочная строковая операция
    EXPECT_FALSE(truck.checkCountry(">", "Germany"));
}

// Тестирование проверок для класса Truck
TEST(TruckTest, CheckParameters) {
    Truck truck(450, 12000, "Sweden");

    EXPECT_TRUE(truck.check("POWER", ">", 400));
    EXPECT_TRUE(truck.check("LOAD", "==", 12000));
    EXPECT_FALSE(truck.check("LOAD", "<", 10000));

    // Несуществующие параметры
    EXPECT_FALSE(truck.check("DOORS", "==", 4));
}

// Тестирование проверок для класса Bus
TEST(BusTest, CheckParameters) {
    Bus bus(250, 50, "Poland");

    EXPECT_TRUE(bus.check("POWER", "==", 250));
    EXPECT_TRUE(bus.check("PASSENGERS", ">=", 50));
    EXPECT_FALSE(bus.check("LOAD", ">", 1000));
}

// Тестирование проверок для класса PassengerCar
TEST(PassengerCarTest, CheckParameters) {
    PassengerCar car(150, 4, 210, "Japan");

    EXPECT_TRUE(car.check("POWER", ">=", 150));
    EXPECT_TRUE(car.check("DOORS", "==", 4));
    EXPECT_TRUE(car.check("SPEED", ">", 200));
    EXPECT_FALSE(car.check("PASSENGERS", "==", 4));
}

// Тестирование форматированного вывода print()
TEST(VehiclePrintTest, OutputFormat) {
    Truck truck(400, 8000, "Germany");
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    truck.print();
    EXPECT_EQ(buffer.str(), "Truck: Power=400, Load=8000 kg, Country=Germany\n");

    std::cout.rdbuf(oldCout);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}