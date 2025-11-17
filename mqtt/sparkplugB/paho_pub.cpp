#include <mqtt/async_client.h>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <ctime>
#include <nlohmann/json.hpp>
#include "json_structure.cpp"

using namespace std;
using json = nlohmann::json;

int loop_count = 0;
int birth_initial_seq = 0;

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
            //        namespace/group_id/message_type/edge_node_id/[device_id]
        const string topic("spBv1.0/officeb/DDATA/ventchamber2/temp1");
        cout << "Message published!" << endl;

        // Initial struct values - sensor1
        json sensor1_nbirth = sensor_nbirth_struct;
        json sensor1_payload = sensor_DDATA_struct;
        json sensor1_ndeath = sensor_ndeath_struct;    
        
        // Set nbirth values and publish once on start
        sensor1_nbirth.at("timestamp") = sampleTime();
        //bdSeq
        sensor1_nbirth.at("metrics").at(0).at("timestamp") = sampleTime();
        sensor1_nbirth.at("metrics").at(0).at("value") = 
        //Reboot
        sensor1_nbirth.at("metrics").at(1).at("timestamp") = sampleTime();
        sensor1_nbirth.at("metrics").at(1).at("value") = 
        //Pool rate
        sensor1_nbirth.at("metrics").at(2).at("timestamp") = sampleTime();
        sensor1_nbirth.at("metrics").at(2).at("value") = 
        //Inputs/Temperature1
        sensor1_nbirth.at("metrics").at(3).at("timestamp") = sampleTime();
        sensor1_nbirth.at("metrics").at(3).at("value") = 
        //Inputs/Temperature2
        sensor1_nbirth.at("metrics").at(4).at("timestamp") = sampleTime();
        sensor1_nbirth.at("metrics").at(4).at("value") = 

        sensor1_nbirth.at("seq") = birth_initial_seq;

        string sensor1_nbirth_payload = sensor1_nbirth.dump(4);
        client.publish(topic, sensor1_nbirth_payload.data(), sensor1_nbirth_payload.size(), 0, false);
        
        auto nodeCTRL = sensor1_nbirth.at("metrics").at(1).at("value");
        string nodeCTRL_payload = nodeCTRL.dump(4);
        client.publish(topic, nodeCTRL_payload.data(), nodeCTRL_payload.size(), 0, false);

        time_t sendTime = time(nullptr);
        while (client.is_connected() && loop_count){
            sensor1_payload["timestamp"] = sendTime; // create function getSendTime

            //Sensor1
            sensor1_payload["metrics"]["timestamp"] = sampleTime(); // function to do
            sensor1_payload["metrics"]["name"] = "temperature1";
            sensor1_payload["metrics"]["value"] = 21; // function do do

            //Sensor2
            sensor1_payload.at("metrics").at(1).at("timestamp") = sampleTime();
            sensor1_payload.at("metrics").at(1).at("name") = "temperature2";
            sensor1_payload.at("metrics").at(1).at("value") = 22; // function do do
            
            sensor1_payload["seq"] = msgSeq();

            
            string sensor1_publish_payload = sensor1_payload.dump(4); // Convert payload to string and set json tabs
            client.publish(topic, sensor1_publish_payload.data(), sensor1_publish_payload.size(), 0, false);
            //client.disconnect()->wait();
            this_thread::sleep_for(chrono::seconds(2));

        }

        //send ndeath once on exit

        
    } catch (const mqtt::exception& exc) {
        cerr << "Error: " << exc.what() << endl;
    }

    return 0;
}
