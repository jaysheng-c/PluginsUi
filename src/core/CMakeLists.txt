add_library(core SHARED)

set(CoreHeader
        ${CMAKE_CURRENT_LIST_DIR}/../plugins/plugin_interface.h
        ${CMAKE_CURRENT_LIST_DIR}/engine/table_engine.h
)
set(CoreSource
        ${CMAKE_CURRENT_LIST_DIR}/engine/table_engine.cpp
)

target_sources(core PRIVATE ${CoreHeader} ${CoreSource})
target_link_libraries(core PRIVATE
        Qt::Core
)
target_compile_definitions(core PRIVATE CORE_LIBRARY)