set(Includes
        # Headers
        "CelestialBody.h"
        "Input.h"
        "Simulation.h"
        "SolarSystem.h"
        "UI.h"
        "Window.h"
        #".h"
)

add_library(include INTERFACE ${Includes})
