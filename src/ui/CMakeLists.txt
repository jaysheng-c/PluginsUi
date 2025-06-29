add_library(ui SHARED)

set(UiHeader
        ${CMAKE_CURRENT_LIST_DIR}/main_window.h
)
set(UiSource
        ${CMAKE_CURRENT_LIST_DIR}/main_window.cpp
)

target_sources(ui PRIVATE ${UiHeader} ${UiSource})
target_link_libraries(ui PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)