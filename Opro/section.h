#ifndef __section
#define __section

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"
#include "sample133.h"
#include "MoveDistance.h"

typedef enum{
	SECTION_ONE_BEFORE_GRAY, 		/* system initialize mode */
	SECTION_ONE_ON_GRAY,
	SECTION_ONE_AFTER_GRAY,
} SECTION_INFO;

SECTION_INFO section_info;

MoveDistance moveDistance;
 
void section();


#endif