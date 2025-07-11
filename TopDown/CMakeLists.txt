
# TopDown Demo

add_executable(TopDown
    top_down_demo.cpp
    level_progression.h
    level_progression.cpp
    high_level_game.h
    coin.h
    coin.cpp
    floor.h
    floor.cpp
    player.h
    player.cpp
    top_down_camera.h
    top_down_camera.cpp
)
set_property(TARGET TopDown PROPERTY CXX_STANDARD 20)
target_link_libraries(TopDown PRIVATE MonaEngine Tracy::TracyClient)
target_include_directories(TopDown PRIVATE
    ${MONA_INCLUDE_DIRECTORY}
    ${THIRD_PARTY_INCLUDE_DIRECTORIES}
)

# Making OpenAL available when executing the program from Visual Studio
add_custom_command(TARGET TopDown POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:TopDown>
)

# Setting up the configuration file to use the asset directories from the source code, this is only for development.
set(APPLICATION_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
set(ENGINE_ASSETS_DIR ${CMAKE_SOURCE_DIR}/MonaEngine/EngineAssets)
configure_file(${CMAKE_SOURCE_DIR}/MonaEngine/config.json.in config.json)
add_custom_command(TARGET TopDown POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    config.json $<TARGET_FILE_DIR:TopDown>
)

# Install process
include(GNUInstallDirs)
install(TARGETS TopDown OpenAL
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/TopDown
        COMPONENT TopDown_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT TopDown_Runtime
        NAMELINK_COMPONENT TopDown_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT TopDown_Development
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/TopDown
)

install(
	DIRECTORY ${ENGINE_ASSETS_DIR}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/TopDown
)