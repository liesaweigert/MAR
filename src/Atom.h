//
// Created by Liesa  on 29/06/16.
//

#ifndef MAR_ATOM_H
#define MAR_ATOM_H


#include <Eigen/Dense>
#include <GLFW/glfw3.h>
#include "DrawPrimitives.h"

enum atom_name{
    Hydrogen,
    Oxigen,
    Chloride,
    Neon,
    Fluoride,
    Stuff,
    Default
};

class Atom {
    int marker_code;
    float diameter;
    atom_name name;
    GLfloat color[3];
public:
    Atom();
    Atom(int marker_code);
    void render_atom();

private:
    void assign_color(float r, float g, float b);
};


#endif //MAR_ATOM_H
