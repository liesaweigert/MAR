//
// Created by Liesa  on 29/06/16.
//

#include "Atom.h"

Atom::Atom(){
    this->name = Default;
    this->diameter = 0;
    this->marker_code = 0;
}

//radius t
Atom::Atom(int marker_code) {
    this->marker_code = marker_code;

    switch (marker_code) {
        case 4648: {
            this->name = atom_name::Oxygen;
            this->diameter = 0.012;
            assign_color(1.0, 0.0, 0.0);
            break;
        }
        case 7236: {
            this->name = atom_name::Carbon;
            this->diameter = 0.014;
            assign_color(0.0, 0.0, 0.0);
            break;
        }
        case 1680: {
            this->name = atom_name::Nitrogen;
            this->diameter = 0.013;
            assign_color(0.0, 0.0, 0.5);
            break;
        }
        case 626: {
            this->name = atom_name::Hydrogen;
            this->diameter = 0.005;
            assign_color(1.0, 1.0, 1.0);
            break;
        }
        default: {
            this->name = atom_name::Default;
            this->diameter = 0;
            assign_color(0.0, 0.0, 0.0);
            break;
        }
    }
}

void Atom::render_atom() {
    glColor3f(color[0], color[1], color[2]);
    glutSolidSphere(this->diameter, 20, 20);
}

void Atom::assign_color(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}