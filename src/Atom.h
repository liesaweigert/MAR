//
// Created by Liesa  on 29/06/16.
//

#ifndef MAR_ATOM_H
#define MAR_ATOM_H


#include <Eigen/Dense>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>

enum atom_name{
    Hydrogen,
    Carbon,
    Nitrogen,
    Oxygen,
    Chlorine,
    Sodium,
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
    void render_bond(Eigen::Matrix4f from, Eigen::Matrix4f to);

private:
    void assign_color(float r, float g, float b);
};


#endif //MAR_ATOM_H
