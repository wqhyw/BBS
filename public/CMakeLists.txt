include_directories(include)

aux_source_directory(src PUBLIC_SRCS)

# public.o
add_library(public ${PUBLIC_SRCS})
