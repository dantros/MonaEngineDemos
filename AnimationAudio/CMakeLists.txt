
# AnimationAudio

add_executable(AnimationAudio "AnimationAudio.cpp") 
set_property(TARGET AnimationAudio  PROPERTY CXX_STANDARD 20)
target_link_libraries(AnimationAudio  PRIVATE
    MonaEngine
)
target_include_directories(AnimationAudio  PRIVATE
    ${MONA_INCLUDE_DIRECTORY}
    ${THIRD_PARTY_INCLUDE_DIRECTORIES}
)

# Making OpenAL available when executing the program from Visual Studio
add_custom_command(TARGET AnimationAudio POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:AnimationAudio>
)

# Setting up the configuration file to use the asset directories from the source code, this is only for development.
set(APPLICATION_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
set(ENGINE_ASSETS_DIR ${CMAKE_SOURCE_DIR}/MonaEngine/EngineAssets)
configure_file(${CMAKE_SOURCE_DIR}/MonaEngine/config.json.in config.json)
add_custom_command(TARGET AnimationAudio POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    config.json $<TARGET_FILE_DIR:AnimationAudio>
)

# Install process
include(GNUInstallDirs)
install(TARGETS AnimationAudio OpenAL
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/Breakout2
        COMPONENT AnimationAudio_Runtime
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT BAnimationAudio_Include
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT AnimationAudio_Runtime
        NAMELINK_COMPONENT AnimationAudio_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT AnimationAudio_Development
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/AnimationAudio
)

install(
	DIRECTORY ${ENGINE_ASSETS_DIR}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/AnimationAudio
)