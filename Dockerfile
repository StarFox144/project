# Використовуємо офіційний образ C++ з Docker Hub
FROM gcc:latest

# Копіюємо файли з вашого проекту в контейнер
COPY . /app

# Вказуємо робочий каталог
WORKDIR /app

# Компілюємо ваш С++ код
RUN g++ -o myapp main.cpp

# Експонуємо порт 8080
EXPOSE 5672

# Команда, яка виконується при запуску контейнера
CMD ["./myapp"]
