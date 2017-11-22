
cmake_minimum_required(VERSION 3.5)

project(fast_dct)

file(GLOB_RECURSE SOURCES "source/*")

add_executable( streamer
	${SOURCES}
)

target_include_directories(fast_dct PUBLIC source/ )

