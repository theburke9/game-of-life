add_library(game STATIC game.c)
target_link_libraries(game PUBLIC core SDL3::SDL3)
target_include_directories(game PUBLIC ${PROJECT_SOURCE_DIR})
