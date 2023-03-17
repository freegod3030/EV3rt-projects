/**
 * This sample program shows how to create and control periodic tasks in EV3RT
 */

#include "app.h"
#include <stdlib.h>

static int32_t fontw, fonth;

// Print start time of a task
static void draw_start_time(int index) {
    SYSTIM tim;
    get_tim(&tim); // get system time in ms

    int x = 0, y = fonth * (1 + index);
    ev3_lcd_fill_rect(x, y, EV3_LCD_WIDTH, fonth, EV3_LCD_WHITE);
    char buf[100];
    sprintf(buf, " PRD_TSK_%d | %lu", index, tim);
    ev3_lcd_draw_string(buf, x, y);
}

// a periodic task 
void periodic_task_1(intptr_t unused) {
    draw_start_time(1);
}

// a periodic task 
void periodic_task_2(intptr_t unused) {
    draw_start_time(2);
}

void main_task(intptr_t unused) {
    static FILE *uart = NULL;
    int count=0;
    char str[100],lcdstr[100];
    uart = ev3_serial_open_file(EV3_SERIAL_UART);
    while(1){
        if(fgets(str, 11, uart) != NULL){
            count++;
            sprintf(lcdstr, "str=%s count=%d", str,count);
            ev3_lcd_draw_string(lcdstr,0,70);
        }
    }
}
