#ifndef VENTSYSTEMREGISTERS_H_
// Registers we want to use.
// Documentation for VentSystem is 1 idexed.
// The VentSystem is 0 indexed ie, if you want access to registry 3 from the docs,
// you must write 2 in the code. The entries listed here have been shifted. 

// Registry R/W permissions
// Coils R/W
// Discrete Inputs R
// Input Reg R
// Holding Reg R/W

struct structInputRegisterList{ // Define stuct to store registers
    const int getOutdoorTemp = 0; //0 InputReg - Get outdoor temperature 
    const int runMode = 2;        //1 InputReg - Get current running mode
    const int extractAirTemp = 8; //2 InputReg - Extract air temp (Exhaust air temp??)
    const int roomTemp1 = 9;      //3 InputReg - Get room temp1
    const int roomTemp2 = 10;     //4 InputReg - Get room temp2
};
structInputRegisterList inputRegisterList;


struct structHoldingRegisterList
{
    const int fanMode = 367;      //0 HoldingReg - Set running mode on air unit
};
structHoldingRegisterList holdingRegisterList;


//Assign a number to each entry in the list of registries
int inputRegEntry0 = 0;
int inputRegEntry1 = 1;
int inputRegEntry2 = 2;
int inputRegEntry3 = 3;
int inputRegEntry4 = 4;

int hRegEntry0 = 0;


#endif