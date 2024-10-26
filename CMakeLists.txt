cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(SOURCES
    ./implement/evants/workerEvants.cpp
    ./implement/evants/carpetsManipulation.cpp
    ./implement/evants/ordersEvants.cpp
    ./implement/evants/optionsEvants.cpp
    ./implement/evants/complexOperationEvants.cpp
    ./implement/dataBase.cpp
    ./implement/orders.cpp
    ./implement/evantSwitch.cpp
    ./implement/helperFunctions.cpp
    ./implement/main.cpp
    ./implement/network.cpp
    ./implement/carpets.cpp
    ./implement/finances.cpp
    ./implement/workers.cpp
    ./implement/options.cpp
    ./implement/time.cpp
)

add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable mysqlcppconn)
