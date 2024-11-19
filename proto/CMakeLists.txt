
find_package(Protobuf REQUIRED)
find_program(GRPC_CPP_PLUGIN_EXECUTABLE NAMES "grpc_cpp_plugin")
set(Protobuf_USE_STATIC_LIBS ON)

file(GLOB PROTOBUF_FILELIST CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

foreach(proto_file ${PROTOBUF_FILELIST})
    get_filename_component(proto_name ${proto_file} NAME_WE)
    get_filename_component(proto_path ${proto_file} DIRECTORY)
    set_source_files_properties(
        "${proto_path}/${proto_name}.pb.cc"
        "${proto_path}/${proto_name}.pb.h"
        "${proto_path}/${proto_name}.grpc.pb.cc"
        "${proto_path}/${proto_name}.grpc.pb.h"
        PROPERTIES GENERATED TRUE
    )

    list(APPEND PROTO_SRC "${proto_path}/${proto_name}.pb.cc" "${proto_path}/${proto_name}.grpc.pb.cc")
    list(APPEND PROTO_HEADER "${proto_path}/${proto_name}.pb.h" "${proto_path}/${proto_name}.grpc.pb.h")

    add_custom_command(
        OUTPUT "${proto_path}/${proto_name}.pb.h" "${proto_path}/${proto_name}.pb.cc"
        "${proto_path}/${proto_name}.grpc.pb.cc" "${proto_path}/${proto_name}.grpc.pb.h"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --cpp_out ${proto_path} --grpc_out ${proto_path}
        --proto_path ${proto_path} --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE} ${proto_file}
        DEPENDS ${proto_file}
        COMMENT "Running C++ protocol buffer compiler on ${proto_file}"
        VERBATIM
    )
endforeach()    

add_library(${PROJECT_NAME}_proto STATIC ${PROTO_HEADER} ${PROTO_SRC})

