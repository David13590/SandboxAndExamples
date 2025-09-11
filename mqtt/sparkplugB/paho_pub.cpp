#include <mqtt/async_client.h>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <ctime>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
const string SERVER_ADDRESS("tcp://localhost:1883");
const string CLIENT_ID("test_publisher");

unsigned long sampleTime(){
    time_t timenow = time(nullptr);
    return timenow;
}

bool firstMsgSeq = true;
int resetMsgSeq = 0;
unsigned long currMsgSeq = 0;
unsigned long msgSeq(){
    if (firstMsgSeq){
        currMsgSeq = resetMsgSeq;
        firstMsgSeq = false;
    }
    currMsgSeq++;
    return currMsgSeq;
}

int main() {

    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        client.connect(connOpts)->wait();
        cout << "Connected to the MQTT broker!" << endl;
        
        // Follow topic structure of Sparkplug B version 1.0
        const string topic("spBv1.0/officeb/DDATA/ventchamber2/temp1");
        // Create JSON payload written in raw JSON
        json jsonpayload = json::parse(R"(
                                   {
                                    "timestamp": 1486144502122,
                                    "metrics": [{
                                        "name": "temperature",
                                        "alias": 1,
                                        "timestamp": 1479123452194,
                                        "dataType": "integer",
                                        "value": "25.5"
                                    }, {
                                        "name": "temperature", 
                                        "alias": 2,
                                        "timestamp": 1479123452196,
                                        "dataType": "integer",
                                        "value": "22"
                                    }],
                                    "seq": 2
                                    }
                                    )");
        // Convert JSON payload to string
        string payload = jsonpayload.dump(4);
        //client.publish(topic, payload.data(), payload.size(), 0, false);
        //cout << "Message published!" << endl;

        // Create empty json stucts to send
        json temp_nbirth;
        json temp_payload; // empty JSON structure 
        json temp_ndeath;
        


        // Parse and send nbirth once
        temp_nbirth["timestamp"] = sampleTime();

        //Node Controls
        temp_nbirth["metrics"][0]["name"] = "bdSeq";
        temp_nbirth["metrics"][0]["timestamp"] = sampleTime();
        temp_nbirth["metrics"][0]["dataType"] = "Int64";
        temp_nbirth["metrics"][0]["value"] = 0;

        temp_nbirth["metrics"][1]["name"] = "Reboot";
        temp_nbirth["metrics"][1]["timestamp"] = sampleTime();
        temp_nbirth["metrics"][1]["dataType"] = "Boolean";
        temp_nbirth["metrics"][1]["value"] = "false";

        temp_nbirth["metrics"][1]["name"] = "Poll rate";
        temp_nbirth["metrics"][1]["timestamp"] = sampleTime();
        temp_nbirth["metrics"][1]["dataType"] = "Int64";
        temp_nbirth["metrics"][1]["value"] = 2;


        //Proterties
        temp_nbirth["metrics"][8]["name"] = "";
        temp_nbirth["metrics"][8]["timestamp"] = sampleTime();
        temp_nbirth["metrics"][8]["dataType"] = "Int64";
        temp_nbirth["metrics"][8]["value"] = 0;


        json temp_nbirth = json::parse(R"(
            {
            "timestamp": 1486144502122,
            "metrics": [{
                "name": "bdSeq",
                "timestamp": 1486144502122,
                "dataType": "Int64",
                "value": 0
            }, {
                "name": "Node Control/",
                "timestamp": 1486144502122,
                "dataType": "Int64",
                "value": 3000
            }, {
                "name": "Properties/Hardware Make",
                "timestamp": 1486144502122,
                "dataType": "String",
                "value": "Opto22 Groov EPIC"
            }, {
                "name": "Inputs/Temperature",
                "timestamp": 1486144502122,
                "dataType": "Float",
                "value": 25.6
            }, {
                "name": "Inputs/Humidity",
                "timestamp": 1486144502122,
                "dataType": "Float",
                "value": 67.8
            }, {
                "name": "Outputs/Pump",
                "timestamp": 1486144502122,
                "dataType": "Boolean",
                "value": true
            }],
            "seq": 0
            }
            
            
            )");
        

        time_t sendTime = time(nullptr);
        while (client.is_connected()){
            temp_payload["timestamp"] = sendTime; // create function getSendTime

            //Sensor1
            temp_payload["metrics"]["Sensor1"]["timestamp"] = sampleTime(); // function to do
            temp_payload["metrics"]["Sensor1"]["name"] = "temperature1";
            temp_payload["metrics"]["Sensor1"]["value"] = 21; // function do do

            //Sensor2
            temp_payload["metrics"]["Sensor2"]["timestamp"] = sampleTime();
            temp_payload["metrics"]["Sensor2"]["name"] = "temperature2";
            temp_payload["metrics"]["Sensor2"]["value"] = 22; // function do do
            
            
            temp_payload["seq"] = msgSeq();

            string publish_payload = temp_payload.dump(4); // Convert payload to string and set json tabs
            client.publish(topic, publish_payload.data(), publish_payload.size(), 0, false);
            //client.disconnect()->wait();
            this_thread::sleep_for(chrono::seconds(2));
        }

        //send ndeath once on exit

        
    } catch (const mqtt::exception& exc) {
        cerr << "Error: " << exc.what() << endl;
    }

    return 0;
}
