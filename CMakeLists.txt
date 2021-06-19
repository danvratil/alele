cmake_minimum_required(VERSION 3.19)

project(alele LANGUAGES CXX VERSION 1.0)

set(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake
        ${CMAKE_BINARY_DIR}
        ${CMAKE_MODULE_PATH}
)

# --------------------------------------------------------#
# Compiler settings
# --------------------------------------------------------#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

enable_testing()

# --------------------------------------------------------#
# Dependencies
# --------------------------------------------------------#

include(${CMAKE_SOURCE_DIR}/cmake/conan.cmake)
conan_cmake_configure(REQUIRES tl-expected/1.0.0
                      GENERATORS cmake_find_package)
conan_cmake_autodetect(conan_settings)
conan_cmake_install(PATH_OR_REFERENCE .
    BUILD missing
    REMOTE conan-center
    SETTINGS ${conan_settings}
)



find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(libzmq 4.3 REQUIRED)
find_package(Threads REQUIRED)
find_package(Xapian REQUIRED)
find_package(msgpack REQUIRED)
find_package(QCoro REQUIRED)
find_package(tl-expected REQUIRED)

qcoro_enable_coroutines()

if (BUILD_TESTING)
    # Force using FindGTest from GTest rather than CMake's own FindGTest
    # (which doesn't support GMock)
    find_package(GTest REQUIRED NO_CMAKE_SYSTEM_PATH)
    include(GoogleTest)
endif()

# --------------------------------------------------------#
# Subdirectories
# --------------------------------------------------------#

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

# --------------------------------------------------------#
# Summary
# --------------------------------------------------------#

include(FeatureSummary)

feature_summary(FATAL_ON_MISSING_REQUIRED_PACKAGES WHAT ALL)
