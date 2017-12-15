#ifndef BRUTEFORCECOLLISION_H
#define BRUTEFORCECOLLISION_H

#include "MovRect.h"
#include "collision_simulation.h"

void bruteforcecollision(MovRect * recta, const int num_rects);
void bruteforcecollision(std::vector< MovRect * > & data);
void bruteforcecollision(std::vector< MovRect * > & data0, std::vector< MovRect * > & data1);

#endif
