cmake_minimum_required(VERSION 2.8)

project(POKER)

include_directories(${POKER_SOURCE_DIR})

add_executable(	Poker
				cards.h
				cards.cpp)

add_executable(	PokerTest
				cards.h
				cards.cpp
				gtest/gtest-all.cc
				gtest/gtest.h
				gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -w -std=gnu++0x")
endif()

target_link_libraries(PokerTest -lgmp -lgmpxx -lpthread)