add_library(
        engine
        src/engine/node.h
        src/object/Enums.h
        src/object/BusStop.cpp src/object/BusStop.h
        src/object/System.cpp src/object/System.h
        src/object/Bus.cpp src/object/Bus.h
        src/event/BaseEvent.cpp src/event/BaseEvent.h
        src/event/BusStartServiceEvent.cpp src/event/BusStartServiceEvent.h
        src/event/BusEndServiceEvent.cpp src/event/BusEndServiceEvent.h
        src/event/BusArriveStopEvent.cpp src/event/BusArriveStopEvent.h
        src/event/BusLeaveStopEvent.cpp src/event/BusLeaveStopEvent.h
        src/event/EventQueue.cpp src/event/EventQueue.h src/object/Passenger.cpp src/object/Passenger.h src/event/CreatePassengerEvent.cpp src/event/CreatePassengerEvent.h src/event/PassengerArriveDestinationEvent.cpp src/event/PassengerArriveDestinationEvent.h)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(engine PRIVATE bus_sim_config)

set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX) #This is a must when there is only .h file for template. Ivy, do you know why?