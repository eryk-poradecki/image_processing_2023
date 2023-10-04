add_executable(ImageProcApp
    main.cpp
    config.hpp)

add_library(ImageProc
	ImageProc/Types.cpp
	ImageProc/Types.h
    ImageProc/ElementaryOperations.cpp
    ImageProc/ElementaryOperations.h)
add_library(CLI
    CLI/InputParser.cpp
    CLI/InputParser.hpp)

target_include_directories(ImageProcApp PRIVATE ${CMAKE_SOURCE_DIR}/libs)

target_link_libraries(ImageProcApp ImageProc CLI)
