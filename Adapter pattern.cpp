#include <iostream>

// Інтерфейс, який використовується цільовою системою
class TourPackage {
public:
    virtual void book() = 0;
};

// Клас, який потрібно адаптувати
class ExternalBookingService {
public:
    void makeBooking() {
        std::cout << "ExternalBookingService: makeBooking called" << std::endl;
    }
};

// Адаптер, який наслідується від цільового інтерфейсу та містить посилання на адаптований об'єкт
class ExternalBookingServiceAdapter : public TourPackage {
private:
    ExternalBookingService* externalService;

public:
    ExternalBookingServiceAdapter(ExternalBookingService* externalService) : externalService(externalService) {}

    void book() override {
        std::cout << "TourPackage: book called. Delegating to ExternalBookingService's makeBooking." << std::endl;
        externalService->makeBooking();
    }
};

int main() {
    ExternalBookingService* externalService = new ExternalBookingService();
    TourPackage* tourPackage = new ExternalBookingServiceAdapter(externalService);

    tourPackage->book();

    delete tourPackage;
    delete externalService;

    return 0;
}