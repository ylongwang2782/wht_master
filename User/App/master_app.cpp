// #include "slave_app.h"
#include "master_app.hpp"

#include "TaskCPP.h"
#include "WhtsProtocol.h"
#include "arch.h"
#include "cmsis_os2.h"
#include "elog.h"
#include "hptimer.hpp"
#include "udp_task.h"
#include "uwb_task.h"

using namespace WhtsProtocol;

static const char *TAG = "master_app";

extern void UWB_Task_Init(void);
extern void UDP_Task_Init(void);

// void Udp2uwb_Task_Init(void);

BackendDataTransferTask backendDataTransferTask;

extern "C" int main_app(void) {


    // for (auto &fragment : commandData) {
    //     UDP_SendData(fragment.data(), fragment.size(), "192.168.0.103",
    //     9000);
    // }

    UWB_Task_Init();    // 初始化UWB通信任务
    UDP_Task_Init();    // 初始化UDP通信任务
    // Udp2uwb_Task_Init();    // 初始化UDP到UWB的转换任务
    backendDataTransferTask.give();

    ProtocolProcessor processor;
    processor.setMTU(127);

    auto syncCmd = std::make_unique<Master2Slave::SyncMessage>();
    // 将当前时间转换为微秒时间戳
    uint64_t timestampUs = hal_hptimer_get_us();
    syncCmd->timestamp = timestampUs;
    auto commandData = processor.packMaster2SlaveMessage(0xFFFFFFFF, *syncCmd);
    // print commandData Info
    elog_i(TAG, "commandData size: %d", commandData.size());
    elog_i(TAG, "commandData[0] size: %d", commandData[0].size());
    // elog_i(TAG, "commandData[0] data: %s", commandData[0].data());
    UDP_SendData(commandData[0].data(), commandData[0].size(),
                 "192.168.0.103", 9000);


    for (;;) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        osDelay(500);
    }
    return 0;
}

// BackendDataTransferTask 实现
BackendDataTransferTask::BackendDataTransferTask()
    : TaskClassS("BackendDataTransfer", TaskPrio_High) {}

// BackendDataTransferTask 任务实现
void BackendDataTransferTask::task() {
    elog_i(TAG, "BackendDataTransferTask task start");

    // 从uwb接受数据并转发到udp
    uwb_rx_msg_t uwb_rx_msg;
    while (1) {
        if (UWB_ReceiveData(&uwb_rx_msg, 1000) == 0) {
            elog_i(TAG, "uwb_rx_msg.data_len: %d", uwb_rx_msg.data_len);
            UDP_SendData(uwb_rx_msg.data, uwb_rx_msg.data_len, "192.168.0.103",
                         9000);
        }
        osDelay(100);
    }
}