cmake_minimum_required(VERSION 3.15)

project(rlFbo VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

set(RLFBO_PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/rlFbo.hpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${RLFBO_PUBLIC_HEADERS}
        ${PROJECT_NAME}/rlFbo.cpp
)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

find_package(raylib 5.0 REQUIRED)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include/rlFbo
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

install(FILES ${SKIT_PUBLIC_HEADERS} DESTINATION include/rlFbo)