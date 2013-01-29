cmake_minimum_required ( VERSION 2.6 )
# Укажите здесь имя вашего проекта.
# Учитываете установку переменных 
# <project_name>_BINARY_DIR и  <project_name>_SOURCE_DIR
# в значение имени каталога с проектом.
set (PROJECT ProjectNULL)
project (${PROJECT})

# - имя исполняемого файла
set ( APP_NAME projectnull )
message(STATUS "App name: ${APP_NAME}")

# Управление типом сборки через задание значения
# предопределенной переменной CMAKE_BUILD_TYPE
# Возможные значения:
# DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL
# Задается при запуске Cmake параметром -DCMAKE_BUILD_TYPE:STRING=Release
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)


include_directories (${INCLUDE_DIR})
#link_directories (/path/to/lib_N)
file(GLOB HEADERS "${INCLUDE_DIR}/*.h")
file(GLOB SOURCES "${SRC_DIR}/*.cpp")


source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

if (MSVC)
	add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions (-Wall -pedantic -Wno-variadic-macros)
	# for Eclipse
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")

	set(CMAKE_VERBOSE_MAKEFILE ON)
else ()
	message(FATAL_ERROR "Error: Unknown compiler")
endif ()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON) 
find_package(Boost 1.40.0 REQUIRED COMPONENTS program_options system thread filesystem)
include_directories( ${Boost_INCLUDE_DIRS} )


add_executable (${APP_NAME} ${SOURCES})
# для создяние dll / so
#add_library (${PROJECT} SHARED ${HEADERS} ${SOURCES})

target_link_libraries(${APP_NAME} ${Boost_LIBRARIES})
target_link_libraries(${APP_NAME} rt)
target_link_libraries(${APP_NAME} pthread)

