// #include "slave_app.h"
#include "MasterServer.h"
#include "cmsis_os2.h"
#include "udp_task.h"
#include "uwb_task.h"
#include "elog.h"

using namespace WhtsProtocol;

extern void UWB_Task_Init(void);
extern void UDP_Task_Init(void);

extern "C" int main_app(void) {
    UWB_Task_Init();    // 初始化UWB通信任务
    UDP_Task_Init();    // 初始化UDP通信任务

    MasterServer masterServer;
    masterServer.run();

    // uint8_t data[TEST_DATA_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (;;) {

        // UDP_SendData(data, TEST_DATA_SIZE, TEST_UDP_IP, TEST_UDP_PORT);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        elog_v("master_app", "Hello World");
        osDelay(MAIN_LOOP_DELAY_MS);
    }
    return 0;
}