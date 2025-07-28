target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/master_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/B2M_MessageHandlers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DeviceManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MasterServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/S2M_MessageHandlers.cpp
        
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
