/*BlueToothでの通信用関数


*/

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h" /* 倒立振子制御用ヘッダファイル */
#include "logSend.h"

//static void logSend(S8 data1, S8 data2, S16 adc1, S16 adc2, S16 adc3, S16 adc4);

void logSend(S8 data1, S8 data2, S16 adc1, S16 adc2, S16 adc3, S16 adc4, S32 datas32, S32 datas32_2) {
	
	static S32 valOfDistance;
	
	
	static U8 data_log_buffer[32];
 
		//左辺は結局data_log_bufferの中身を表している。要するにただの代入
		//32ビット分アクセスするためにdata_log_bufferの[1]から[3]へはアクセスしてない。
			*((U32 *)(&data_log_buffer[0]))  = (U32)systick_get_ms();
//			*((U32 *)(&data_log_buffer[0]))  = (U32)datas32;
			*(( S8 *)(&data_log_buffer[4]))  =  (S8)data1;
            *(( S8 *)(&data_log_buffer[5]))  =  (S8)data2;
            *((U16 *)(&data_log_buffer[6]))  = (U16)ecrobot_get_light_sensor(NXT_PORT_S3); //light sensor value
            *((S32 *)(&data_log_buffer[8]))  = (S32)nxt_motor_get_count(0);
            *((S32 *)(&data_log_buffer[12])) = (S32)nxt_motor_get_count(1);
            *((S32 *)(&data_log_buffer[16])) = (S32)datas32;
            *((S16 *)(&data_log_buffer[20])) = (S16)adc1;
            *((S16 *)(&data_log_buffer[22])) = (S16)adc2;
            *((S16 *)(&data_log_buffer[24])) = (S16)adc3;
            *((S16 *)(&data_log_buffer[26])) = (S16)adc4;
			*((S32 *)(&data_log_buffer[28])) = (U32)datas32_2; 
         //*((S32 *)(&data_log_buffer[28])) = (S32)systick_get_ms(); // どこの値？
            
            ecrobot_send_bt_packet(data_log_buffer, 32);
	
	
	
}

