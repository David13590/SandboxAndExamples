// Registers we want to use.
// Documentation for VentSystem is 1 idexed.
// The VentSystem is 0 indexed ie, if you want access to registry 3 from the docs,
// you must write 2 in the code. The entries listed here have been shifted. 

// Registry R/W permissions
// Coils R/W
// Discrete Inputs R
// Input Reg R
// Holding Reg R/W

// These registry entries have been shifted once.
#define getOutdoorTemp 0 // InputReg - Get outdoor temperature 
#define runMode 2        // InputReg - Get current running mode
#define extractAirTemp 8 // InputReg - Extract air temp (Exhaust air temp??)
#define roomTemp1 9      // InputReg - Get room temp1
#define roomTemp2 10     // InputReg - Get room temp2
#define fanMode 367      // HoldingReg - Set running mode on air unit