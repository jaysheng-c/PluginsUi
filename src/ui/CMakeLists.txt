add_library(ui SHARED)

set(UI_RESOURCE_FILE resource/ui.qrc)
qt_add_resources(${UI_RESOURCE_FILE})

# 设置导出宏和包含路径
target_include_directories(ui
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

# UI模块自包含的构建配置
set(UI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/main_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/main_menu_bar.cpp
)

target_compile_definitions(ui PRIVATE UI_LIBRARY)

target_sources(ui PRIVATE
        ${UI_SOURCES}
#        ${UI_RESOURCE_FILE}
)

# 链接必要的Qt模块
target_link_libraries(ui PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Gui
)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ui
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()