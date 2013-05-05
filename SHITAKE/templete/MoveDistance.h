#ifndef __MoveDistance
#define __MoveDistance

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"


 /* Ô—Ö”¼ŒaA‘–s‘Ì•*/
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//Ô—Ö‚Ì‰~ü[cm]
#define CIRCUMFERENCE 25.8			//Ô—Ö‚Ì‰~ü


int MoveDistance_detect_move_distance();

void MoveDistance_create();	

//ˆÚ“®‹——£‚ğ•Ô‚·
int MoveDistance_detect_move_distance();



//‚±‚ÌƒNƒ‰ƒX‚©‚ç‚µ‚©ŒÄ‚Î‚ê‚È‚¢private‚ÈŠÖ”

//Œ»İ‚Ìƒ‚[ƒ^‰ñ“]Šp‚ğ•Û‘¶
static void MoveDistance_reset_move_distance_measurement();


#endif
