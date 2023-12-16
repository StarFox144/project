#include <iostream>
#include <string>

// Клас, що представляє тур
class Tour {
public:
    void setDestination(const std::string& destination) {
        destination_ = destination;
    }

    void setDuration(int duration) {
        duration_ = duration;
    }

    void setCost(double cost) {
        cost_ = cost;
    }

    void display() const {
        std::cout << "Tour to " << destination_ << " (" << duration_ << " days) - Cost: $" << cost_ << std::endl;
    }

private:
    std::string destination_;
    int duration_;
    double cost_;
};

// Базовий клас для будівництва турів
class TourBuilder {
public:
    virtual void buildDestination() = 0;
    virtual void buildDuration() = 0;
    virtual void buildCost() = 0;
    virtual Tour* getResult() = 0;
    virtual ~TourBuilder() {}
};

// Конкретний клас білдера для пляжного туру
class BeachTourBuilder : public TourBuilder {
private:
    Tour* tour;

public:
    BeachTourBuilder() : tour(nullptr) {
        tour = new Tour();
    }

    void buildDestination() override {
        tour->setDestination("Beach Resort");
    }

    void buildDuration() override {
        tour->setDuration(7);
    }

    void buildCost() override {
        tour->setCost(1000.0);
    }

    Tour* getResult() override {
        return tour;
    }

    ~BeachTourBuilder() {
        delete tour;
    }
};

// Клас туриста, який використовує білдера для створення туру
class Tourist {
public:
    Tour* createTour(TourBuilder* builder) {
        builder->buildDestination();
        builder->buildDuration();
        builder->buildCost();
        return builder->getResult();
    }
};

int main() {
    // Приклад використання

    Tourist tourist;

    // Створення пляжного туру
    TourBuilder* beachTourBuilder = new BeachTourBuilder();
    Tour* beachTour = tourist.createTour(beachTourBuilder);

    // Відображення створеного туру
    beachTour->display();

    // Звільнення ресурсів
    delete beachTourBuilder;
    delete beachTour;

    return 0;
}
