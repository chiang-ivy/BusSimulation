configure_file(config.json . COPYONLY)

add_library(
        bus_sim_config
        src/config/config.cpp
        src/config/config.h
        src/config/bus_system.cpp
        src/config/bus_system.h
)

target_include_directories(bus_sim_config PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

