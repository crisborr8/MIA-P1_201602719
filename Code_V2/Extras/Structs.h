#ifndef STRUCTS_H
#define STRUCTS_H

#include <ctime>
#include <chrono>
#include <string.h>
#include <iostream>
using namespace std;

class Str{
    public:
        struct Particion;
        struct MBR;
        struct EBR;

        struct Files;
        struct Montura;

        struct Superbloque;
        struct Inodos;
        struct Journaling;
        struct Bloques_carpeta;
        struct Bloques_content;
        struct Bloques_archivo;
        struct Bloques_apuntad;
};

#endif