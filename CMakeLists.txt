cmake_minimum_required(VERSION 3.26)
project(advent)

set(CMAKE_CXX_STANDARD 17)

file(GLOB sources day*/*.cpp)
foreach (source ${sources})
    get_filename_component(name ${source} NAME_WE)
    get_filename_component(parent ${source} DIRECTORY)
    get_filename_component(parent ${parent} NAME)
    add_executable(${parent}-${name} ${source})
endforeach ()

