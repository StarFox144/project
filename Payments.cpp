#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <vector>
#include <cpr/cpr.h>

using namespace Pistache;
using namespace std;

struct Booking {
    int id;
    int userId;
    int tourId;
    double price;
    string paymentStatus;
};

struct Payment {
    int id;
    Booking booking;
    double amount;
    string status;
};

vector<Payment> payments;

void handleGetPayment(const Rest::Request& request, Http::ResponseWriter response) {
    int paymentId = stoi(request.param(":id").as<string>());
    auto it = find_if(payments.begin(), payments.end(), [&](const Payment& payment) { return payment.id == paymentId; });

    if (it != payments.end()) {
        response.send(Http::Code::Ok, *it);
    } else {
        response.send(Http::Code::Not_Found, "Payment not found");
    }
}

void handleCreatePayment(const Rest::Request& request, Http::ResponseWriter response) {
    Payment payment;
    request.body().bind(&payment);

    // Отримати інформацію про бронювання з сервісу бронювань
    cpr::Response bookingResponse = cpr::Get(cpr::Url{"http://localhost:9082/bookings/" + to_string(payment.booking.id)});
    if (bookingResponse.status_code == 200) {
        payment.booking = bookingResponse.text;
        payment.amount = payment.booking.price;
        payment.
