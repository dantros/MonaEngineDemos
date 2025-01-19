
# BreakoutPhysics Demo

add_executable(BreakoutPhysics "breakout_physics.cpp") 
set_property(TARGET BreakoutPhysics  PROPERTY CXX_STANDARD 20)
target_link_libraries(BreakoutPhysics  PRIVATE
    MonaEngine
    breakout_lib
)
target_include_directories(BreakoutPhysics  PRIVATE
    ${MONA_INCLUDE_DIRECTORY}
    ${THIRD_PARTY_INCLUDE_DIRECTORIES}
    ${breakout_lib_INCLUDES}
)

# Making OpenAL available when executing the program from Visual Studio
add_custom_command(TARGET BreakoutPhysics POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:BreakoutPhysics>
)

# Setting up the configuration file to use the asset directories from the source code, this is only for development.
set(APPLICATION_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
set(ENGINE_ASSETS_DIR ${CMAKE_SOURCE_DIR}/MonaEngine/EngineAssets)
configure_file(${CMAKE_SOURCE_DIR}/MonaEngine/config.json.in config.json)
add_custom_command(TARGET BreakoutPhysics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    config.json $<TARGET_FILE_DIR:BreakoutPhysics>
)

# Install process
include(GNUInstallDirs)
install(TARGETS BreakoutPhysics OpenAL
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/BreakoutPhysics
        COMPONENT BreakoutPhysics_Runtime
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT BreakoutPhysics_Include
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT BreakoutPhysics_Runtime
        NAMELINK_COMPONENT BreakoutPhysics_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT BreakoutPhysics_Development
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/BreakoutPhysics
)

install(
	DIRECTORY ${ENGINE_ASSETS_DIR}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/BreakoutPhysics
)