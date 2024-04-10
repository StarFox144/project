#include "crow.h"
#include <vector>
#include <string>

struct User {
    std::string id;
    std::string name;
    std::string email;
};

std::vector<User> users;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/users")
        ([](const crow::request& req) {
        if (req.method() == "POST"_method) {
            auto x = crow::json::load(req.body);
            User user;
            user.id = x["id"].s();
            user.name = x["name"].s();
            user.email = x["email"].s();
            users.push_back(user);
            return crow::response(crow::status::CREATED, crow::json::wvalue(user));
        }
        else {
            std::vector<crow::json::wvalue> userList;
            for (const auto& user : users) {
                userList.push_back(crow::json::wvalue(user));
            }
            return crow::response(crow::json::wvalue(userList));
        }
            });

    CROW_ROUTE(app, "/users/<string>")
        ([](const crow::request& req, std::string userId) {
        for (const auto& user : users) {
            if (user.id == userId) {
                return crow::response(crow::json::wvalue(user));
            }
        }
        return crow::response(crow::status::NOT_FOUND, "User not found");
            });

    app.port(3000).run();
    return 0;
}