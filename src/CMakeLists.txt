set(Sources
        # Sources
        "CelestialBody.cpp"
        "main.cpp"
        "SolarSystem.cpp"
        "Window.cpp"
        #".cpp"
)

set(Dirs
        "../include"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})
