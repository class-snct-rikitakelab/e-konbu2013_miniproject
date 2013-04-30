#ifndef __MoveDistance
#define __MoveDistance



 /* Ô—Ö”¼ŒaA‘–s‘Ì•*/
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//Ô—Ö‚Ì‰~ü[cm]
#define CIRCUMFERENCE 25.8			//Ô—Ö‚Ì‰~ü



//ˆÚ“®‹——£ƒNƒ‰ƒX

typedef struct {
	
float target_move_distance;

}MoveDistance;

int detect_move_distance();

void MoveDistance_init(MoveDistance *this_MoveDistance);	
void MoveDistance_set_target_distance(MoveDistance *this_MoveDistance,float target_distance);
int MoveDistance_detect_move_distance(MoveDistance *this_MoveDistance);

#endif
