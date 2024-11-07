
add_executable(TopDown "top_down_demo.cpp")
set_property(TARGET TopDown  PROPERTY CXX_STANDARD 20)
target_link_libraries(TopDown  PRIVATE MonaEngine)

target_include_directories(TopDown PRIVATE
    ${MONA_INCLUDE_DIRECTORY}
    ${THIRD_PARTY_INCLUDE_DIRECTORIES}
)
add_custom_command(TARGET TopDown POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:TopDown>
)

# Setting up the configuration file to use the asset directories from the source code, this is only for development.
set(APPLICATION_ASSETS_DIR ${CMAKE_SOURCE_DIR}/Assets)
set(ENGINE_ASSETS_DIR ${CMAKE_SOURCE_DIR}/MonaEngine/EngineAssets)
configure_file(${CMAKE_SOURCE_DIR}/MonaEngine/config.json.in config.json)

add_custom_command(TARGET TopDown POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    config.json $<TARGET_FILE_DIR:TopDown>
)

# Install process
include(GNUInstallDirs)
install(TARGETS TopDown
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT TopDown_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT TopDown_Runtime
        NAMELINK_COMPONENT TopDown_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT TopDown_Development
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)