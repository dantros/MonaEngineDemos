
# RnD ECS

set(APPLICATION_ASSETS_DIR ${CMAKE_SOURCE_DIR}/AnimationAudio/Assets)
set(ENGINE_ASSETS_DIR ${CMAKE_SOURCE_DIR}/MonaEngine/EngineAssets)

function(Add_Example TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME}) 
    set_property(TARGET ${TARGETNAME}  PROPERTY CXX_STANDARD 20)
    target_link_libraries(${TARGETNAME}  PRIVATE
        MonaEngine
    )
    target_include_directories(${TARGETNAME}  PRIVATE
        ${MONA_INCLUDE_DIRECTORY}
        ${THIRD_PARTY_INCLUDE_DIRECTORIES}
    )

    # Making OpenAL available when executing the program from Visual Studio
    add_custom_command(TARGET ${TARGETNAME} POST_BUILD        
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:${TARGETNAME}>
    )

    # Setting up the configuration file to use the asset directories from the source code, this is only for development.
    configure_file(${CMAKE_SOURCE_DIR}/MonaEngine/config.json.in config.json)
    add_custom_command(TARGET ${TARGETNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        config.json $<TARGET_FILE_DIR:${TARGETNAME}>
    )

    # Install process
    include(GNUInstallDirs)
    install(TARGETS ${TARGETNAME} OpenAL
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/RnD-ECS
            COMPONENT RnD-ECS_Runtime
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            COMPONENT RnD-ECS_Include
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT RnD-ECS_Runtime
            NAMELINK_COMPONENT RnD-ECS_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT RnD-ECS_Development
    )
endfunction(Add_Example)

set(ECS_PROJECT_FILES
	#ECS/Components/StatComponents.hpp
	#ECS/Components/CollisionComponents.hpp
	#ECS/Components/InputComponents.hpp
	#ECS/Events/CollisionEvents.hpp
	#ECS/Events/ColorChangeEvents.hpp
	#ECS/Events/InputEvents.hpp
	#ECS/Systems/BaseSystem.hpp
	#ECS/Systems/StatsSystem.hpp
	#ECS/Systems/CollisionSystem.hpp
	#ECS/Systems/MovementSystem.hpp
	#ECS/Systems/InputSystem.hpp
	ECS/Systems/StatsSystem.cpp
	ECS/Systems/CollisionSystem.cpp
	ECS/Systems/MovementSystem.cpp
	ECS/Systems/InputSystem.cpp
)

set(ECS_EXAMPLE_FILES ECSExample.cpp ${ECS_PROJECT_FILES})
Add_Example(ECSExample "${ECS_EXAMPLE_FILES}")

set(ECS_BREAKOUT_FILES ECSBreakout.cpp ${ECS_PROJECT_FILES})
Add_Example(ECSBreakout "${ECS_BREAKOUT_FILES}")

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/AnimationAudio/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/RnD-ECS
)

install(
    DIRECTORY ${ENGINE_ASSETS_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/RnD-ECS
)