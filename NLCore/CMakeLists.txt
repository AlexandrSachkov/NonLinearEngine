SET(HEADERS NLCore.h)
SET(SOURCES NLCore.cpp)

add_library (NLCore
  ${HEADERS}
  ${SOURCES}
)

install (TARGETS NLCore DESTINATION bin)
install (FILES ${HEADERS} DESTINATION include)