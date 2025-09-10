#include <mqtt/async_client.h>
#include <string>
#include <iostream>
using namespace std;

const string SERVER_ADDRESS("tcp://localhost:1883");
const string CLIENT_ID("cpp_test_subscriber");
const string TOPIC("spBv1.0/officeb/DDATA/ventchamber2/temp1");

class callback : public virtual mqtt::callback {
    void message_arrived(mqtt::const_message_ptr msg) override {
        cout << "Message received: " << msg->get_payload_str() << endl;
    }
};

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try {
        // Connect to EMQX broker
        client.connect(connOpts)->wait();
        cout << "Connected to EMQX broker" << endl;

        // Subscribe to topic
        client.subscribe(TOPIC, 1)->wait();
        cout << "Subscribed to topic: " << TOPIC << endl;

        // Keep running to receive messages
        cout << "Press Enter to exit..." << endl;
        cin.get();

        // Disconnect
        client.disconnect()->wait();
        cout << "Disconnected" << endl;
    } catch (const mqtt::exception& exc) {
        cerr << "Error: " << exc.what() << endl;
        return 1;
    }

    return 0;
}