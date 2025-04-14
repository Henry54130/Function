#include <regx52.h>
#include "D:\\University\\microprocessor\\teacher\\_gw52\\_uartm\\tm0x52_ini0.h"
#include "D:\\University\\microprocessor\\teacher\\_gw52\\_hwbio\\hw02_def_ktb0.h"

#define TASK_NO 2
#define TASK_FRQ 1000
unsigned int pbase_frq = TASK_NO * TASK_FRQ;
unsigned char vaTH0, vaTL0;

unsigned int led_cnt = 0;
unsigned int led_threshold = 500;  // ??????
unsigned char led_flag = 0;
unsigned char spk_flag = 0;

void main() {
    IE = 0x82;                                // ?? Timer0 ??
    tmr0_ini(pbase_frq, &vaTH0, &vaTL0);      // ?? Timer0 ? 2KHz (TASK_NO * TASK_FRQ)
    TR0 = 1;                                  // ?? Timer0

    while (1) {
        // ??????????
    }
}

void tmr0_isr(void) interrupt 1 {
    static unsigned char div = 0;
    TH0 = vaTH0;
    TL0 = vaTL0;
    div++;
    if (div >= TASK_NO) div = 0;

    switch (div) {
        case 0: // LED ????
            led_cnt++;

            // ?? DSW ????(? DSW ? 4 ?)
			
            led_threshold = DSW*20+100;  // ??? 100ms ? 1600ms

            if (led_cnt >= led_threshold) {
                led_cnt = 0;
                led_flag = !led_flag;
                LED = led_flag ? 0 : 1;  // ?????
            }
            break;

        case 1: // ?????(?? JPB1 ????)
            if (JPB1 == 1) {
                spk_flag = !spk_flag;
                SPK = spk_flag;
            } else {
                SPK = 0;
            }
            break;
    }
}
