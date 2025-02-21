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
target_link_libraries(src imgui)