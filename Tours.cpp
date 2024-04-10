#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <vector>

using namespace Pistache;
using namespace std;

struct Tour {
    int id;
    string destination;
    double price;
};

vector<Tour> tours;

void handleGetTour(const Rest::Request& request, Http::ResponseWriter response) {
    int tourId = stoi(request.param(":id").as<string>());
    auto it = find_if(tours.begin(), tours.end(), [&](const Tour& tour) { return tour.id == tourId; });

    if (it != tours.end()) {
        response.send(Http::Code::Ok, *it);
    } else {
        response.send(Http::Code::Not_Found, "Tour not found");
    }
}

void handleCreateTour(const Rest::Request& request, Http::ResponseWriter response) {
    Tour tour;
    request.body().bind(&tour);
    tour.id = tours.size() + 1;
    tours.push_back(tour);
    response.send(Http::Code::Created, tour);
}

int main() {
    Address addr(Ipv4::any(), Port(9081));
    auto server = std::make_shared<Http::Endpoint>(addr);

    Rest::Router router;
    Rest::Routes::Get(router, "/tours/:id", &handleGetTour);
    Rest::Routes::Post(router, "/tours", &handleCreateTour);

    server->init(router);
    server->serveThreaded();

    return 0;
}
