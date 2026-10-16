cmake_minimum_required(VERSION 3.20)
project(autopc_sdk C CXX)

include(VeloCE)

# Build each demo with the AutoPC helper compiled in.
velo_add_executable(hello examples/hello/hello.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/hello/hello.rc)
target_include_directories(hello PRIVATE include)

velo_add_executable(stonks examples/stonks/stonks.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/stonks/stonks.rc)
target_include_directories(stonks PRIVATE include)

velo_add_executable(visualiser examples/visualiser/visualiser.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/visualiser/visualiser.rc)
target_include_directories(visualiser PRIVATE include)

# Import libraries for the Auto PC's own DLLs, named as the device exports them.
file(GLOB AUTOPC_EXPORT_LISTS "${CMAKE_CURRENT_SOURCE_DIR}/exports/*.txt")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/autopc")
foreach(exports IN LISTS AUTOPC_EXPORT_LISTS)
    get_filename_component(dll "${exports}" NAME_WE)
    string(TOUPPER "${dll}" dll_upper)
    set(stubs "${CMAKE_BINARY_DIR}/autopc/${dll}.S")
    add_custom_command(
        OUTPUT "${stubs}"
        COMMAND "${Python3_EXECUTABLE}" "${VELO_TOOLCHAIN_ROOT}/tools/mkimplib.py" "${exports}" "${dll_upper}.dll" "${stubs}" --arch ${VELO_ARCH}
        DEPENDS "${exports}" "${VELO_TOOLCHAIN_ROOT}/tools/mkimplib.py"
        VERBATIM)
    add_library(autopc_${dll} STATIC EXCLUDE_FROM_ALL "${stubs}")
    add_library(autopc::${dll} ALIAS autopc_${dll})
endforeach()

# Build a program against Microsoft's Auto PC SDK headers, as the SDK's samples were.
function(autopc_add_sdk_executable target)
    set(VELO_RC_INCLUDES "${PROJECT_SOURCE_DIR}/sdk/include")
    velo_add_executable(${target} ${ARGN})
    target_sources(${target} PRIVATE "${PROJECT_SOURCE_DIR}/src/sdk_guids.cpp")
    target_include_directories(${target} SYSTEM BEFORE PRIVATE "${PROJECT_SOURCE_DIR}/sdk/compat" "${PROJECT_SOURCE_DIR}/sdk/include")
    target_compile_definitions(${target} PRIVATE UNDER_CE=200 UNICODE _UNICODE _WIN32 WIN32 _MSC_VER=1200 __asm=__velo_shx_asm)
    target_compile_options(${target} PRIVATE -fms-extensions -fms-compatibility -fdeclspec -fretain-comments-from-system-headers)
    target_link_libraries(${target} PRIVATE velo::ole32 velo::oleaut32 autopc::coredll autopc::asfc autopc::apcdll)
endfunction()

# Microsoft's Bandit sample, when its source is in examples/bandit (not in the repository).
if(EXISTS "${PROJECT_SOURCE_DIR}/examples/bandit/oabmain.cpp")
    autopc_add_sdk_executable(bandit examples/bandit/oabmain.cpp examples/bandit/oabapp.cpp examples/bandit/oabsinks.cpp examples/bandit/oabwheel.cpp
        RESOURCES examples/bandit/bandit.rc)
endif()

