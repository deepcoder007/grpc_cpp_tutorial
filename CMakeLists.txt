cmake_minimum_required(VERSION 3.16)

project(grpc_cpp_tutorial DESCRIPTION "testing of GRPC C++ library" VERSION 1.0 LANGUAGES CXX)

include(GNUInstallDirs)
add_subdirectory(proto)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
message("List of identified files: ${SOURCE_FILES}")

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Protobuf_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC grpc++.a grpc.a libz.a ssl.a crypto.a gpr.a)

function(setup_app target src_file)
    add_executable(${target} ${src_file})
    target_link_libraries(${target} PRIVATE ${PROJECT_NAME}_proto)
    target_link_libraries(${target} PRIVATE ${PROJECT_NAME})
    target_include_directories(${target} PRIVATE proto)
endfunction()

setup_app(server "app/server.x.cpp")
setup_app(client "app/client.x.cpp")



