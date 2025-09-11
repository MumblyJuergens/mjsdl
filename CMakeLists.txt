cmake_minimum_required(VERSION 3.29)

project(mjsdl
        VERSION 0.1.0
        DESCRIPTION "A C++ light wrapper for SDL3 for lifetime safety (and a couple of helpers)"
        HOMEPAGE_URL "https://mumblyjuergens.github.io/mjsdl/"
        LANGUAGES CXX)

include(GNUInstallDirs)

# Are we bundled...
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(NOT_SUBPROJECT ON)
else()
  set(NOT_SUBPROJECT OFF)
endif()


find_package(SDL3 REQUIRED)
# CPMAddPackage("gh:libsdl-org/SDL#release-3.2.20")


include(cmake/mjhelpers.cmake)
include(cmake/generated.cmake)

add_library(mjsdl INTERFACE
    ${MJSDL_GENERATED_HEADERS}
    include/mjsdl/compat.hpp
    include/mjsdl/generated.hpp
    include/mjsdl/guard.hpp
    include/mjsdl/memory.hpp
    include/mjsdl/mjsdl.hpp
)
add_library(mjsdl::mjsdl ALIAS mjsdl)
target_compile_features(mjsdl INTERFACE cxx_std_14)
target_link_libraries(mjsdl INTERFACE SDL3::SDL3)
target_include_directories(mjsdl
INTERFACE   $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
IF(NOT_SUBPROJECT)
    MJSDLFullCompilerWarnings(mjsdl INTERFACE)
endif()

install(TARGETS mjsdl EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("mjsdlConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)
install(FILES
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mjsdl DESTINATION include)


if(NOT_SUBPROJECT)
    add_executable(testharness testharness/main.cpp)
    target_compile_features(testharness PUBLIC cxx_std_23)
    target_link_libraries(testharness PUBLIC mjsdl::mjsdl)
    target_compile_definitions(testharness PUBLIC -DMJSDL_GUARD_DEFAULT=mjsdl::guard_throws)
    MJSDLFullCompilerWarnings(testharness PUBLIC)
endif()

if(NOT_SUBPROJECT)
    # add_subdirectory(cmake/packaging)
endif()

