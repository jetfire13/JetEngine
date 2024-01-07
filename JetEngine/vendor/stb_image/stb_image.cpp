#include "JEpch.h"


//!!!! Needs to be investigated
#if defined(__GNUC__) && !defined(NDEBUG) && defined(__OPTIMIZE__)
    #warning "Undefing __OPTIMIZE__ because of fmt"
    #undef __OPTIMIZE__
#endif


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"