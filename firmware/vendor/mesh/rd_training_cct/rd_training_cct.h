#ifndef RD_TRAINING_CCT_H
#define RD_TRAINING_CCT_H

#include "../rd_type_dev/rd_type_dev.h"
#include "vendor/common/light.h"
#include "vendor/common/lighting_model.h"
#include "vendor/common/fast_provision_model.h"

#define ENABLE_TRAINING_1		0	//RD_EDIT: ENA OR DIS TRAINING


void Time_kickout();
void Process_Test2();
void Process_1();
void Process_2();
void Process_3();
void Process_4();
void Process_5();
void Process_6();
void Training_Run();
void Init_Training_1();

void RD_Flash_CleanTraining(void);
void RD_Flash_Training_Init(void);
u8 RD_get_flag_fac_mode();

#endif
