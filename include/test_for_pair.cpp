#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <any>
namespace ns {
 struct Student {
    std::string Name;
    std::any Group;
    double Avg;
    std::any Debt;
};
void to_json(json& j, const Student& s) {
        j = json{{"name", s.Name}, {"group", s.Group}, {"avg", s.Avg},{"debt", s.Debt}};
    }
    void from_json(const json& j, Student& s) {
    j.at("name").get_to(s.Name);
    j.at("group").get_to(s.Group);
    j.at("avg").get_to(s.Avg);
    j.at("debt").get_to(s.Debt);
}
}
using json = nlohmann::json;
ns::Student s {"Sidorov Ivan", 31, 4, "C++"};
json j = s;
std::cout << j << std::endl;
auto s2 = j.get<ns::Student>();
assert(p == s2);
