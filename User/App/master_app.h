#pragma once

// ============================
// MASTER APPLICATION CONFIGURATION
// ============================

// ========== TIMING CONFIGURATIONS ==========
#define DEFAULT_INTERVAL_MS 10 // 默认采集间隔 (ms)

// TDMA timing
#define TDMA_STARTUP_DELAY_MS 100                        // TDMA启动延迟时间 (ms)
#define TDMA_EXTRA_DELAY_MS 100                          // TDMA额外延迟时间 (ms)
#define TDMA_MIN_CYCLE_MS TDMA_EXTRA_DELAY_MS            // TDMA最小周期时间 (ms)
#define SYNC_START_DELAY_US (TDMA_EXTRA_DELAY_MS * 1000) // 同步启动延迟时间 (us) - 500ms

// ========== RETRY AND TIMEOUT CONFIGURATIONS ==========
#define DEFAULT_MAX_RETRIES 3            // 默认最大重试次数
#define RESET_MAX_RETRIES 1              // 重置命令最大重试次数
#define BASE_RETRY_TIMEOUT_MS 100        // 基础重试超时时间 (ms)
#define MAX_RETRY_TIMEOUT_MS 1000        // 最大重试超时时间 (ms)
#define BACKEND_RESPONSE_TIMEOUT_MS 5000 // 后端响应超时时间 (ms)
#define CONTROL_RESPONSE_TIMEOUT_MS 2000 // 控制响应超时时间 (ms)

// ========== DEVICE MANAGEMENT CONFIGURATIONS ==========
#define DEVICE_STATUS_CHECK_INTERVAL_MS 30000 // 设备状态检查间隔 (ms)
#define DEVICE_CLEANUP_INTERVAL_MS 60000      // 设备清理间隔 (ms)
#define DEVICE_TIMEOUT_MS 90000               // 设备超时时间 (ms)
#define SHORT_ID_START 1                      // 短ID起始值
#define SHORT_ID_MAX 254                      // 短ID最大值
#define ANNOUNCE_COUNT_LIMIT 3                // 宣告次数限制

// ========== UWB HEALTH MONITORING ==========
#define MAX_CONSECUTIVE_UWB_FAILURES 10     // UWB最大连续失败次数
#define UWB_FAILURE_RESET_INTERVAL_MS 30000 // UWB失败重置间隔 (ms)
#define UWB_HEALTH_CHECK_INTERVAL_MS 60000  // UWB健康检查间隔 (ms)

// ========== TASK AND PROCESSING CONFIGURATIONS ==========
#define MAX_BACKEND_PROCESS_TIME_MS 5000  // 后端处理最大时间 (ms)
#define MAX_BACKEND_PROCESS_ITERATIONS 10 // 后端处理最大迭代次数
#define TASK_DELAY_MS 1                   // 任务延迟时间 (ms)
#define MAIN_LOOP_DELAY_MS 500            // 主循环延迟时间 (ms)

// ========== BUFFER AND QUEUE SIZES ==========
#define UDP_DATA_TRANSFER_STACK_SIZE 1024     // UDP数据传输栈大小
#define MAX_BUF_SIZE 100                      // 最大缓冲区大小
#define DATA_TRANSFER_CONTEXT_QUEUE_SIZE 1024 // 数据传输上下文队列大小
#define DATA_SEND_TX_QUEUE_TIMEOUT_MS 100     // 数据发送队列超时 (ms)

// ========== NETWORK CONFIGURATIONS ==========
#define DEFAULT_BACKEND_IP "192.168.0.3" // 默认后端IP地址
#define DEFAULT_BACKEND_PORT 8080        // 默认后端端口

// ========== PROTOCOL CONFIGURATIONS ==========
#define BROADCAST_SLAVE_ID 0xFFFFFFFF // 广播从机ID

// ========== OPERATION MODE DEFINITIONS ==========
#define MODE_CONDUCTION 0 // 导通检测模式
#define MODE_RESISTANCE 1 // 阻值检测模式
#define MODE_CLIP 2       // 卡钉检测模式

// ========== SYSTEM STATUS DEFINITIONS ==========
#define SYSTEM_STATUS_STOP 0  // 系统停止状态
#define SYSTEM_STATUS_RUN 1   // 系统运行状态
#define SYSTEM_STATUS_RESET 2 // 系统重置状态

// ========== RESPONSE STATUS DEFINITIONS ==========
#define RESPONSE_STATUS_SUCCESS 0 // 响应成功状态
#define RESPONSE_STATUS_ERROR 1   // 响应错误状态

// ========== CONTROL COMMAND DEFINITIONS ==========
#define CONTROL_ENABLE 1  // 控制启用
#define CONTROL_DISABLE 0 // 控制禁用
#define RESET_UNLOCK 0    // 重置解锁
#define LED_OFF 0         // LED关闭