CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(wsics)

IF (WIN32)
	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}\ /std:c++latest)
ELSE()
	SET(CMAKE_CXX_STANDARD 17)
ENDIF()

add_compile_definitions(OPENCV_TRAITS_ENABLE_DEPRECATED BOOST_ALL_DYN_LINK)

SET(GROUP_BLOB_OPERATIONS
	WSICS/BLOB_Operations/BLOB.h
	WSICS/BLOB_Operations/BLOB_Operations.h
	WSICS/BLOB_Operations/BLOB_Window.h
	WSICS/BLOB_Operations/BLOB.cpp
	WSICS/BLOB_Operations/BLOB_Operations.cpp
	WSICS/BLOB_Operations/BLOB_Window.cpp
)
SET(GROUP_HE_STAINING
	WSICS/HE_Staining/HE_Classifier.h
	WSICS/HE_Staining/MaskGeneration.h
	WSICS/HE_Staining/HE_Classifier.cpp
	WSICS/HE_Staining/MaskGeneration.cpp
)
SET(GROUP_HOUGH_TRANSFORM
	WSICS/HoughTransform/AveragedEllipseParameters.h
	WSICS/HoughTransform/Ellipse.h
	WSICS/HoughTransform/IAccumulator.h
	WSICS/HoughTransform/Line.h
	WSICS/HoughTransform/LocationCell.h
	WSICS/HoughTransform/PointCollection.h
	WSICS/HoughTransform/RandomizedHoughTransform.h
	WSICS/HoughTransform/TreeAccumulator.h
	WSICS/HoughTransform/WindowedTripletDetector.h
	WSICS/HoughTransform/AveragedEllipseParameters.cpp
	WSICS/HoughTransform/Ellipse.cpp
	WSICS/HoughTransform/Line.cpp
	WSICS/HoughTransform/LocationCell.cpp
	WSICS/HoughTransform/PointCollection.cpp
	WSICS/HoughTransform/RandomizedHoughTransform.cpp
	WSICS/HoughTransform/TreeAccumulator.cpp
	WSICS/HoughTransform/WindowedTripletDetector.cpp
)
SET(GROUP_HSD
	WSICS/HSD/BackgroundMask.h
	WSICS/HSD/HSD_Model.h
	WSICS/HSD/Transformations.h
	WSICS/HSD/BackgroundMask.cpp
	WSICS/HSD/HSD_Model.cpp
	WSICS/HSD/Transformations.cpp
)
SET(GROUP_IO
	WSICS/IO/CommandLineInterface.h
	WSICS/IO/Logging/LogHandler.h
	WSICS/IO/Logging/LogLevel.h
	WSICS/IO/CommandLineInterface.cpp
	WSICS/IO/Logging/LogHandler.cpp
	WSICS/IO/Logging/LogLevel.cpp
)
SET(GROUP_MISC 
	WSICS/Misc/LevelReading.h
	WSICS/Misc/MT_Singleton.hpp
	WSICS/Misc/Random.h
	WSICS/Misc/MatrixOperations.h
	WSICS/Misc/LevelReading.cpp
	WSICS/Misc/Random.cpp
	WSICS/Misc/MatrixOperations.cpp
)
SET(GROUP_ML
	WSICS/ML/NaiveBayesClassifier.h
	WSICS/ML/NaiveBayesFeatureClassifier.h
	WSICS/ML/NaiveBayesClassifier.cpp
	WSICS/ML/NaiveBayesFeatureClassifier.cpp
)
SET(GROUP_NORMALIZATION
	WSICS/Normalization/CxCyWeights.h
	WSICS/Normalization/NormalizedLutCreation.h
	WSICS/Normalization/NormalizedOutput.h
	WSICS/Normalization/PixelClassificationHE.h
	WSICS/Normalization/CLI.h
	WSICS/Normalization/WSICS_Algorithm.h
	WSICS/Normalization/WSICS_Parameters.h
	WSICS/Normalization/TransformCxCyDensity.h
	WSICS/Normalization/CxCyWeights.cpp
	WSICS/Normalization/NormalizedLutCreation.cpp
	WSICS/Normalization/NormalizedOutput.cpp
	WSICS/Normalization/PixelClassificationHE.cpp
	WSICS/Normalization/CLI.cpp
	WSICS/Normalization/WSICS_Algorithm.cpp
	WSICS/Normalization/TransformCxCyDensity.cpp
)

ADD_EXECUTABLE(wsics
	WSICS/Main.cpp
	${GROUP_BLOB_OPERATIONS}
	${GROUP_HE_STAINING}
	${GROUP_HOUGH_TRANSFORM}
	${GROUP_HSD}
	${GROUP_IO}
	${GROUP_MISC}
	${GROUP_ML}
	${GROUP_NORMALIZATION}
)

SOURCE_GROUP("BLOB_Operations"	FILES ${GROUP_BLOB_OPERATIONS})
SOURCE_GROUP("HE_Staining"		FILES ${GROUP_HE_STAINING})
SOURCE_GROUP("HoughTransform"	FILES ${GROUP_HOUGH_TRANSFORM})
SOURCE_GROUP("HSD" 				FILES ${GROUP_HSD})
SOURCE_GROUP("IO"				FILES ${GROUP_IO})
SOURCE_GROUP("Misc"				FILES ${GROUP_MISC})
SOURCE_GROUP("ML"		FILES ${GROUP_ML})
SOURCE_GROUP("Normalization"	FILES ${GROUP_NORMALIZATION})


find_package(Threads REQUIRED)

FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem program_options system)
IF(Boost_FOUND)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF()

FIND_PACKAGE(OpenCV REQUIRED)
IF(OpenCV_FOUND)
	INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
	LINK_DIRECTORIES(${OpenCV_LIBRARY_DIRS})
ENDIF()

SET(ASAP_INCLUDE_DIRS "ASAP_INCLUDE_DIRECTORY" CACHE FILEPATH "The path to the ASAP include directory.")
SET(ASAP_LIB_DIRS "ASAP_LIB_DIRECTORY" CACHE FILEPATH "The path to the ASAP library directory.")
	INCLUDE_DIRECTORIES(${ASAP_INCLUDE_DIRS})
	LINK_DIRECTORIES(${ASAP_LIB_DIRS})
IF (WIN32)
	SET(ASAP_LIBRARIES ${ASAP_LIB_DIRS}/core.lib ${ASAP_LIB_DIRS}/multiresolutionimageinterface.lib)
ELSE()
	SET(ASAP_LIBRARIES ${ASAP_LIB_DIRS}/libcore.so ${ASAP_LIB_DIRS}/libmultiresolutionimageinterface.so)
ENDIF()


TARGET_LINK_LIBRARIES(wsics ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} ${ASAP_LIBRARIES} Threads::Threads)

install(TARGETS wsics DESTINATION bin)