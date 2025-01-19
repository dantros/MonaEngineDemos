
# RnD IK

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
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/RnD-IK
            COMPONENT RnD-IK_Runtime
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            COMPONENT RnD-IK_Include
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT RnD-IK_Runtime
            NAMELINK_COMPONENT RnD-IK_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT RnD-IK_Development
    )
endfunction(Add_Example)

Add_Example(IKBasicExample IKBasicExample.cpp)
Add_Example(IKMultipleCharactersExample IKMultipleCharactersExample.cpp)
Add_Example(IKMultipleTerrainsExample IKMultipleTerrainsExample.cpp)
Add_Example(IKTest IKTest.cpp)
Add_Example(NoIKTest NoIKTest.cpp)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/AnimationAudio/Assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/RnD-IK
)

install(
    DIRECTORY ${ENGINE_ASSETS_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/RnD-IK
)