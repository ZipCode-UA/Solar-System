set(Sources
        # Sources
        "MilkyWay.cpp"
        "SolarSystem.cpp"
        #".cpp"
)

set(Dirs
        "../include"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(src OpenGL::GL)