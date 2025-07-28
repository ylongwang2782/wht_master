#pragma once

#include <memory>
#include <string>
#include <vector>

#include "WhtsProtocol.h"


using namespace WhtsProtocol;

// Forward declarations
class MasterServer;

// Message handler interface for Slave2Master messages
class ISlave2MasterMessageHandler {
   public:
    virtual ~ISlave2MasterMessageHandler() = default;
    virtual std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                                    const Message &message,
                                                    MasterServer *server) = 0;
    virtual void executeActions(uint32_t slaveId, const Message &message,
                                MasterServer *server) = 0;
};

// Announce Message Handler
class AnnounceHandler : public ISlave2MasterMessageHandler {
   public:
    static AnnounceHandler &getInstance() {
        static AnnounceHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    AnnounceHandler() = default;
    AnnounceHandler(const AnnounceHandler &) = delete;
    AnnounceHandler &operator=(const AnnounceHandler &) = delete;
};

// Short ID Confirm Message Handler
class ShortIdConfirmHandler : public ISlave2MasterMessageHandler {
   public:
    static ShortIdConfirmHandler &getInstance() {
        static ShortIdConfirmHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    ShortIdConfirmHandler() = default;
    ShortIdConfirmHandler(const ShortIdConfirmHandler &) = delete;
    ShortIdConfirmHandler &operator=(const ShortIdConfirmHandler &) = delete;
};

// SetTime Response Message Handler
class SetTimeResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static SetTimeResponseHandler &getInstance() {
        static SetTimeResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    SetTimeResponseHandler() = default;
    SetTimeResponseHandler(const SetTimeResponseHandler &) = delete;
    SetTimeResponseHandler &operator=(const SetTimeResponseHandler &) = delete;
};

// Conduction Config Response Handler
class ConductionConfigResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static ConductionConfigResponseHandler &getInstance() {
        static ConductionConfigResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    ConductionConfigResponseHandler() = default;
    ConductionConfigResponseHandler(const ConductionConfigResponseHandler &) =
        delete;
    ConductionConfigResponseHandler &operator=(
        const ConductionConfigResponseHandler &) = delete;
};

// Resistance Config Response Handler
class ResistanceConfigResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static ResistanceConfigResponseHandler &getInstance() {
        static ResistanceConfigResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    ResistanceConfigResponseHandler() = default;
    ResistanceConfigResponseHandler(const ResistanceConfigResponseHandler &) =
        delete;
    ResistanceConfigResponseHandler &operator=(
        const ResistanceConfigResponseHandler &) = delete;
};

// Clip Config Response Handler
class ClipConfigResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static ClipConfigResponseHandler &getInstance() {
        static ClipConfigResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    ClipConfigResponseHandler() = default;
    ClipConfigResponseHandler(const ClipConfigResponseHandler &) = delete;
    ClipConfigResponseHandler &operator=(const ClipConfigResponseHandler &) =
        delete;
};

// Reset Response Handler
class ResetResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static ResetResponseHandler &getInstance() {
        static ResetResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    ResetResponseHandler() = default;
    ResetResponseHandler(const ResetResponseHandler &) = delete;
    ResetResponseHandler &operator=(const ResetResponseHandler &) = delete;
};

// Ping Response Handler
class PingResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static PingResponseHandler &getInstance() {
        static PingResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    PingResponseHandler() = default;
    PingResponseHandler(const PingResponseHandler &) = delete;
    PingResponseHandler &operator=(const PingResponseHandler &) = delete;
};

// Slave Control Response Handler
class SlaveControlResponseHandler : public ISlave2MasterMessageHandler {
   public:
    static SlaveControlResponseHandler &getInstance() {
        static SlaveControlResponseHandler instance;
        return instance;
    }
    std::unique_ptr<Message> processMessage(uint32_t slaveId,
                                            const Message &message,
                                            MasterServer *server) override;
    void executeActions(uint32_t slaveId, const Message &message,
                        MasterServer *server) override;

   private:
    SlaveControlResponseHandler() = default;
    SlaveControlResponseHandler(const SlaveControlResponseHandler &) = delete;
    SlaveControlResponseHandler &operator=(
        const SlaveControlResponseHandler &) = delete;
};