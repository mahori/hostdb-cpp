# C++

enable_language(CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost C++ Libraries

find_package(Boost REQUIRED COMPONENTS program_options)

# MongoDB C++ Driver

find_package(mongocxx REQUIRED)

# executable

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} Boost::program_options)
target_link_libraries(${PROJECT_NAME} mongo::mongocxx_shared)

# install

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION $ENV{HOME}/bin)
