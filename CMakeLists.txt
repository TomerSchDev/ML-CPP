cmake_minimum_required(VERSION 3.16)
project(MLCPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(NN main.cpp Vector.h Matrix.h LiniarAlgebra.cpp LiniarAlgebra.h ML.cpp ML.h "Activation Functions.h" "Activation Functions.cpp")
