cmake_minimum_required(VERSION 3.16)

# Coleta de fontes
FILE(GLOB EMB_BDI_AGENT_SOURCES ../embedded-bdi/lib/agent/*.cpp)
FILE(GLOB EMB_BDI_BDI_SOURCES ../embedded-bdi/lib/bdi/*.cpp)
FILE(GLOB EMB_BDI_LIB_SOURCES ../embedded-bdi/lib/lib/*.cpp)
FILE(GLOB EMB_BDI_SYNTAX_SOURCES ../embedded-bdi/lib/syntax/*.cpp)
FILE(GLOB EMB_BDI_COMMUNICATION_SOURCES ../embedded-bdi/lib/communication/*.cpp)

# Configuração do componente
idf_component_register(SRCS src/agent_loop.cpp data/functions.cpp wifi_functions/wifi_station.c 
                       ${EMB_BDI_AGENT_SOURCES} 
                       ${EMB_BDI_BDI_SOURCES} 
                       ${EMB_BDI_LIB_SOURCES} 
                       ${EMB_BDI_SYNTAX_SOURCES} 
                       ${EMB_BDI_COMMUNICATION_SOURCES}
                       INCLUDE_DIRS "src" "../embedded-bdi/lib" "data")

