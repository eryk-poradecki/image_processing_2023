add_executable(ImageProcApp main.cpp)

add_library(ImageProc ImageProc/Image.cpp)

target_include_directories(ImageProcApp PRIVATE ${CMAKE_SOURCE_DIR}/libs)

target_link_libraries(ImageProcApp ImageProc)


