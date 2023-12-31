#include <iostream>
#include <memory>

// Абстрактний клас для турів
class Tour {
public:
    virtual void display() = 0;
    virtual ~Tour() {}
};

// Конкретні класи турів
class ExcursionTour : public Tour {
public:
    void display() override {
        std::cout << "Екскурсійний тур\n";
    }
};

class VacationTour : public Tour {
public:
    void display() override {
        std::cout << "Тур для відпочинку\n";
    }
};

class CulturalTour : public Tour {
public:
    void display() override {
        std::cout << "Культурний тур\n";
    }
};

// Абстрактна фабрика турів
class TourFactory {
public:
    virtual std::unique_ptr<Tour> createTour() = 0;
    virtual ~TourFactory() {}
};

// Конкретні фабрики турів
class ExcursionTourFactory : public TourFactory {
public:
    std::unique_ptr<Tour> createTour() override {
        return std::make_unique<ExcursionTour>();
    }
};

class VacationTourFactory : public TourFactory {
public:
    std::unique_ptr<Tour> createTour() override {
        return std::make_unique<VacationTour>();
    }
};

class CulturalTourFactory : public TourFactory {
public:
    std::unique_ptr<Tour> createTour() override {
        return std::make_unique<CulturalTour>();
    }
};

int main() {
    // Використання фабрик для створення турів
    std::unique_ptr<TourFactory> excursionFactory = std::make_unique<ExcursionTourFactory>();
    std::unique_ptr<Tour> excursionTour = excursionFactory->createTour();
    excursionTour->display();

    std::unique_ptr<TourFactory> vacationFactory = std::make_unique<VacationTourFactory>();
    std::unique_ptr<Tour> vacationTour = vacationFactory->createTour();
    vacationTour->display();

    std::unique_ptr<TourFactory> culturalFactory = std::make_unique<CulturalTourFactory>();
    std::unique_ptr<Tour> culturalTour = culturalFactory->createTour();
    culturalTour->display();

    return 0;
}
