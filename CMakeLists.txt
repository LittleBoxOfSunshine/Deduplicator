cmake_minimum_required (VERSION 2.6)
project (Deduplicator)

#Versioning
set (Deduplicator_VERSION_MAJOR 0)
set (Deduplicator_VERSION_MINOR 1)

#Include headers into the project
include_directories(include)

#Recursively include source files into the project
file(GLOB_RECURSE SOURCES "src/*.cpp")
 
# add the executable
add_executable(Deduplicator ${SOURCES})

#Installation location
install(TARGETS Deduplicator DESTINATION bin)