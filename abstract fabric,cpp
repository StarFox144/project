#include <iostream>
#include <memory>

// Абстрактні класи для турів, готелів та транспорту
class Tour {
public:
    virtual void display() = 0;
    virtual ~Tour() {}
};

class Hotel {
public:
    virtual void display() = 0;
    virtual ~Hotel() {}
};

class Transport {
public:
    virtual void display() = 0;
    virtual ~Transport() {}
};

// Конкретні класи турів, готелів та транспорту для конкретного типу турів
class CityTour : public Tour {
public:
    void display() override {
        std::cout << "City Tour\n";
    }
};

class BeachHotel : public Hotel {
public:
    void display() override {
        std::cout << "Beach Hotel\n";
    }
};

class BusTransport : public Transport {
public:
    void display() override {
        std::cout << "Bus Transport\n";
    }
};

// Абстрактна фабрика
class TravelFactory {
public:
    virtual std::unique_ptr<Tour> createTour() = 0;
    virtual std::unique_ptr<Hotel> createHotel() = 0;
    virtual std::unique_ptr<Transport> createTransport() = 0;
    virtual ~TravelFactory() {}
};

// Конкретні фабрики для різних типів турів
class CityTravelFactory : public TravelFactory {
public:
    std::unique_ptr<Tour> createTour() override {
        return std::make_unique<CityTour>();
    }

    std::unique_ptr<Hotel> createHotel() override {
        return std::make_unique<BeachHotel>();
    }

    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<BusTransport>();
    }
};

int main() {
    // Використання абстрактної фабрики
    std::unique_ptr<TravelFactory> cityFactory = std::make_unique<CityTravelFactory>();
    std::unique_ptr<Tour> tour = cityFactory->createTour();
    std::unique_ptr<Hotel> hotel = cityFactory->createHotel();
    std::unique_ptr<Transport> transport = cityFactory->createTransport();

    // Виведення інформації про тур, готель та транспорт
    tour->display();
    hotel->display();
    transport->display();

    return 0;
}
