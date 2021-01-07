SOURCES       += main.cpp ../program/Markov_chain.cpp
HEADERS       = ../program/Markov_chain.h
QT           += testlib
QMAKE_CXXFLAGS += /std:c++17
windows:TARGET  = ../tests
