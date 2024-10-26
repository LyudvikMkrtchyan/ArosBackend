cmake_minimum_required(VERSION 3.10)

# Укажите имя вашего проекта
project(MyProject)

# Укажите путь к vcpkg
set(CMAKE_TOOLCHAIN_FILE "/root/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Укажите список исходных файлов
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

# Добавьте исполняемый файл
add_executable(MyExecutable ${SOURCES})

# Найдите пакет nlohmann-json и подключите его
find_package(nlohmann_json CONFIG REQUIRED)

# Свяжите библиотеку nlohmann-json с вашим исполняемым файлом
target_link_libraries(MyExecutable PRIVATE nlohmann_json::nlohmann_json)

# Свяжите другие библиотеки
target_link_libraries(MyExecutable PRIVATE mysqlcppconn)

