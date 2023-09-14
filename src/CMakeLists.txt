# ================= SOURCES =================
set(EXE_NAME "cpy")

set(SOURCES
    cpy.cpp
)
# ============================================

# ================= EXECUTABLE =================
add_executable(${EXE_NAME} ${SOURCES})
# ===============================================

# ================= INCLUDES =================
target_include_directories(${EXE_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)
# =============================================

# ================= LINKS =================
# target_link_libraries(${EXE_NAME} PUBLIC
# )
# =========================================
