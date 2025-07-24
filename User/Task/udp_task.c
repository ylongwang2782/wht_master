#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/inet.h"
#include "cmsis_os.h"
#include "main.h"
#include <string.h>

#define UDP_SERVER_PORT     8000
#define UDP_BUFFER_SIZE     512

void udp_echo_server(void *argument)
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[UDP_BUFFER_SIZE];
    socklen_t client_addr_len = sizeof(client_addr);
    int recv_len;

    // 创建 socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        printf("Socket creation failed!\r\n");
        osThreadExit();
    }

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 绑定 socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Socket bind failed!\r\n");
        closesocket(sockfd);
        osThreadExit();
    }

    printf("UDP Echo Server started on port %d\r\n", UDP_SERVER_PORT);

    while (1) {
        // 接收数据
        recv_len = recvfrom(sockfd, buffer, UDP_BUFFER_SIZE, 0,
                            (struct sockaddr *)&client_addr, &client_addr_len);
        if (recv_len > 0) {
            buffer[recv_len] = '\0'; // Null-terminate for printing
            printf("Received: %s from %s:%d\r\n", buffer,
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            // 原样返回
            sendto(sockfd, buffer, recv_len, 0,
                   (struct sockaddr *)&client_addr, client_addr_len);
        }

        osDelay(1); // 防止任务占满 CPU
    }
}

static osThreadId_t udpTaskHandle;

void UDP_Task_Init(void) {
    const osThreadAttr_t udpTask_attributes = {
        .name = "udpTask",
        .stack_size = 512 * 4,
        .priority = (osPriority_t)osPriorityNormal,
    };
    udpTaskHandle = osThreadNew(udp_echo_server, NULL, &udpTask_attributes);
}