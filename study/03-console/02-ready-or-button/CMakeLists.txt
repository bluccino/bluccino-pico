# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(02-ready-or-button)
add_definitions(-DPROJECT="${CMAKE_PROJECT_NAME}")

set (PICO ../../../include/zephyr)
include_directories(src ${PICO})
target_sources(app PRIVATE src/main.c ${PICO}/pico/pico.c)
