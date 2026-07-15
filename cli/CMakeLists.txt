set(CLI_SRC src/main.cpp)

add_executable(SobelCli ${CLI_SRC})

target_link_libraries(SobelCli PUBLIC SobelCore)

install(TARGETS SobelCli DESTINATION bin)