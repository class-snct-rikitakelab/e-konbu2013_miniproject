#ifndef __MoveDistance
#define __MoveDistance

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"


 /* 車輪半径、走行体幅*/
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//車輪の円周[cm]
#define CIRCUMFERENCE 25.8			//車輪の円周


int MoveDistance_detect_move_distance();

void MoveDistance_create();	

//移動距離を返す
int MoveDistance_detect_move_distance();



//このクラスからしか呼ばれないprivateな関数

//現在のモータ回転角を保存
static void MoveDistance_reset_move_distance_measurement();


#endif
