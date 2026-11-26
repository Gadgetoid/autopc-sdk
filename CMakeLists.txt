cmake_minimum_required(VERSION 3.20)
project(autopc_sdk C CXX)

include(VeloCE)

if(VELO_ARCH STREQUAL "x86")
    set(AUTOPC_AUTORUN_SECTION X86)
    set(AUTOPC_PACKAGE_TARGET joyride)
else()
    set(AUTOPC_AUTORUN_SECTION shx)
    set(AUTOPC_PACKAGE_TARGET 310c)
endif()

# Package a program as a card installer: card/<target>/AUTORUN.INF and <target>.cei.
function(autopc_add_package target name)
    if(Python3_VERSION VERSION_LESS 3.11)
        message(WARNING "Packaging ${target} needs Python 3.11 or later (tomllib)")
        return()
    endif()
    set(card "${CMAKE_BINARY_DIR}/card/${target}")
    set(manifest "${CMAKE_BINARY_DIR}/packages/${target}.toml")
    file(GENERATE OUTPUT "${card}/AUTORUN.INF"
        CONTENT "[AutoPC.${AUTOPC_AUTORUN_SECTION}]\nTitle=${name} Install\nItem1=${name} 1.0\nOpen1=${target}.cei\n" NEWLINE_STYLE CRLF)
    file(GENERATE OUTPUT "${manifest}"
        CONTENT "[package]\nname = \"${name}\"\nversion = \"1.0\"\ntarget = \"${AUTOPC_PACKAGE_TARGET}\"\n\n[[file]]\nsource = '$<TARGET_FILE_DIR:${target}>/${target}.exe'\nshortcut = \"${name}\"\n\n[menu]\nname = \"${name}\"\n")
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${Python3_EXECUTABLE}" "${PROJECT_SOURCE_DIR}/tools/ceipack.py" "${manifest}" "${card}/${target}.cei"
        VERBATIM)
endfunction()

# Build each demo with the AutoPC helper compiled in.
velo_add_executable(hello examples/hello/hello.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/hello/hello.rc)
target_include_directories(hello PRIVATE include)
autopc_add_package(hello "Hello")

velo_add_executable(stonks examples/stonks/stonks.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/stonks/stonks.rc)
target_include_directories(stonks PRIVATE include)
autopc_add_package(stonks "Stonks")

velo_add_executable(pclink examples/pclink/pclink.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/pclink/pclink.rc)
target_include_directories(pclink PRIVATE include)

velo_add_executable(visualiser examples/visualiser/visualiser.c src/autopc.c src/autopc_app.c
    ICON assets/autopc.ico RESOURCES examples/visualiser/visualiser.rc)
target_include_directories(visualiser PRIVATE include)

if(VELO_ARCH STREQUAL "x86")
    velo_add_executable(ctprobe examples/ctprobe/ctprobe.c src/autopc.c src/autopc_app.c
        ICON assets/autopc.ico RESOURCES examples/ctprobe/ctprobe.rc)
    target_include_directories(ctprobe PRIVATE include)
    autopc_add_package(ctprobe "CT Probe")

    velo_add_executable(bigscreen examples/bigscreen/bigscreen.c src/autopc.c src/autopc_app.c
        ICON assets/autopc.ico RESOURCES examples/bigscreen/bigscreen.rc)
    target_include_directories(bigscreen PRIVATE include)
    autopc_add_package(bigscreen "Big Screen")

    velo_add_executable(bigvis examples/bigvis/bigvis.c src/autopc.c src/autopc_app.c
        ICON assets/autopc.ico RESOURCES examples/bigvis/bigvis.rc)
    target_include_directories(bigvis PRIVATE include)
    autopc_add_package(bigvis "Big Visualiser")

    velo_add_executable(msgtest examples/msgtest/msgtest.c src/autopc.c src/autopc_app.c
        ICON assets/autopc.ico RESOURCES examples/msgtest/msgtest.rc)
    target_include_directories(msgtest PRIVATE include)
    target_link_libraries(msgtest PRIVATE velo::msgstore)
    autopc_add_package(msgtest "Msg Test")

    set(HELIX "${PROJECT_SOURCE_DIR}/third_party/libhelix-mp3-0a0e0673f82bc6804e5a3ddb15fb6efdcde747cd")
    add_library(helix_mp3 STATIC EXCLUDE_FROM_ALL
        "${HELIX}/mp3dec.c"
        "${HELIX}/mp3tabs.c"
        "${HELIX}/real/bitstream.c"
        "${HELIX}/real/buffers.c"
        "${HELIX}/real/dct32.c"
        "${HELIX}/real/dequant.c"
        "${HELIX}/real/dqchan.c"
        "${HELIX}/real/huffman.c"
        "${HELIX}/real/hufftabs.c"
        "${HELIX}/real/imdct.c"
        "${HELIX}/real/polyphase.c"
        "${HELIX}/real/scalfact.c"
        "${HELIX}/real/stproc.c"
        "${HELIX}/real/subband.c"
        "${HELIX}/real/trigtabs.c"
        src/mp3_stream.c)
    target_include_directories(helix_mp3 PUBLIC "${HELIX}/pub" include PRIVATE "${HELIX}/real")
    target_compile_options(helix_mp3 PRIVATE -O2 -w -include "${PROJECT_SOURCE_DIR}/src/helix_c.h")
    target_link_libraries(helix_mp3 PRIVATE velo::headers)

    velo_add_executable(changerplay examples/changerplay/changerplay.c src/autopc.c src/autopc_app.c
        ICON assets/autopc.ico RESOURCES examples/changerplay/changerplay.rc)
    target_include_directories(changerplay PRIVATE include)
    target_link_libraries(changerplay PRIVATE helix_mp3)
    autopc_add_package(changerplay "Changer Play")
endif()

# Import libraries for the Auto PC's own DLLs, named as the device exports them.
if(VELO_ARCH STREQUAL "x86")
    set(AUTOPC_EXPORTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/exports/x86")
else()
    set(AUTOPC_EXPORTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/exports")
endif()
file(GLOB AUTOPC_EXPORT_LISTS "${AUTOPC_EXPORTS_DIR}/*.txt")
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
    target_compile_definitions(${target} PRIVATE UNDER_CE=200 UNICODE _UNICODE _WIN32 WIN32 _MSC_VER=1200)
    target_compile_options(${target} PRIVATE -fms-extensions -fms-compatibility -fdeclspec -fretain-comments-from-system-headers)
    if(VELO_ARCH STREQUAL "x86")
        target_compile_definitions(${target} PRIVATE _INTEGRAL_MAX_BITS=64)
        target_compile_options(${target} PRIVATE -fasm-blocks)
    else()
        target_compile_definitions(${target} PRIVATE __asm=__velo_shx_asm)
    endif()
    set(libraries velo::ole32 velo::oleaut32)
    if(TARGET autopc::coredll)
        list(APPEND libraries autopc::coredll)
    endif()
    target_link_libraries(${target} PRIVATE ${libraries} autopc::asfc autopc::apcdll)
endfunction()

# Microsoft's Bandit sample, when its source is in examples/bandit (not in the repository).
if(EXISTS "${PROJECT_SOURCE_DIR}/examples/bandit/oabmain.cpp")
    autopc_add_sdk_executable(bandit examples/bandit/oabmain.cpp examples/bandit/oabapp.cpp examples/bandit/oabsinks.cpp examples/bandit/oabwheel.cpp
        RESOURCES examples/bandit/bandit.rc)
endif()

