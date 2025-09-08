// https://cppscripts.com/paho-mqtt-cpp-cmake

#include <iostream>
#include <string>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("ExampleSubscriber");

class MessageCallback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message arrived: '" << msg->get_payload()
                  << "' on topic: " << msg->get_topic() << std::endl;
    }
};

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    MessageCallback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        client.connect(connOpts)->wait();
        std::cout << "Connected to the MQTT broker!" << std::endl;
        
        const std::string topic("esp32/ds/temperature");
        client.subscribe(topic, 0);

        // Wait for messages
        std::this_thread::sleep_for(std::chrono::seconds(30));
        client.disconnect()->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    return 0;
}
