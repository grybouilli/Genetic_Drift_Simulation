cmake_minimum_required(VERSION 3.16)
project(genetic_drift)

find_package(SFML 2.5 
COMPONENTS 
system window graphics network audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("." "./Headers")
configure_file("Debug/medias/Background.png" "medias/Background.png" COPYONLY)
configure_file("Debug/medias/ElephantModel.jpg" "medias/ElephantModel.jpg" COPYONLY)
configure_file("Debug/medias/FemaleTusked.png" "medias/FemaleTusked.png" COPYONLY)
configure_file("Debug/medias/FemaleUntusked.png" "medias/FemaleUntusked.png" COPYONLY)
configure_file("Debug/medias/MaleTusked.png" "medias/MaleTusked.png" COPYONLY)
configure_file("Debug/medias/MaleUntusked.png" "medias/MaleUntusked.png" COPYONLY)

file(GLOB SOURCES "*.cpp")
add_executable(genetic_drift ${SOURCES})

target_link_libraries(genetic_drift sfml-graphics)
#target_link_libraries(test sfml-window)