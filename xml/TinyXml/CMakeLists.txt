cmake_minimum_required (VERSION 2.6)
project (TinyXml)

add_library(TinyXml tinystr.cpp  tinyxml.cpp  tinyxmlerror.cpp  tinyxmlparser.cpp  xmltest.cpp)
target_link_libraries(TinyXml TinyXml)

