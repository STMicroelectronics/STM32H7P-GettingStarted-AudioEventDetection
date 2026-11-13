
# CMakeLists.txt for aed model

# AI sources
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/stai_network.c
    ${CMAKE_CURRENT_LIST_DIR}/network_sysmem.eFlash2.c
    ${CMAKE_CURRENT_LIST_DIR}/network_sysmem.eFlash1.c
    ${CMAKE_CURRENT_LIST_DIR}/network.c
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

# Add compile definitions, equivalent to "-D"
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
)





