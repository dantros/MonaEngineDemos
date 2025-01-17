
add_subdirectory(breakout_lib)
set(breakout_lib_INCLUDES breakout_lib/public)

add_executable(BreakoutMona "breakout.cpp") 
set_property(TARGET BreakoutMona  PROPERTY CXX_STANDARD 20)
target_link_libraries(BreakoutMona  PRIVATE
    MonaEngine
    breakout_lib
)
target_include_directories(BreakoutMona  PRIVATE
    ${MONA_INCLUDE_DIRECTORY}
    ${THIRD_PARTY_INCLUDE_DIRECTORIES}
    ${breakout_lib_INCLUDES}
)
add_custom_command(TARGET BreakoutMona POST_BUILD        
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:BreakoutMona>
)

# Setting up the configuration file to use the asset directories from the source code, this is only for development.
set(APPLICATION_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
set(ENGINE_ASSETS_DIR ${CMAKE_SOURCE_DIR}/MonaEngine/EngineAssets)
configure_file(${CMAKE_SOURCE_DIR}/MonaEngine/config.json.in config.json)

add_custom_command(TARGET BreakoutMona POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        config.json $<TARGET_FILE_DIR:BreakoutMona>
)

# Proceso de instalación
include(GNUInstallDirs)
install(TARGETS BreakoutMona
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT BreakoutMona_Runtime
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT BreakoutMona_Include
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT BreakoutMona_Runtime
        NAMELINK_COMPONENT BreakoutMona_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT BreakoutMona_Development
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Breakout2/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/Breakout2/bin
)