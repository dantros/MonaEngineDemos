cmake_minimum_required(VERSION 3.30)
project(MonaEngineDemos_sln C CXX)

# Building the engine
option(MONA_BUILD_EXAMPLES "" OFF)
option(MONA_INSTALL "" OFF)
add_subdirectory(MonaEngine)

# Building demos
option(BUILD_TOP_DOWN_DEMO "" ON)
if (${BUILD_TOP_DOWN_DEMO})
    add_subdirectory(TopDown)
endif()

option(BUILD_SIDE_SCROLLING_DEMO "" OFF)
if (${BUILD_SIDE_SCROLLING_DEMO})
    add_subdirectory(SideScrolling)
endif()

option(BUILD_FIRST_PERSON_DEMO "" OFF)
if (${BUILD_FIRST_PERSON_DEMO})
    add_subdirectory(FirstPerson)
endif()

option(BUILD_THIRD_PERSON_DEMO "" OFF)
if (${BUILD_THIRD_PERSON_DEMO})
    add_subdirectory(ThirdPerson)
endif()
