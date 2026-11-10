add_library(render STATIC render.c)
target_link_libraries(render PUBLIC game SDL3::SDL3)
target_include_directories(render PUBLIC ${PROJECT_SOURCE_DIR})
