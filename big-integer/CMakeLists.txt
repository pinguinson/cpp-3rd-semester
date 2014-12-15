cmake_minimum_required(VERSION 2.8)

project(BIGINTEGER)

include_directories(${BIGINTEGER_SOURCE_DIR})

add_executable(	BigInteger
				BigInteger.h
				BigInteger.cpp
				exception.cpp
				main.cpp)

add_executable(	BigIntegerTest
				BigIntegerTest.cpp
				BigInteger.h
				BigInteger.cpp
				exception.cpp
				main.cpp
				gtest/gtest-all.cc
				gtest/gtest.h)

target_link_libraries(BigIntegerTest -lgmp -lgmpxx -lpthread)