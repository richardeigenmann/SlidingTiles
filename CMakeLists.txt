CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(sliding-tiles)

# To run with Clang:
# cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang ..

SET(CMAKE_CXX_STANDARD 17)
IF (WIN32)
  SET(SFML_ROOT "C:/Users/Richard/Documents/SFML-2.4.2")
  SET(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" "${PROJECT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")
  message( STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
  message( STATUS "CMAKE_CL_64: ${CMAKE_CL_64}")
ENDIF (WIN32)
IF (UNIX)
    # Since SFML 2.5 everything is now easier: see https://en.sfml-dev.org/forums/index.php?topic=24070.0
    #SET(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" "${PROJECT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")

    SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
    ## If you want to link SFML statically
    # set(SFML_STATIC_LIBRARIES TRUE)

    ## In most cases better set in the CMake cache
    # set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
ENDIF (UNIX)


FIND_PACKAGE(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
MESSAGE(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
MESSAGE(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")

find_package(ZeroMQ)
MESSAGE(STATUS "ZeroMQ_INCLUDE_DIR: ${ZeroMQ_INCLUDE_DIR}")
MESSAGE(STATUS "ZeroMQ_LIBRARIES: ${ZeroMQ_LIBRARIES}")

# See http://mariobadr.com/using-clang-tidy-with-cmake-36.html
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
  )
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*,-fuchsia-*")
endif()


SET( sliding-tiles_assets_dir "${PROJECT_SOURCE_DIR}/sliding-tiles-assets")
SET( sliding-tiles-assets
    ${sliding-tiles_assets_dir}/Raleway-Regular.ttf

    ${sliding-tiles_assets_dir}/bottomright.png
    ${sliding-tiles_assets_dir}/endbottom.png
    ${sliding-tiles_assets_dir}/endright.png
    ${sliding-tiles_assets_dir}/endtop.png
    ${sliding-tiles_assets_dir}/endleft.png
    ${sliding-tiles_assets_dir}/horizontal.png
    ${sliding-tiles_assets_dir}/leftbottom.png
    ${sliding-tiles_assets_dir}/lefttop.png
    ${sliding-tiles_assets_dir}/startbottom.png
    ${sliding-tiles_assets_dir}/startleft.png
    ${sliding-tiles_assets_dir}/startright.png
    ${sliding-tiles_assets_dir}/starttop.png
    ${sliding-tiles_assets_dir}/topright.png
    ${sliding-tiles_assets_dir}/vertical.png
    ${sliding-tiles_assets_dir}/empty.png
    ${sliding-tiles_assets_dir}/trophy.png
    ${sliding-tiles_assets_dir}/undo.png
    ${sliding-tiles_assets_dir}/over_par.png

    ${sliding-tiles_assets_dir}/sliding-tiles.json

    ${sliding-tiles_assets_dir}/GuetGmacht.ogg
    ${sliding-tiles_assets_dir}/CooliSach.ogg
    ${sliding-tiles_assets_dir}/AechtStarch.ogg
    ${sliding-tiles_assets_dir}/HammerGuet.ogg
    ${sliding-tiles_assets_dir}/EsKlarsTalaent.ogg
    ${sliding-tiles_assets_dir}/KonkretKrassMann.ogg
    ${sliding-tiles_assets_dir}/Awesome.ogg
    ${sliding-tiles_assets_dir}/WieEnWaeltmeister.ogg
    ${sliding-tiles_assets_dir}/Saubi.ogg

    ${sliding-tiles_assets_dir}/HaeschMueh.ogg
    ${sliding-tiles_assets_dir}/HuereStrengGaell.ogg
    ${sliding-tiles_assets_dir}/NurNoEsPaarWenigiZueueg.ogg
    ${sliding-tiles_assets_dir}/DasHettNoJedesChindBesserChoenne.ogg
    ${sliding-tiles_assets_dir}/Warmduscher.ogg
    ${sliding-tiles_assets_dir}/IschEsZSchwirig.ogg

    ${sliding-tiles_assets_dir}/button_restart.png
    ${sliding-tiles_assets_dir}/button_random.png
    ${sliding-tiles_assets_dir}/button_next.png
)

SET( SOURCE_FILES
    game.cpp
    gameView.cpp
    tileView.cpp
    tile.cpp
    texturesSingleton.cpp
    renderingSingleton.cpp
    direction.cpp
    tileType.cpp
    moveNode.cpp
    gameBoard.cpp
    puzzleSolver.cpp
    json.hpp
    button.cpp
    label.cpp
    randomSoundPlayer.cpp
    winnerBlingBling.cpp
    zmqSingleton.cpp
    debugMessageListener.cpp
    attitudeSoundPlayer.cpp
    levelLabel.cpp
    parLabel.cpp
    movesLabel.cpp
    overPar.cpp
)

set( UNIT_TESTS
    game.tests.cpp
    gameView.tests.cpp
    tileView.tests.cpp
    tile.tests.cpp
    texturesSingleton.tests.cpp
    renderingSingleton.tests.cpp
    direction.tests.cpp
    tileType.tests.cpp
    gameBoard.tests.cpp
    puzzleSolver.tests.cpp
    button.tests.cpp
    move.tests.cpp
    debugMessageListener.cpp
    attitudeSoundPlayer.cpp
)

ADD_EXECUTABLE(sliding-tiles main.cpp ${SOURCE_FILES})

ADD_CUSTOM_COMMAND( TARGET sliding-tiles POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo About to make target asset directory
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:sliding-tiles>/sliding-tiles-assets
  COMMAND ${CMAKE_COMMAND} -E echo About to copy sliding-tiles-assets to target with copy_if_different
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${sliding-tiles_assets_dir} $<TARGET_FILE_DIR:sliding-tiles>/sliding-tiles-assets/
)

TARGET_INCLUDE_DIRECTORIES(sliding-tiles PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${SFML_INCLUDE_DIR}
    ${ZeroMQ_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(sliding-tiles LINK_PUBLIC
    #${SFML_LIBRARIES}
    sfml-graphics  sfml-window sfml-system sfml-audio
    ${ZeroMQ_LIBRARIES}
    stdc++fs
)

if(CLANG_TIDY_EXE)
  set_target_properties(
    sliding-tiles PROPERTIES
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  )
endif()


#INSTALL(TARGETS sliding-tiles "/usr/local/bin")

IF (WIN32)
  ADD_CUSTOM_COMMAND( TARGET sliding-tiles POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${SFML_ROOT}/bin $<TARGET_FILE_DIR:sliding-tiles>
  )
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sliding-tiles)
  set_target_properties(sliding-tiles PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $(Configuration))
ENDIF (WIN32)


# Download and unpack googletest at configure time
# see https://crascit.com/2015/07/25/cmake-gtest/
# copy the CMakeLists.txt.in to build area as CMakeLists.txt
configure_file( CMakeLists.txt.in googletest-download/CMakeLists.txt )
# we need to execute the build steps at config time so that
# the tests can find the gtest libraries when they configure
execute_process( COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process( COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
option(INSTALL_GMOCK "Install Googletest's GMock?" OFF)
option(INSTALL_GTEST "Install Googletest's GTest?" OFF)
add_subdirectory( ${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build )

# these steps compile and link the unit-tests executable
enable_testing()  # gives us a make test target
add_test( all unit-tests ) # gives us a make test all target
add_executable( unit-tests test-main.cpp ${SOURCE_FILES} ${UNIT_TESTS} )
TARGET_INCLUDE_DIRECTORIES( unit-tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${SFML_INCLUDE_DIR}
    ${ZeroMQ_INCLUDE_DIR}
)
target_link_libraries( unit-tests LINK_PUBLIC
    gtest
    gmock
    #${SFML_LIBRARIES}
    sfml-graphics sfml-window sfml-system sfml-audio
    ${ZeroMQ_LIBRARIES}
    stdc++fs
)


# see http://stackoverflow.com/questions/13116488/detailed-guide-on-using-gcov-with-cmake-cdash
IF (WIN32)
  SET(CHECK_COVERAGE OFF)
ENDIF (WIN32)
IF (UNIX)
    SET(CHECK_COVERAGE ON)
ENDIF (UNIX)
if (CHECK_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage unit-tests coverage)
ENDIF (CHECK_COVERAGE)


SET(LEVEL_GENERATOR_SOURCE_FILES
    gameBoard.cpp
    moveNode.cpp
    direction.cpp
    tile.cpp
    tileType.cpp
    puzzleSolver.cpp
    zmqSingleton.cpp
    debugMessageListener.cpp
)


ADD_EXECUTABLE(levelGenerator levelGenerator.cpp ${LEVEL_GENERATOR_SOURCE_FILES})
TARGET_INCLUDE_DIRECTORIES(levelGenerator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${ZeroMQ_INCLUDE_DIR}
)
TARGET_LINK_LIBRARIES(levelGenerator LINK_PUBLIC
    ${ZeroMQ_LIBRARIES}
)


# set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM;TZ;ZIP;TBZ2;DEB")
set(CPACK_PACKAGE_NAME "sliding-tiles")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sliding Tiles Game")
set(CPACK_RPM_PACKAGE_DESCRIPTION "The Sliding Tiles Game written by Richard Eigenmann")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_CONTACT "Richard Eigenmann")
set(CPACK_PACKAGE_VENDOR "Richard Eigenmann")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
SET(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/richardeigenmann/SlidingTiles")
set(CPACK_PACKAGE_CHECKSUM "MD5")
#SET(CPACK_PACKAGE_EXECUTABLES "sliding-tiles;Slding Tiles Game")
SET(CPACK_RPM_PACKAGE_REQUIRES "libzmq5 libsfml2-2_5 Mesa")
SET(CPACK_RPM_INSTALL_WITH_EXEC ON)
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libzmq5,libsfml-audio2.5,libsfml-graphics2.5,libsfml-network2.5,libsfml-system2.5,libsfml-window2.5")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
install(TARGETS sliding-tiles
  RUNTIME
  DESTINATION "bin")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/sliding-tiles-assets/" DESTINATION "bin/sliding-tiles-assets")
include(CPack)


# Additional target to perform clang-format run
# Requires clang-format 



# Get all project files
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)

add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)

#add_custom_target(
#        clang-tidy
#        COMMAND /usr/bin/clang-tidy
#        ${ALL_SOURCE_FILES}
#        -config=''
#        --
#        -std=c++17
#        ${INCLUDE_DIRECTORIES} ${SFML_INCLUDE_DIR} ${ZeroMQ_INCLUDE_DIR} gtest gmock
#    
#)

# This creates a compile_commands.json file for SourceTrail
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
