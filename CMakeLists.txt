cmake_minimum_required(VERSION 3.10)
project(Final_Project)

set(CMAKE_CXX_STANDARD 11)

set(EASY_BMP EasyBMP.h EasyBMP_BMP.h EasyBMP.cpp EasyBMP_DataStructures.h EasyBMP_VariousBMPutilities.h)
set(SOURCE_FILES main.cpp Image.cpp Image.h Functions.h Functions.cpp Track.cpp Track.h Run.cpp Run.h)

set(CMAKE_CXX_FLAGS "-pedantic -Wall")

add_executable(Final_Project ${SOURCE_FILES} ${EASY_BMP})