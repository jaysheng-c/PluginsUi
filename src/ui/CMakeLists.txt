add_library(ui SHARED)

#set(QML_SOURCE_FILES resource/ui.qrc)
#qt_add_resources(${QML_SOURCE_FILES})

# 设置导出宏和包含路径
target_include_directories(ui
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

# UI模块自包含的构建配置
set(UI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/main_window.cpp
)

target_compile_definitions(ui PRIVATE UI_LIBRARY)

target_sources(ui PRIVATE
        ${UI_SOURCES}
#        ${QML_SOURCE_FILES}
)

# 链接必要的Qt模块
target_link_libraries(ui PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Gui
)