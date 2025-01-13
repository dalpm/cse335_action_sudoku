project(GameLib)

set(SOURCE_FILES)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        Sparty.cpp
        Sparty.h
        Container.cpp
        Container.h
        XRay.cpp
        XRay.h
        Digit.cpp
        Digit.h
        Sudoku.cpp
        Sudoku.h
        Scoreboard.cpp
        Scoreboard.h
        ids.h
        ImageManager.cpp
        ImageManager.h
        Level.cpp
        Level.h
        Given.cpp
        Given.h
        Background.cpp
        Background.h
        ItemVisitor.cpp
        ItemVisitor.h
        VisitContainer.cpp
        VisitContainer.h
        SpartyFinder.cpp
        SpartyFinder.h
        XRayFinder.cpp
        XRayFinder.h
        VisitDigit.cpp
        VisitGiven.cpp
        VisitGiven.h
        Banner.h
        Banner.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})