#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "WhtsProtocol.h"
#include "master_app.h"

using namespace WhtsProtocol;

// Command tracking for timeout and retry management
struct PendingCommand
{
    uint32_t slaveId;
    std::unique_ptr<Message> command;
    uint32_t timestamp;
    uint8_t retryCount;
    uint8_t maxRetries;

    PendingCommand(uint32_t id, std::unique_ptr<Message> cmd, uint8_t maxRetry = DEFAULT_MAX_RETRIES)
        : slaveId(id), command(std::move(cmd)), timestamp(0), retryCount(0), maxRetries(maxRetry)
    {
    }
};

// Ping session tracking
struct PingSession
{
    uint32_t targetId;
    uint8_t pingMode;
    uint16_t totalCount;
    uint16_t currentCount;
    uint16_t successCount;
    uint16_t interval;
    uint32_t lastPingTime;
    std::unique_ptr<Message> originalMessage; // Store original ping control message for response

    PingSession(uint32_t target, uint8_t mode, uint16_t total, uint16_t intervalMs)
        : targetId(target), pingMode(mode), totalCount(total), currentCount(0), successCount(0), interval(intervalMs),
          lastPingTime(0), originalMessage(nullptr)
    {
    }

    PingSession(uint32_t target, uint8_t mode, uint16_t total, uint16_t intervalMs, std::unique_ptr<Message> msg)
        : targetId(target), pingMode(mode), totalCount(total), currentCount(0), successCount(0), interval(intervalMs),
          lastPingTime(0), originalMessage(std::move(msg))
    {
    }
};

// Configuration tracking for backend command responses
struct PendingBackendResponse
{
    uint8_t messageType;                                 // Backend2Master message type
    std::unique_ptr<Message> originalMessage;            // Original backend message
    std::unordered_set<uint32_t> pendingSlaves;          // Slaves that haven't responded
    std::unordered_map<uint32_t, uint8_t> slaveStatuses; // Slave ID -> status (0=success, 1=error)
    uint32_t timestamp;                                  // When the configuration started
    uint32_t timeoutMs;                                  // Timeout in milliseconds

    PendingBackendResponse(uint8_t msgType, std::unique_ptr<Message> msg, const std::vector<uint32_t> &slaves,
                           uint32_t timeout = BACKEND_RESPONSE_TIMEOUT_MS)
        : messageType(msgType), originalMessage(std::move(msg)), timestamp(0), timeoutMs(timeout)
    {
        for (uint32_t slaveId : slaves)
        {
            pendingSlaves.insert(slaveId);
        }
    }

    // Check if all slaves have responded
    bool isComplete() const
    {
        return pendingSlaves.empty();
    }

    // Mark a slave as responded with status
    void markSlaveResponse(uint32_t slaveId, uint8_t status)
    {
        pendingSlaves.erase(slaveId);
        slaveStatuses[slaveId] = status;
    }

    // Check if timed out
    bool isTimedOut(uint32_t currentTime) const
    {
        return (currentTime - timestamp) > timeoutMs;
    }

    // Get overall status (success=all success, error=any error)
    uint8_t getOverallStatus() const
    {
        for (const auto &pair : slaveStatuses)
        {
            if (pair.second != RESPONSE_STATUS_SUCCESS)
            {
                return RESPONSE_STATUS_ERROR; // Error
            }
        }
        return RESPONSE_STATUS_SUCCESS; // Success
    }
};