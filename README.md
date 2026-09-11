A small virtual machine written in C simulating the LC-3 educational computer architecture I took on to learn how code interacts with the hardware.

Project and guide: https://www.jmeiners.com/lc3-vm

- Simulated essential hardware architecture: created 65536 16bit memory locations, 10 16bit CPU registers: 8
working, 2 reserved. Added RISC CPU instruction set, condition flags and trap codes.
- used bitwise SHIFT and bitwise AND to extract required information out of the 16bit instructions
- Implemented the instruction set and trap_routine cases in main in accordance with the LC-3 documentation
This project familiarized me with bitwise operations and their practical use cases greatly.
