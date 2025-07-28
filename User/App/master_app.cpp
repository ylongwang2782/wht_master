// #include "slave_app.h"
#include "master_app.hpp"

#include "cmsis_os2.h"
#include "udp_task.h"
#include "uwb_task.h"
#include "MasterServer.h"

using namespace WhtsProtocol;

extern void UWB_Task_Init(void);
extern void UDP_Task_Init(void);

extern "C" int main_app(void) {
    UWB_Task_Init();    // 初始化UWB通信任务
    UDP_Task_Init();    // 初始化UDP通信任务

    MasterServer masterServer;
    masterServer.run();

    for (;;) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        osDelay(500);
    }
    return 0;
}