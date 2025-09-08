#ifndef JOYSTICK_HPP_
#define JOYSTICK_HPP_
    
class joystick{
    public:
        struct joystickValue{
            int x;
            int y;
            int button;
        };
        joystickValue& get_value();
        void setup(int xPin, int yPin, int buttonPin);        
    private:
        int xPin_private = 000;
        int yPin_private = 000;
        int buttonPin_private = 000;
        const int neutralMin = 1700;
        const int neutralMax = 2000;
        joystickValue myjoystickvalue;
};
#endif