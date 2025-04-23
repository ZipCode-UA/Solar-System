set(Sources
        # Sources
        "CelestialBody.cpp"
        "Input.cpp"
        "Simulation.cpp"
        "main.cpp"
        "SolarSystem.cpp"
        "UI.cpp"
        "Window.cpp"
        #".cpp"
)

set(Dirs
        "../include"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})
