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


void sampleTime(){
    time_t timenow = time(nullptr);
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
        // const string payload("Hello, MQTT!");
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
                                   }],
                                      "seq": 2
                                   }
                                   )");
        // Convert JSON payload to string
        string payload = jsonpayload.dump(4);
        //client.publish(topic, payload.data(), payload.size(), 0, false);
        //cout << "Message published!" << endl;

        // You can also construct the JSON object sequentially
        json altpayload; // empty JSON structure 

        time_t sendTime = time(nullptr);
        time_t payloadTime = time(nullptr);

        altpayload["timestamp"] = sendTime;
        altpayload["metrics"]["timestamp"] = payloadTime; // function to do
        altpayload["metrics"]["name"] = "temperature";
        altpayload["value"] = 25; // function do do

        string publish_payload = altpayload.dump(4);
        client.publish(topic, publish_payload.data(), publish_payload.size(), 0, false);
        client.disconnect()->wait();


    } catch (const mqtt::exception& exc) {
        cerr << "Error: " << exc.what() << endl;
    }

    return 0;
}
