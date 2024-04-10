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

vector<User> users;

void handleGetUser(const Rest::Request& request, Http::ResponseWriter response) {
    int userId = stoi(request.param(":id").as<string>());
    auto it = find_if(users.begin(), users.end(), [&](const User& user) { return user.id == userId; });

    if (it != users.end()) {
        response.send(Http::Code::Ok, *it);
    } else {
        response.send(Http::Code::Not_Found, "User not found");
    }
}

void handleCreateUser(const Rest::Request& request, Http::ResponseWriter response) {
    User user;
    request.body().bind(&user);
    user.id = users.size() + 1;
    users.push_back(user);
    response.send(Http::Code::Created, user);
}

int main() {
    Address addr(Ipv4::any(), Port(9080));
    auto server = std::make_shared<Http::Endpoint>(addr);

    Rest::Router router;
    Rest::Routes::Get(router, "/users/:id", &handleGetUser);
    Rest::Routes::Post(router, "/users", &handleCreateUser);

    server->init(router);
    server->serveThreaded();

    return 0;
}
