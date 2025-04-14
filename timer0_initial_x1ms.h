// timer0_initial_x1ms.h
#ifndef __TIMER0_INITIAL_X1MS_H__
#define __TIMER0_INITIAL_X1MS_H__

#include <regx52.h>

// === User must implement this function in main.c ===
// Called every X ms in Timer0 ISR
void Timer0_User_ISR(void);

// === Internal variables for reload values ===
static unsigned char th0_reload = 0;
static unsigned char tl0_reload = 0;

// === Initialize Timer0 to interrupt every `ms` milliseconds ===
void Timer0_Initial_x1ms(unsigned int ms) {
    unsigned long counts;
    unsigned int preload;

    TMOD &= 0xF0;      // Clear Timer0 bits
    TMOD |= 0x01;      // Mode 1: 16-bit

    counts = (unsigned long)ms * 1000;  // Convert ms to us
    if (counts > 65535) counts = 65535; // 16-bit limit

    preload = 65536 - counts;
    th0_reload = (preload >> 8) & 0xFF;
    tl0_reload = preload & 0xFF;

    TH0 = th0_reload;
    TL0 = tl0_reload;

    ET0 = 1;  // Enable Timer0 interrupt
    EA = 1;   // Enable global interrupts
    TR0 = 1;  // Start Timer0
}

// === Timer0 ISR ===
void Timer0_ISR(void) interrupt 1 {
    TH0 = th0_reload;
    TL0 = tl0_reload;

    Timer0_User_ISR();  // Call user-defined ISR logic
}

#endif
