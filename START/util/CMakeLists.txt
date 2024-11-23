cmake_minimum_required(VERSION 3.16)
project(util)

aux_source_directory(./ SRC)

add_library(util ${SRC})
