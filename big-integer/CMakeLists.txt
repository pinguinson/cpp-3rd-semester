cmake_minimum_required(VERSION 2.8.4)
project(big_integer)

set(SOURCE_FILES
    main.cpp
    BigInteger.cpp
    exception.cpp
    )

set(HEADERS
    BigInteger.h
    )

add_executable(big_integer ${SOURCE_FILES})