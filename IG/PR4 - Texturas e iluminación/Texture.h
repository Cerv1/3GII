#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
// #include "jpg_imagen.hpp"
// #include "jpg_jinclude.h"

#ifndef _TEXTURE_H
#define _TEXTURE_H

class Texture {
    private:
        // jpg::Imagen * pimg;
        unsigned int tamx;
        unsigned int tamy;
        unsigned char * texels;
        unsigned int id;
        bool automatico;
    public:
        Texture(const char *file_name);
        void activar();
        void disable();
};

#endif
