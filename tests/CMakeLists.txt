add_executable(test_flower
    test_flower.cpp
    ${PROJECT_SOURCE_DIR}/src/flower.cpp
)

target_include_directories(test_flower PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_flower PRIVATE
    glm::glm
)

target_compile_features(test_flower PRIVATE cxx_std_17)

add_test(NAME flower_geometry COMMAND test_flower)
