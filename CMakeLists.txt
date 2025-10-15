cmake_minimum_required(VERSION 3.15)
project(
  zroc
  VERSION 1.0.0
  LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c)

add_library(zroc SHARED ${SRC_FILES})

target_include_directories(zroc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(zroc PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

install(
  TARGETS zroc
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)
install(DIRECTORY include/ DESTINATION include)

include(GNUInstallDirs)
configure_file(zroc.pc.in zroc.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/zroc.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

enable_testing()

file(GLOB TEST_SOURCES tests/*.c)
add_executable(all_tests ${TEST_SOURCES})
target_include_directories(all_tests
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(all_tests PRIVATE zroc criterion)
add_test(NAME all_tests COMMAND all_tests)
