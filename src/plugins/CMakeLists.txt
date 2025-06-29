add_library(plugins SHARED)

set(PluginsHeader
        ${CMAKE_CURRENT_SOURCE_DIR}/plugin_interface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/excel/excel_importer.h
)

set(PluginsSource
        ${CMAKE_CURRENT_SOURCE_DIR}/excel/excel_importer.cpp
)

target_sources(plugins PRIVATE ${PluginsHeader} ${PluginsSource})
target_link_libraries(plugins PRIVATE
        Qt::Core
        Qt::Gui
        QXlsx::QXlsx
)
target_compile_definitions(plugins PRIVATE PLUGINS_LIBRARY)