cmake_minimum_required(VERSION 3.22)
project(asiotest)

# set(SDK_FORCE_PLATFORM "Android")
# set(SDK_FORCE_PLATFORM "Windows")
# set(SDK_FORCE_PLATFORM "iOS")

if ((NOT (DEFINED SDK_FORCE_PLATFORM) AND (DEFINED ANDROID)) OR (${SDK_FORCE_PLATFORM} MATCHES "Android"))
    set(SDK_USE_ANDROID 1)
endif ()

if ((NOT (DEFINED SDK_FORCE_PLATFORM) AND (DEFINED WIN32)) OR (${SDK_FORCE_PLATFORM} MATCHES "Windows"))
    set(SDK_USE_WINDOWS 1)
endif ()

if ((NOT (DEFINED SDK_FORCE_PLATFORM) AND (DEFINED APPLE)) OR (${SDK_FORCE_PLATFORM} MATCHES "iOS"))
    set(SDK_USE_IOS 1)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3 -Wall -Wextra")

file(GLOB_RECURSE ALL_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE ALL_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.h)

add_executable(asiotest ${ALL_SRC})

add_definitions(
        -D_LIBCPP_DEBUG2=2
        -D_LIBCPP_DEBUG_LEVEL=2
        -DASIO_STANDALONE
        -DASIO_HAS_STD_ADDRESSOF
        -DASIO_HAS_STD_ARRAY
        -DASIO_HAS_CSTDINT
        -DASIO_HAS_STD_SHARED_PTR
        -DASIO_HAS_STD_TYPE_TRAITS
        -DASIO_HAS_STD_FUNCTION
        -DASIO_HAS_STD_CHRONO
        -DASIO_HAS_STD_THREAD
        -DASIO_HAS_VARIADIC_TEMPLATES
        -DBOOST_ALL_NO_LIB
)

if (SDK_USE_WINDOWS)
   target_link_libraries(asiotest PRIVATE wsock32 ws2_32)
   # add_definitions(
   #         -D_WIN32_WINNT=0x0501
   #         -D_WINSOCK_DEPRECATED_NO_WARNINGS
   #         -DBLE_USE_NETBLE
   # )
endif ()

target_include_directories(asiotest
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/lib/asio/asio/include
        )
