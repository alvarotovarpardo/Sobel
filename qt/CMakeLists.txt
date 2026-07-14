find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_SOURCES 
    src/main.cpp 
    src/mainwindow.cpp
)

add_executable(SobelQt ${QT_SOURCES})

target_link_libraries(SobelQt PRIVATE SobelCore Qt6::Widgets)