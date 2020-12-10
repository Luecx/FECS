cmake_minimum_required(VERSION 3.17)
project(Fenix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Fenix
        main.cpp
        src/linear_algebra/matrix/DenseMatrix.h
        src/linear_algebra/matrix/ListedMatrix.cpp
        src/linear_algebra/matrix/ListedMatrix.h
        src/linear_algebra/matrix/Matrix.h
        src/linear_algebra/matrix/Matrix3x3.cpp
        src/linear_algebra/matrix/Matrix3x3.h
        src/linear_algebra/matrix/SparseMatrix.cpp
        src/linear_algebra/matrix/SparseMatrix.h
        src/linear_algebra/vector/DenseVector.cpp
        src/linear_algebra/vector/DenseVector.h
        src/fem/elements/Node.h
        src/fem/elements/Node.cpp
        src/fem/elements/Element.h
        src/fem/elements/Element.cpp
        src/fem/system/System.cpp
        src/fem/system/System.h
        src/fem/reader/Reader.cpp
        src/fem/reader/Reader.h
        src/fem/reader/ReaderParseInit.cpp
        src/fem/reader/ReaderParseNodes.cpp
        src/fem/reader/ReaderParseElements.cpp
        src/fem/elements/Element_T2D2.h src/fem/reader/Errors.h src/fem/elements/Element_C2D3.h src/fem/boundary/Boundary.cpp src/fem/boundary/Boundary.h src/fem/step/Step.cpp src/fem/step/Step.h src/fem/step/StaticStep.cpp src/fem/step/StaticStep.h src/fem/boundary/Force.cpp src/fem/boundary/Force.h)