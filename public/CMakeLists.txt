aux_source_directory(src PUBLIC_SRCS)
include_directories(include)

add_library(public ${PUBLIC_SRCS})
