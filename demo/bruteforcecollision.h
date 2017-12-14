#ifndef BRUTEFORCECOLLISION_H
#define BRUTEFORCECOLLISION_H

#include "MovRect.h"
#include "test0.h"

void bruteforcecollision(MovRect * recta, const int num_rects);
void bruteforcecollision(std::vector< MovRect * > & data);

#endif
