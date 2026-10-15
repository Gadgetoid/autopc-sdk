cmake_minimum_required(VERSION 3.20)
project(autopc_sdk C)

include(VeloCE)

# Build each demo with the AutoPC helper compiled in.
velo_add_executable(hello examples/hello/hello.c src/autopc.c)
target_include_directories(hello PRIVATE include)

velo_add_executable(stonks examples/stonks/stonks.c src/autopc.c)
target_include_directories(stonks PRIVATE include)
