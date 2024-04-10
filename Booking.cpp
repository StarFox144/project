#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <vector>
#include <cpr/cpr.h>

using namespace Pistache;
using namespace std;

struct User {
    int id;
    string name;
    string email;
};

struct Tour {
    int id;
    string destination;
    double price;
};

struct Booking {
    int id;
    User user;
    Tour tour;
    string paymentStatus;
};

vector<Booking> bookings;

void handleGetBooking(const Rest::Request& request, Http::ResponseWriter response) {
    int bookingId = stoi(request.param(":id").as<string>());
    auto it = find_if(bookings.begin(), bookings.end(), [&](const Booking& booking) { return booking.id == bookingId; });

    if (it != bookings.end()) {
        response.send(Http::Code::Ok, *it);
    }
    else {
        response.send(Http::Code::Not_Found, "Booking not found");
    }
}

void handleCreateBooking(const Rest::Request& request, Http::ResponseWriter response) {
    Booking booking;
    request.body().bind(&booking);

    // Отримати інформацію про користувача з сервісу користувачів
    cpr::Response userResponse = cpr::Get(cpr::Url{ "http://localhost:9080/users/" + to_string(booking.user.id) });
    if (userResponse.status_code == 200) {
        booking.user = userResponse.text;
    }
    else {
        response.send(Http::Code::Bad_Request, "User not found");
        return;
    }

    // Отримати інформацію про тур з сервісу турів
    cpr::Response tourResponse = cpr::Get(cpr::Url{ "http://localhost:9081/tours/" + to_string(booking.tour.id) });
    if (tourResponse.status_code == 200) {
        booking.tour = tourResponse.text;
    }
    else {
        response.send(Http::Code::Bad_Request, "Tour not found");
        return;
    }

    booking.id = bookings.size() + 1;
    booking.paymentStatus = "pending";
    bookings.push_back(booking);
    response.send(Http::Code::Created, booking);
}

int main() {
    Address addr(Ipv4::any(), Port(9082));
    auto server = std::make_shared<Http::Endpoint>(addr);

    Rest::Router router;
    Rest::Routes::Get(router, "/bookings/:id", &handleGetBooking);
    Rest::Routes::Post(router, "/bookings", &handleCreateBooking);

    server->init(router);
    server->serveThreaded();

    return 0;
}