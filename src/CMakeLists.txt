add_executable(ImageProcApp main.cpp)

add_library(ImageProc ImageProc/Image.cpp)

target_link_libraries(ImageProcApp ImageProc)

