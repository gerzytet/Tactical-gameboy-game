#ifndef PALLETES_H
#define PALLETES_H

#include <gb/gb.h>
#include <gb/cgb.h>

const uint16_t colors[32] = {
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0), 
    RGB(31, 31, 31), RGB(7, 23, 8), RGB(4, 14, 6), RGB(19, 13, 0), 
    RGB(31, 31, 31), RGB(0, 0, 0), RGB(25, 25, 0), RGB(10, 7, 1), 
    RGB(31, 31, 31), RGB(15, 15, 5), RGB(13, 10, 1), RGB(5, 5, 5), 
    RGB(31, 31, 31), RGB(18, 12, 5), RGB(10, 7, 1), RGB(0, 0, 0), 
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(31, 7, 3), RGB(0, 0, 0), 
    RGB(28, 29, 5), RGB(7, 23, 8), RGB(4, 14, 6), RGB(0, 7, 5), 
    RGB(28, 29, 5), RGB(7, 23, 8), RGB(4, 14, 6), RGB(0, 7, 5), 
};

//greyscale, blue, red, green
const uint16_t colors_objects[32] = {
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0), 
    RGB(31, 31, 31), RGB(12, 18, 21), RGB(0, 10, 18), RGB(0, 6, 13), 
    RGB(31, 31, 31), RGB(31, 18, 18), RGB(31, 13, 13), RGB(20, 0, 0), 
    RGB(31, 31, 31), RGB(25, 28, 15), RGB(20, 23, 5), RGB(15, 19, 1), 
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0),
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0),
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0),
    RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0),
};

#endif