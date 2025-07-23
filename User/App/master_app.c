// #include "slave_app.h"
#include <stdio.h>

extern void UWB_Task_Init(void);

int main_app(void) {
    printf("master_app\r\n");
    UWB_Task_Init();
    return 0;
}