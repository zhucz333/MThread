﻿CMAKE_MINIMUM_REQUIRED (VERSION 3.5)

PROJECT (MThreadTest CXX)

SET(TARGETTEST MThreadTest)

FILE(GLOB_RECURSE MTHREADTEST_HEADERS *.h)
AUX_SOURCE_DIRECTORY(. MTHREADTEST_SRCS)

ADD_EXECUTABLE(${TARGETTEST} ${MTHREADTEST_HEADERS} ${MTHREADTEST_SRCS})

INCLUDE_DIRECTORIES(${INC_PATH})
LINK_DIRECTORIES(${LIB_PATH})
TARGET_LINK_LIBRARIES(${TARGETTEST} ${TARGETBIN})

SET_TARGET_PROPERTIES(${TARGETTEST} PROPERTIES OUTPUT_NAME "${TARGETTEST}${ARCH}$<$<CONFIG:Debug>:D>")

