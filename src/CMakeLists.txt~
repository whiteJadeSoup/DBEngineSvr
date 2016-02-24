
cmake_minimum_required (VERSION 2.8)
# Project 
project (DBEngineSvr)


# policy
# 去除使用相对路径的提示
cmake_policy(SET CMP0015 OLD)

message (STATUS "compiler is ${CMAKE_CXX_COMPILER_ID}" )
message (STATUS "source dir: ${PROJECT_SOURCE_DIR} ")
message (STATUS "current dir: ${CMAKE_CURRENT_SOURCE_DIR}")

ADD_DEFINITIONS (-std=c++0x -g -Wall )

# 验证是否支持C++11
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
    endif ()
    elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

    else ()
        message(FATAL_ERROR "Your C++ compiler does not support C++11.")
    endif ()


# 设置boost库路径
set (Boost_root_path    ../boost)
set (Boost_head_path    ${Boost_root_path}/include)
set (Boost_lib_path	    ${Boost_root_path}/lib)

# 设置mysql
set (Mysql_root_path    ../mysql)
set (Mysql_head_path    ${Mysql_root_path}/include)
set (Mysql_lib_path	    ${Mysql_root_path}/lib)


include_directories(${Boost_head_path})
LINK_DIRECTORIES(${Boost_lib_path})

include_directories(${Mysql_head_path})
LINK_DIRECTORIES(${Mysql_lib_path})


# use boost lib
set (Boost_system_lib 		    libboost_system.a)
set (Boost_serialization_lib 	libboost_serialization.a)
set (Boost_signals_lib 		    libboost_signals.a)

# use mysql lib
set (mysql_lib 	libmysqlcppconn.so)


set (Used_Boost_libs ${Boost_system_lib} ${Boost_serialization_lib} ${Boost_signals_lib})
set (Used_Mysql_libs ${mysql_lib})


# set used protobuf
set (Pb_lib	libprotobuf.a)
set (Pb_used_libs ${Pb_lib})

# 当前目前下的所有源文件
file(GLOB_RECURSE HEAD_FILES *h *hpp)
aux_source_directory (. DIR_SRCS)
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS} ${HEAD_FILES})


#
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Used_Boost_libs} ${Used_Mysql_libs} ${Pb_used_libs})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpthread)


