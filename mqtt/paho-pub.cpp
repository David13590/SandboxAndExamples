// https://cppscripts.com/paho-mqtt-cpp-cmake

#include <iostream>
#include <string>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://10.56.16.100:1883");
const std::string CLIENT_ID("ExampleClient");
int msg_count = 10;
int current_msg_count = 0;

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        client.connect(connOpts)->wait();
        std::cout << "Connected to the MQTT broker!" << std::endl;

        while (current_msg_count <= msg_count){
            const std::string topic("esp32/ds/temperature");
            const std::string payload("Hello, MQTT!");
            client.publish(topic, payload.data(), payload.size(), 0, false);
            std::cout << "Message published!" << std::endl;
            current_msg_count++;
            if(current_msg_count == 10){
                const std::string payload("Last msg!");
                client.publish(topic, payload.data(), payload.size(), 0, false);
                break;
            }
        }
        client.disconnect()->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    return 0;
}