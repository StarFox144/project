#include <iostream>
#include <string>

// Клас, що представляє тур (прототип)
class Tour {
public:
    virtual Tour* clone() = 0;
    virtual void display() const = 0;
    virtual ~Tour() {}
};

// Конкретний клас туру (пляжний тур)
class BeachTour : public Tour {
public:
    Tour* clone() override {
        return new BeachTour(*this);
    }

    void display() const override {
        std::cout << "Beach Tour" << std::endl;
    }

    // Інші методи та поля класу BeachTour
};

// Клас туриста, який використовує прототип для створення туру
class Tourist {
public:
    Tour* createTour(Tour* prototype) {
        return prototype->clone();
    }
};

int main() {
    // Приклад використання паттерна прототипу

    Tourist tourist;

    // Створення прототипу пляжного туру
    Tour* beachTourPrototype = new BeachTour();

    // Створення нового туру на основі прототипу
    Tour* newBeachTour = tourist.createTour(beachTourPrototype);

    // Відображення створеного туру
    newBeachTour->display();

    // Звільнення ресурсів
    delete beachTourPrototype;
    delete newBeachTour;

    return 0;
}
