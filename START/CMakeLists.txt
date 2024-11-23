cmake_minimum_required(VERSION 3.16)

# Enable vcpkg integration if toolchain file is specified
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(START VERSION 1.0 LANGUAGES CXX)

# Configure CXX settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure Qt settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add this section to help find Qt6
set(Qt6_DIR "D:/QT1/6.5.0/msvc2019_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${Qt6_DIR}")

# Windows specific settings
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)
    
    # Boost specific Windows settings
    add_compile_definitions(BOOST_ALL_NO_LIB)  # Disable auto-linking
    add_compile_definitions(BOOST_ALL_DYN_LINK)  # Use dynamic linking
endif()

# Find Qt6
find_package(Qt6 COMPONENTS 
    Core
    Gui
    Widgets
    Network
    Svg
    REQUIRED
)

if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found. Please set Qt6_DIR to the appropriate path.")
endif()

# Find Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS  system filesystem)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found. Please install Boost or set BOOST_ROOT to the appropriate path.")
endif()

message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost library dirs: ${Boost_LIBRARY_DIRS}")
message(STATUS "Qt6 version: ${Qt6_VERSION}")
message(STATUS "Qt6 DIR: ${Qt6_DIR}")

add_subdirectory(util)


# Source files
set(SOURCES
    main.cpp
    START.cpp
    AuthMgr.cpp
    ClickedLabel.cpp
    customWidgets.cpp
    Device.cpp
    global.cpp
    httpmgr.cpp
    loginDialog.cpp
    registerdialog.cpp
    tcpMgr.cpp
    TimerBtn.cpp
    UserMgr.cpp
)

# Header files
set(HEADERS
    START.h
    AuthMgr.h
    ClickedLabel.h
    customWidgets.h
    Device.h
    global.h
    httpmgr.h
    loginDialog.h
    registerdialog.h
    singleton.h
    tcpMgr.h
    TimerBtn.h
    UserMgr.h
)

# UI files
set(UI_FILES
    START.ui
    loginDialog.ui
    registerdialog.ui
)

# Resource files
set(RESOURCE_FILES
    rc.qrc
)

# Add executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCE_FILES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
)

if(WIN32)
    target_link_directories(${PROJECT_NAME} PRIVATE
        ${Boost_LIBRARY_DIRS}
    )
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::Svg
    Boost::system
    Boost::filesystem
    util
)

# Set properties for IDEs
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}/bin;${Boost_LIBRARY_DIRS};$ENV{PATH}"
)

if(MSVC)
    # Enable parallel compilation
    target_compile_options(${PROJECT_NAME} PRIVATE 
        /MP
        /bigobj  # For large Boost template instantiations
    )
    
    # Enable multi-processor compilation for Release
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/LTCG"
            COMPILE_FLAGS "/GL"
        )
    endif()
endif()

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Copy resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_BINARY_DIR}/bin/res
)

# Copy Qt DLLs and other dependencies for Windows
if(WIN32)
    # Get the Qt binary directory
    get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BINARY_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    
    # Add custom command to copy Qt DLLs
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/Qt6Cored.dll>
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/Qt6Guid.dll>
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/Qt6Widgetsd.dll>
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/Qt6Networkd.dll>
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/Qt6Svgd.dll> 
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/Qt6Core.dll>
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/Qt6Gui.dll>
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/Qt6Widgets.dll>
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/Qt6Network.dll>
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/Qt6Svgd.dll> 

        ${CMAKE_BINARY_DIR}/bin
    )

    # Copy platform plugin
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/bin/platforms
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/../plugins/platforms/qwindowsd.dll>
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/../plugins/platforms/qwindows.dll>
        ${CMAKE_BINARY_DIR}/bin/platforms
    )

    # Copy TLS plugins
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/bin/plugins/tls
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${QT_BINARY_DIR}/../plugins/tls/qopensslbackendd.dll>
        $<$<CONFIG:Release>:${QT_BINARY_DIR}/../plugins/tls/qopensslbackend.dll>
        ${CMAKE_BINARY_DIR}/bin/plugins/tls
    )

    # Copy config directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/bin/config
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config/conf.properties
        ${CMAKE_BINARY_DIR}/bin/config/conf.properties
    )

    # Copy cert directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/bin/certs
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/certs/server.crt
        ${CMAKE_BINARY_DIR}/bin/certs/server.crt
    )

    # Copy style directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/bin/style
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/style/stylesheet.qss
        ${CMAKE_BINARY_DIR}/bin/style/stylesheet.qss
    )

    # Copy res directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/bin/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/bin/res
    )

    # Copy rc.qrc directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/rc.qrc
        ${CMAKE_BINARY_DIR}/bin/rc.qrc
    )
endif()