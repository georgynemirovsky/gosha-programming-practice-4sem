#include "json.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

using namespace nlohmann;

struct Person {
public:
    std::string name;
    int age;
    std::string mail;
    Person(std::string name = "", int age = 0, std::string mail = "") : name(name), age(age), mail(mail) {}
    ~Person(){}
    friend std::istream& operator>>(std::istream &in, Person &person);
    friend std::ostream& operator<<(std::ostream &out, Person &person);
};

std::istream& operator>>(std::istream& in, Person &person) {
    in >> person.name;
    in >> person.age;
    in >> person.mail;
    return in;
}

std::ostream& operator<<(std::ostream& out, Person &person) {
    out << person.name << " " << person.age << " " << person.mail;
    return out;
}

int main() {
    Person person;
    std::cin >> person;
    json jsonfile;
    jsonfile["name"] = person.name;
    jsonfile["age"] = person.age;
    jsonfile["mail"] = person.mail;
    std::filesystem::create_directory("persons");
    std::ofstream file("persons/person.json");
    file << jsonfile;
}
