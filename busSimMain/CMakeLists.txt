
add_executable(busSim src/busSimMain/main.cpp)

target_link_libraries(busSim PRIVATE bus_sim_config engine)

#target_link_libraries(busSim PRIVATE engine)