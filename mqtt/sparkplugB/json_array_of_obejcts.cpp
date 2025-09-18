#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

std::string studentjson= R"(
{
    "test-data":
    [
        {
            "name": "tom",
            "age": 11
        },
        {
            "name": "jane",
            "age": 12
        }
    ]
}
)";

int main(){
    json myjson = json::parse(studentjson);
    
    auto &students = myjson["test-data"];
    
    for(auto &student : students) {
        cout << student["name"].get<string>() << endl;
    }

    return 0;
}