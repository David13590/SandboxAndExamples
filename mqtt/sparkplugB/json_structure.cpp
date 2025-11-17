#include <nlohmann/json_fwd.hpp>
#include <string>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


json sensor_nbirth_struct = json::parse(R"(
            {
            "timestamp": 0,
            "metrics": [{
                "name": "bdSeq",
                "timestamp": 0,
                "dataType": "Int64",
                "value": 0
            }, {
                "name": "Reboot",
                "timestamp": 0,
                "dataType": "bool",
                "value": false
            }, {
                "name": "Poll rate",
                "timestamp": 0,
                "dataType": "String",
                "value": "2"
            }, {
                "name": "Inputs/Temperature1",
                "timestamp": 0,
                "dataType": "Float",
                "value": 0
            }, {
                "name": "Inputs/Temperature2",
                "timestamp": 1486144502122,
                "dataType": "Float",
                "value": 0
            }],
            "seq": 0
            }
            )");

json sensor_ndeath_struct = json::parse(R"(
            {
            "timestamp": 0,
            "metrics": [{
                "name": "bdSeq",
                "timestamp": 0,
                "dataType": "Int64",
                "value": 0
            }, {
                "name": "Reboot",
                "timestamp": 0,
                "dataType": "Int64",
                "value": false
            }
            ],
            "seq": 0
            }
            )");


json sensor_DDATA_struct = json::parse(R"(
            {
            "timestamp": 0,
            "metrics": [{
                "name": "0",
                "alias": 1,
                "timestamp": 0,
                "dataType": "integer",
                "value": "0"
            }, {
                "name": "0", 
                "alias": 2,
                "timestamp": 0,
                "dataType": "integer",
                "value": "0"
            }],
            "seq": 0
            }
            )");