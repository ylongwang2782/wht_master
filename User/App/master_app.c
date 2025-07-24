// #include "slave_app.h"
#include "cmsis_os2.h"
#include "elog.h"
#include "udp_task.h"
#include "uwb_task.h"

extern void UWB_Task_Init(void);
extern void UDP_Task_Init(void);

void Udp2uwb_Task_Init(void);

int main_app(void) {
    UWB_Task_Init();        // 初始化UWB通信任务
    UDP_Task_Init();        // 初始化UDP通信任务
    Udp2uwb_Task_Init();    // 初始化UDP到UWB的转换任务
    return 0;
}

void udp2uwb_task(void *argument) {
    static const char *TAG = "udp2uwb_task";
    elog_i(TAG, "udp2uwb_task start");

    // 从uwb接受数据并转发到udp
    uwb_rx_msg_t uwb_rx_msg;
    while (1) {
        if (UWB_ReceiveData(&uwb_rx_msg, 1000) == 0) {
            elog_i(TAG, "uwb_rx_msg.data_len: %d", uwb_rx_msg.data_len);
            UDP_SendData(uwb_rx_msg.data, uwb_rx_msg.data_len, "192.168.0.103", 9000);
        }
    }
}

static osThreadId_t udp2uwbHandle;
void Udp2uwb_Task_Init(void) {
    const osThreadAttr_t uwbTask_attributes = {
        .name = "uwbTask",
        .stack_size = 512 * 4,
        .priority = (osPriority_t)osPriorityNormal,
    };
    udp2uwbHandle = osThreadNew(udp2uwb_task, NULL, &uwbTask_attributes);
}
