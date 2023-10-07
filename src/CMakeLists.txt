add_executable(ImageProcApp
    main.cpp
    config.hpp)

set(SOURCE_FILES
    ImageProc/Types.cpp
	  ImageProc/Types.h
    ImageProc/ElementaryOperations.cpp
    ImageProc/ElementaryOperations.h
    ImageProc/GeometricOperations.h
    ImageProc/GeometricOperations.cpp
    ImageProc/Helpers.h
    ImageProc/Helpers.cpp
    ImageProc/Exceptions.h
    ImageProc/Exceptions.cpp
    ImageProc/ImgAnalysis.cpp
    ImageProc/ImgAnalysis.h
    )

add_library(ImageProc ${SOURCE_FILES})

add_library(CLI
    CLI/InputParser.cpp
    CLI/InputParser.hpp)

target_include_directories(ImageProc
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include the source directory
)
target_include_directories(ImageProcApp PRIVATE ${CMAKE_SOURCE_DIR}/libs)

target_link_libraries(ImageProcApp ImageProc CLI)
