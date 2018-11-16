cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Stacer)

# Adding features(build cache + faster linkers) and reasonable defaults(Debug build by default)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/cxxbasics/CXXBasics.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindPCRECPP.cmake")

# Setting a cleaner directory structure for the generated binaries
set(CMAKE_BINARY_DIR        "${CMAKE_BINARY_DIR}/output")
set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}/")
set(LIBRARY_OUTPUT_PATH     "${CMAKE_BINARY_DIR}/lib")

set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

# Activating MOC and searching for the Qt5 dependencies
set(CMAKE_AUTOMOC ON)
find_package(Qt5  COMPONENTS  Core Gui Widgets Charts Svg Concurrent REQUIRED)

# Setting the minimum C++ standard and passing the Qt-specific define
set(CMAKE_CXX_STANDARD           11)
set(CMAKE_CXX_EXTENSIONS         YES)
set(CMAKE_CXX_STANDARD_REQUIRED  YES)
add_definitions(-DQT_DEPRECATED_WARNINGS)

# GET PLATFORM AND ARCH
# we'll make lib path from these
### for the uninstal target below...
execute_process(COMMAND "uname -a"
		OUTPUT_VARIABLE SYS_UNAME
)
string(REGEX MATCH "[x|i][0-9|_]+" SYS_ARCH SYS_UNAME)
string(REGEX MATCH "^[[:alnum:]]+\\w" SYS_PLAT SYS_UNAME)
if ("${SYS_PLAT}" STREQUAL "Linux")
	string(CONCAT PREFIX_LIBARCH_DIR SYS_ARCH "-linux-gnu")
endif()

# `make clean` doesn't remove the autogen directories LMAO
# # ensure that it does
set(ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_ROOT}/stacer/stacer_autogen/*.*" "${PROJECT_ROOT}/stacer-core/stacer-core_autogen/*.*")

# Make target: `distclean` FOR REGENNING EVERYTHING
ADD_CUSTOM_TARGET(distclean @echo clean for full remake) 
ADD_CUSTOM_COMMAND(
       COMMENT "Removing CMake generated files and built files"
       COMMAND $(MAKE_COMMAND) clean && git clean -d -f
       TARGET distclean
)
# Make target: `uninstall` FOR RM'ING STUFF INSTALLED TO PREFIX
ADD_CUSTOM_TARGET(uninstall @echo uninstall from PREFIX)
ADD_CUSTOM_COMMAND(
       COMMENT "Removing files installed via make install"
       COMMAND rm -rf "${CMAKE_INSTALL_PREFIX}/lib/${PREFIX_LIBARCH_DIR}/libstacer-core.a" ; rm -rf "${CMAKE_INSTALL_PREFIX}/lib/libstacer-core.a" ; rm -rf "${CMAKE_INSTALL_PREFIX}/bin/stacer"
       TARGET uninstall
)

# Subprojects
add_subdirectory(stacer-core)
add_subdirectory(stacer)
