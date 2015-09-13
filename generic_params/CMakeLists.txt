project( generic_parameters )
cmake_minimum_required( VERSION 2.8 )

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()


set( HEADER_LISTS
     ${HEADER_LISTS} )

set( SOURCE_FILES
     ${SOURCE_FILES}
     main.cpp )

add_subdirectory( data )
     
add_library( ${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_LISTS} )
#install headers     
     
