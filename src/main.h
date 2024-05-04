#pragma once
#ifdef _WIN32
 #define RAYGUI_IMPLEMENTATION
   
#endif
#ifdef __linux__
 #define RAYGUI_IMPLEMENTATION
#endif 

enum screen{
    MAINSCREEN,
    ALGORITHM_LIST,
    DATASTRUCTURE_LIST,
    LINEARSEARCH,
    ARRAY_VISUALIZER,
    QUEUE_VISUALIZER,
};

