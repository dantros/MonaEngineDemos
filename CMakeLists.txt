cmake_minimum_required(VERSION 3.30)
project(MonaEngineDemos C CXX)

# Building the engine
option(MONA_BUILD_EXAMPLES "" OFF)
option(MONA_INSTALL "" OFF)
option(TRACY_ENABLE "" ON)
add_subdirectory(MonaEngine)

# Building demos
option(MONAENGINEDEMOS_BUILD_ANIMATION_AUDIO "" ON)
if (${MONAENGINEDEMOS_BUILD_ANIMATION_AUDIO})
    add_subdirectory(AnimationAudio)
endif()

option(MONAENGINEDEMOS_BUILD_TOP_DOWN_DEMO "" ON)
if (${MONAENGINEDEMOS_BUILD_TOP_DOWN_DEMO})
    add_subdirectory(TopDown)
endif()

option(MONAENGINEDEMOS_BUILD_BREAKOUT2 "" ON)
if (${MONAENGINEDEMOS_BUILD_BREAKOUT2})
    add_subdirectory(Breakout2)
endif()

option(MONAENGINEDEMOS_BUILD_BREAKOUT_PHYSICS "" ON)
if (${MONAENGINEDEMOS_BUILD_BREAKOUT_PHYSICS})
    add_subdirectory(BreakoutPhysics)
endif()

option(MONAENGINEDEMOS_BUILD_RND_ECS "" ON)
if (${MONAENGINEDEMOS_BUILD_RND_ECS})
    add_subdirectory(RnD-ECS)
endif()

option(MONAENGINEDEMOS_BUILD_RND_IK "" ON)
if (${MONAENGINEDEMOS_BUILD_RND_IK})
    add_subdirectory(RnD-IK)
endif()

# Comming soon ...

#option(MONAENGINEDEMOS_BUILD_SIDE_SCROLLING_DEMO "" OFF)
#if (${MONAENGINEDEMOS_BUILD_SIDE_SCROLLING_DEMO})
#    add_subdirectory(SideScrolling)
#endif()

#option(MONAENGINEDEMOS_BUILD_FIRST_PERSON_DEMO "" OFF)
#if (${MONAENGINEDEMOS_BUILD_FIRST_PERSON_DEMO})
#    add_subdirectory(FirstPerson)
#endif()

#option(MONAENGINEDEMOS_BUILD_THIRD_PERSON_DEMO "" OFF)
#if (${MONAENGINEDEMOS_BUILD_THIRD_PERSON_DEMO})
#    add_subdirectory(ThirdPerson)
#endif()
