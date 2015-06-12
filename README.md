# Deduplicator
Simple tool to safely and efficiently remove duplicate files from a local filesystem

Requires boost::filesystem to build

Requires BMCA header-only library to build (https://github.com/Ranind/BMCA)

Compile with:
g++ *.cpp -std=c++11 -lboost_system -lboost_filesystem

