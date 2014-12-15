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
				gtest/gtest-all.cc
				gtest/gtest.h
				gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -w -std=gnu++0x")
endif()

target_link_libraries(BigIntegerTest -lgmp -lgmpxx -lpthread)