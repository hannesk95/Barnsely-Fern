cmake_minimum_required(VERSION 3.10)
project(BarnselyFern)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

set(SRC_FILES Buffer.h Consumer.h GenuineConsumer.h GenuineProducer.h Producer.h Worker.h main.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# If CImg shall use built in png (for some reason ImageMagick does not work right now)
set(YOU_NEED_PNG 1)

if(${YOU_NEED_PNG} EQUAL 1)
    message(STATUS "Looking for libpng...")

    # Flags to enable native support for PNG image files, using the PNG library.
    # ( http://www.libpng.org/ )
    set(CIMG_PNG_CCFLAGS -Dcimg_use_png)

    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${PNG_LIBRARY})
    target_compile_definitions(${PROJECT_NAME} PRIVATE cimg_use_png=1)
endif()
