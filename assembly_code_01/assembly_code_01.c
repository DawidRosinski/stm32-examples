#include <stdint.h>

int main(void)
{
    // board_setup_init();

    uint32_t *x = (uint32_t *)0x20001000;
    uint32_t *y = (uint32_t *)0x20001004;
    *x = 4;
    *y = 6;

    __asm volatile("LDR R1,=#0x20001000");
    __asm volatile("LDR R2,=#0x20001004");
    __asm volatile("LDR R0,[R1]");
    __asm volatile("LDR R1,[R2]");
    __asm volatile("ADD R0,R0,R1");
    __asm volatile("STR R0,[R2]");

    // example 2
    // move variable value to register
    uint32_t val = 50;
    __asm volatile("MOV R0,%0": :"r"(val));

    for(;;);
    
    }
