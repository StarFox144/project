#include <iostream>

class TouristCompany {
private:
    static TouristCompany* instance;

    // Приватний конструктор
    TouristCompany() {}

public:
    // Статичний метод для отримання єдиного екземпляра
    static TouristCompany* getInstance() {
        if (instance == nullptr) {
            instance = new TouristCompany();
        }
        return instance;
    }

    // Додаткові методи класу туристичної компанії
    // ...

    // Деструктор
    ~TouristCompany() {
        delete instance;
    }
};

TouristCompany* TouristCompany::instance = nullptr;

int main() {
    TouristCompany* company1 = TouristCompany::getInstance();
    TouristCompany* company2 = TouristCompany::getInstance();

    // Перевірка, що обидва вказівники вказують на один і той самий об'єкт
    if (company1 == company2) {
        std::cout << "company1 і company2 вказують на один і той самий об'єкт" << std::endl;
    }

    return 0;
}