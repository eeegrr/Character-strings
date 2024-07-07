#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct BusRoute {
    std::string start;
    std::string end;
    std::string day;
    std::string time;
    double price;
};

std::string trim(const std::string &str) {
    size_t start = str.find_first_not_of(" \t\n\r"); // searches first index
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r"); //searches last index
    return str.substr(start, end - start + 1); // returns all text without spaces
}

std::vector<BusRoute> create_routes() {
    std::vector<BusRoute> routes; 
    std::ifstream input {"db.csv"}; 
    std::ofstream error_file {"err.txt"};
    std::string line, word;
    BusRoute route;

    if (!input) {
        std::cerr << "Unable to open db.csv\n";
        throw;
    }

    while (std::getline(input, line)) {
        // skip empthy lines
        if (line.empty()) continue;

        std::stringstream s(line);
        std::vector<std::string> items;

        while (std::getline(s, word, ',')) {
            items.push_back(trim(word));
        }

        bool valid = true;
        if (items.size() != ) {
            valid = false;
        } else {
            route.start = items[0];
            route.end = items[1];
            route.day = items[2];
            route.time = items[3];

            // price double
            try {
                route.price = std::stod(items[4]);
            } catch (const std::invalid_argument &e) {
                valid = false;
            }
        }

        if (valid && (route.day.length() != 2 || route.time.length() != 5 || route.time[2] != ':')) {
            valid = false;
        }

        for (char c : route.time) {
            if (!isdigit(c) && c != ':') {
                valid = false;
            }
        }

        if (!valid) {
            error_file << line << "\n";
        } else {
            routes.push_back(route);
        }
    }
    return routes;
}
// output route
void display_route(const BusRoute &route) {
    std::cout << route.start << " " << route.end << " " << route.day << " " << route.time << " " << std::fixed
              << std::setprecision(2) << route.price << "\n";
}

// route start and end point
void query_a(const std::vector<BusRoute> &routes) {
    std::string start, end;
    std::cin >> start;
    std::cin >> end;
    std::cout << "result:\n";
    for (const auto &route : routes) {
        if (route.start == start && route.end == end) {
            display_route(route);
        }
    }
}

// route in expected day
void query_b(const std::vector<BusRoute> &routes) {
    std::string day;
    std::cin >> day;
    std::cout << "result:\n";
    for (const auto &route : routes) {
        if (route.day == day) {
            display_route(route);
        }
    }
}

// route by price
void query_c(const std::vector<BusRoute> &routes) {
    double price;
    std::cin >> price;
    std::cout << "result:\n";
    std::set<std::string> uniqueRouteIdentifiers;

    for (const auto &route : routes) {
        if (route.price <= price) {
            std::string routeIdentifier = route.start + route.end + route.day + route.time;
            if (uniqueRouteIdentifiers.find(routeIdentifier) == uniqueRouteIdentifiers.end()) {
                uniqueRouteIdentifiers.insert(routeIdentifier);
                display_route(route);
            }
        }
    }
}

//error cases
void query_d() {
    std::ifstream error_file {"err.txt"};
    std::string line;
    if (!error_file) {
        std::cerr << "Unable to open err.txt\n";
        throw;
    }

    std::cout << "result:\n";
    while (std::getline(error_file, line)) {
        std::string trimmed_line = trim(line);
        if (!trimmed_line.empty()) {
            std::cout << trimmed_line << "\n";
        }
    }
}

int main() {
    std::vector<BusRoute> routes = create_routes();
    char command;
    do {
        std::cin >> command;
        switch (command) {
            case 'a': query_a(routes); break;
            case 'b': query_b(routes); break;
            case 'c': query_c(routes); break;
            case 'd': query_d(); break;
            case 'e': break;
            default: std::cout << "Invalid command. Please enter a valid command (a, b, c, d, e): "; break;
        }
    } while (command != 'e');
}