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
    ImageProc/NoiseRemoval.h
    ImageProc/NoiseRemoval.cpp
    ImageProc/Helpers.h
    ImageProc/Helpers.cpp
    ImageProc/Exceptions.h
    ImageProc/Exceptions.cpp
    ImageProc/ImgAnalysis.cpp
    ImageProc/ImgAnalysis.h
	ImageProc/Histogram.cpp
	ImageProc/Histogram.h
	ImageProc/ImgCharacteristics.h
    ImageProc/ImgCharacteristics.cpp
    ImageProc/NonLinearFilter.h
    ImageProc/NonLinearFilter.cpp
    ImageProc/ExtractionDetails.cpp
    ImageProc/ExtractionDetails.h
	cli.hpp
	files.hpp
    )

add_library(ImageProc ${SOURCE_FILES})
find_package(Matplot++ REQUIRED)
if(Matplot++_FOUND )                                                     
  message("using system installed matplot")
  target_link_libraries(ImageProc PUBLIC Matplot++::matplot)
else()
  message("building matplotlib")  
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/matplotplusplus)
  target_link_libraries(ImageProc PUBLIC matplot)
ENDIF()

add_library(CLI
    CLI/InputParser.cpp
    CLI/InputParser.hpp)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/libs)

find_package(Matplot++ REQUIRED)

target_include_directories(ImageProc
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include the source directory
)


target_link_libraries(ImageProcApp PUBLIC ImageProc CLI )
