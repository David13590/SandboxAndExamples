#ifndef CONTROLLERSENDER_HPP_
#define CONTROLLERSENDER_HPP_
    
class controllerSender{
    private:
        //JoystickLeft
        #define JOY_LEFT_VRX_PIN 39
        #define JOY_LEFT_VRY_PIN 36
        #define JOY_LEFT_SW_PIN 17

        //JoystickRight
        #define JOY_RIGHT_VRX_PIN 33
        #define JOY_RIGHT_VRY_PIN 32
        #define JOY_RIGHT_SW_PIN 37

        #define pcbButtonLeft 2
        #define pcbButtonRight 38

    public:
        const int buttonDebounceTime = 100;
        const int mapFromLow = 0;
        const int mapFromHigh = 4095;
        const int mapToLow = 0;
        const int mapToHigh = 1000;

        typedef struct channel_data {
            int channel1;
            int channel2;
            bool channel3;
            int channel4;
            int channel5;
            bool channel6;
            bool channel7;
            bool channel8;
        } channel_data;             
};
#endif