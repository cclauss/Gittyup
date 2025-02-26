# Define test macro.
macro(test)
  cmake_parse_arguments(ARG "NO_WIN32_OFFSCREEN" "NAME" "" ${ARGN})

  add_executable(test_${ARG_NAME} ${ARG_NAME}.cpp)
  target_link_libraries(test_${ARG_NAME} testlib)

  set_target_properties(test_${ARG_NAME} PROPERTIES OUTPUT_NAME ${ARG_NAME}
                                                    AUTOMOC ON)

  target_include_directories(
    test_${ARG_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src
                             ${CMAKE_CURRENT_BINARY_DIR})

  add_test(NAME ${ARG_NAME} COMMAND $<TARGET_FILE:test_${ARG_NAME}>)
  add_dependencies(check_build test_${ARG_NAME})

  if(${ARG_NO_WIN32_OFFSCREEN})
    set_property(
      TEST ${ARG_NAME}
      APPEND
      PROPERTY LABELS "NO_WIN32_OFFSCREEN")
  endif()

  if(WIN32)
    find_package(Qt5Gui)
    string(REPLACE ";" "\;" NEWPATH "$ENV{PATH}")
    string(REPLACE ";" "\;" PLUGIN_PATH
                   "$<TARGET_FILE_DIR:Qt5::QOffscreenIntegrationPlugin>")

    if(${ARG_NO_WIN32_OFFSCREEN})
      set(PLATFORM "windows")
    else()
      set(PLATFORM "offscreen")
    endif()

    set_tests_properties(
      ${ARG_NAME}
      PROPERTIES
        ENVIRONMENT
        "PATH=${CMAKE_BINARY_DIR}\;${NEWPATH};QT_QPA_PLATFORM_PLUGIN_PATH=${PLUGIN_PATH};QT_QPA_PLATFORM=offscreen"
    )
  else()
    set_tests_properties(${ARG_NAME} PROPERTIES ENVIRONMENT
                                                "QT_QPA_PLATFORM=offscreen")
  endif()
endmacro()

add_custom_target(check_build)

# Add check target.
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure
          --timeout 300
  DEPENDS check_build
  COMMENT "Running tests..."
  USES_TERMINAL)

# Add check target excluding NO_WIN32_OFFSCREEN tests.
add_custom_target(
  check_no_win32_offscreen
  COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure
          --timeout 300 --label-exclude NO_WIN32_OFFSCREEN
  DEPENDS check_build
  COMMENT "Running tests..."
  USES_TERMINAL)

enable_testing()

# Add test library.
add_subdirectory(dep/zip)
add_library(testlib Test.cpp)
target_link_libraries(testlib app git ui Qt5::Test zip)
target_include_directories(testlib PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(
  testlib PRIVATE TESTREPOSITORIES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/testRepos")

# Add tests.
test(NAME bare_repo)
test(NAME init_repo)
test(NAME merge)
test(NAME external_tools_dialog)
test(NAME config)
test(NAME branches_panel NO_WIN32_OFFSCREEN)
test(NAME editor NO_WIN32_OFFSCREEN)
test(NAME index)
test(NAME line_endings NO_WIN32_OFFSCREEN)
test(NAME log)
test(NAME main_window)
test(NAME new_branch_dialog)
test(NAME sanity)
test(NAME HunkWidget)
test(NAME Diff)
test(NAME EditorLineInfos)
test(NAME CommitAuthorCommitter)
