cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(Ra224_Glue)
# project(sim_alpha_project)

# Find Geant4 package
find_package(Geant4 REQUIRED ui_all vis_all)
# Include Geant4 directories
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})


# Gather sources and headers
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Copy macro and data files to the build directory
file(GLOB MACRO_FILES "${PROJECT_SOURCE_DIR}/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES "${PROJECT_SOURCE_DIR}/*.dat")
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Create the executable
add_executable(Ra224_Glue main.cc ${sources} ${headers})
# add_executable(sim_alpha_project main.cc ${sources} ${headers})


# Link Geant4 libraries
target_link_libraries(Ra224_Glue ${Geant4_LIBRARIES})
# target_link_libraries(sim_alpha_project ${Geant4_LIBRARIES})

# Add custom target
add_custom_target(Ra224_Glue_l DEPENDS Ra224_Glue)
# add_custom_target(sim_alpha_project_L DEPENDS sim_alpha_project)