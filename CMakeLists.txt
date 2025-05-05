cmake_minimum_required(VERSION 3.10)
project(Carter VERSION 0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find external libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(Box2D REQUIRED)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE_DIR})

# Define source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(carter ${SOURCES})

# Link libraries
target_link_libraries(carter 
    ${SFML_LIBRARIES}
    ${BOX2D_LIBRARIES}
)

# Copy assets to build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})