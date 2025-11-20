#ifndef VENTSYSTEMREGISTERS_H_
#include <string.h>
// Registers we want to use.
// Documentation for VentSystem is 1 idexed.
// The VentSystem is 0 indexed ie, if you want access to registry 3 from the docs,
// you must write 2 in the code. The entries listed here have been shifted. 

// Registry R/W permissions
// Coils R/W
// Discrete Inputs R
// Input Reg R
// Holding Reg R/W

struct modbusRegister{
    String name;
    int modbusAddress;
};

struct modbusRegisterList{
     modbusRegister reg;
     int lastReadTime;    
};

modbusRegisterList inputRegisterList[] = { // Define stuct to store registers
    {{"OutdoorTemp", 0}, 0},    //0 InputReg - Get outdoor temperature
    {{"runMode", 2}, 0},        //1 InputReg - Get current running mode
    {{"extractAirTemp", 8}, 0}, //2 InputReg - Extract air temp (Exhaust air temp??)
    {{"roomTemp1", 9}, 0},      //3 InputReg - Get room temp1
    {{"roomTemp2", 10}, 0},     //4 InputReg - Get room temp2
    
};

modbusRegisterList holdingRegisterList[] = {
    {{"fanMode", 367}, 0},
};

#endif