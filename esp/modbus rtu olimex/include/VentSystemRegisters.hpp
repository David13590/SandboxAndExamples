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

modbusRegisterList inputRegisterList[] = {
    {{"OutdoorTemp", 0}, 0},
    {{"runMode", 2}, 0},
    {{"extractAirTemp", 8}, 0},
    {{"roomTemp1", 9}, 0},
    {{"roomTemp2", 10}, 0},
    
};

modbusRegisterList holdingRegisterList[] = {
    {{"fanMode", 367}, 0},
};

// struct structInputRegisterList{ // Define stuct to store registers
    
//     const int getOutdoorTemp = 0; //0 InputReg - Get outdoor temperature 
//     const int runMode = 2;        //1 InputReg - Get current running mode
//     const int extractAirTemp = 8; //2 InputReg - Extract air temp (Exhaust air temp??)
//      int roomTemp1 = 9;      //3 InputReg - Get room temp1
//      int roomTemp2 = 10;     //4 InputReg - Get room temp2
// };
// structInputRegisterList inputRegisterList;


// struct structHoldingRegisterList
// {
//     const int fanMode = 367;      //0 HoldingReg - Set running mode on air unit
// };
// structHoldingRegisterList holdingRegisterList;


//Assign a number to each entry in the list of registries


#endif