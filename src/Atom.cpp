//
// Created by Liesa  on 29/06/16.
//

#include "Atom.h"

Atom::Atom(){
    this->name = Default;
    this->diameter = 0;
    this->marker_code = 0;
}

Atom::Atom(int marker_code) {
    this->marker_code = marker_code;

    switch (marker_code) {
        case 4648: {
            this->name = atom_name::Oxigen;
            this->diameter = 0.02;
            assign_color(0.5, 0.5, 0.0);
            break;
        }
        case 7236: {
            this->name = atom_name::Chloride;
            this->diameter = 0.01;
            assign_color(0.8, 0.5, 0.8);
            break;
        }
        case 1680: {
            this->name = atom_name::Fluoride;
            this->diameter = 0.03;
            assign_color(0.5, 0.0, 0.3);
            break;
        }
        case 626: {
            this->name = atom_name::Hydrogen;
            this->diameter = 0.06;
            assign_color(0.0, 0.5, 0.9);
            break;
        }
        case 90: {
            this->name = atom_name::Neon;
            this->diameter = 0.02;
            assign_color(0.5, 1.0, 0.9);
            break;
        }
        case 2884: {
            this->name = atom_name::Stuff;
            this->diameter = 0.04;
            assign_color(0.5, 0.5, 1.0);
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
    drawSphere(this->diameter, 10, 10);
}

void Atom::assign_color(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}