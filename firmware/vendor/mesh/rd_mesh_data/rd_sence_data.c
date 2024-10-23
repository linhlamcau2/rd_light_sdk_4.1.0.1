#include "rd_mesh_data.h"
#include "../rd_lib.h"

#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#include "../../common/scene.h"

#if  (NAME == SMT_121)
	uint16_t groupType 		= 0x0001;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == COB_122)
	uint16_t groupType 		= 0x002;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == DOWNLIGHT_TT_124)
	uint16_t groupType 		= 0x0004;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == PN_T_125)
	uint16_t groupType 		= 0x0005;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == PN_126)
	uint16_t groupType 		= 0x0006;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x15c0, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x0000};
#elif(NAME == OT_127)
	uint16_t groupType 		= 0x0007;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x15c0, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x0000};
#elif(NAME == GT_128)
	uint16_t groupType 		= 0x0008;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TL_12a)
	uint16_t groupType 		= 0x000a;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TT_12b)
	uint16_t groupType 		= 0x000b;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == LED_WIRE_CT)
	uint16_t groupType 		= 0x000d;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TUBE_12e)
	uint16_t groupType 		= 0x000e;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x0320, 0x0320, 0x0320};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x7fff};

//----------------------------------------------------------------------------------------

#elif(NAME == RLT03_12W_12026)
	uint16_t groupType 		= 0x001d;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TRL08_10W_12025)
	uint16_t groupType 		= 0x001c;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TRL08_20W_12024)
	uint16_t groupType 		= 0x001b;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT01_10W_12023)
	uint16_t groupType 		= 0x001a;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT02_20W_12022)
	uint16_t groupType 		= 0x0019;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT02_10W_12021)
	uint16_t groupType 		= 0x0018;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT03_06W_12020)
	uint16_t groupType 		= 0x0017;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#endif

static uint16_t rd_list_check_scene[50] = {0};
static uint8_t numSceen = 0;


//RD_EDIT: 1.THANH: SCEEN AUTO
u8 RD_mesh_cmd_sig_scene_set_ll(u16 scene_id, mesh_cb_fun_par_t *cb_par, u16 lightness, u16 tempLight)
{
    u8 st = SCENE_ST_SUCCESS;
    u16 op = cb_par->op;
    int save = 0;
    if((SCENE_STORE == op)||(SCENE_STORE_NOACK == op)){
		scene_data_t *p_exist = 0;
		scene_data_t *p_null = 0;

		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[cb_par->model_idx][i];
			if((0 == p_null) && (0 == p->id)){
				p_null = p; 	// the first empty
			}
			if(scene_id == p->id){
				p_exist = p;
				break;	// exist
			}
		}

		scene_data_t *p_save = 0;
		if(p_exist){
			p_save = p_exist;
		}else if(p_null){
			p_save = p_null;
		}

		if(p_save){
			save = 1;
			p_save->id = scene_id;
			p_save->lightness_s16 = get_level_from_lightness(lightness);
			#if LIGHT_TYPE_CT_EN
			p_save->temp_s16 = get_level_from_ctl_temp(tempLight, MIN_TEMP, MAX_TEMP);
			p_save->delta_uv_s16 = 0;
			p_save->ct_flag = ct_flag;
			#endif
			#if LIGHT_TYPE_HSL_EN
			p_save->hue_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_HSL_HUE);
			p_save->sat_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_HSL_SAT);
			#endif
			#if (LIGHT_TYPE_SEL == LIGHT_TYPE_XYL)
			p_save->x_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_XYL_X);
			p_save->y_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_XYL_Y);
			#endif
			#if MD_LIGHT_CONTROL_EN
			scene_get_lc_par(p_save, cb_par->model_idx);
			#endif
			CB_NL_PAR_NUM_2(p_nl_get_vendor_scene_data, scene_id, p_save->nl_data);
			scene_active_set(cb_par->model_idx, scene_id, 0);
		}else{
			st = SCENE_ST_REG_FULL;
		}
    }else{	// del
		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[cb_par->model_idx][i];
			if(scene_id == p->id){
				memset(p, 0, sizeof(scene_data_t));
				scene_proc_t *p_scene = &scene_proc[cb_par->model_idx];
				if(scene_id == p_scene->current_scene){
					p_scene->current_scene = 0;
				}

				if(scene_id == p_scene->target_scene){
					p_scene->target_scene = 0;
				}
				save = 1;
				break;	// exist
			}
		}
    }

    if(save){
		mesh_model_store(1, SIG_MD_SCENE_SETUP_S);
	}

    return st;
}

static void RD_GroupAuto(uint16_t groupID, mesh_cb_fun_par_t *cb_par, uint16_t OpGroup){
	mesh_cb_fun_par_t *cb_par_g = cb_par;
	cb_par_g->op = OpGroup;
	cb_par_g->op_rsp = CFG_MODEL_SUB_STATUS;
	cb_par_g->model_idx = 0;
	uint8_t parGroup[8] = {0};
	if(cb_par_g->adr_dst == 0xFFFF) cb_par_g->adr_dst = ele_adr_primary;

	for(int i=0; i< ELE_CNT; i++)
	{
		if(OpGroup == CFG_MODEL_SUB_ADD || OpGroup == CFG_MODEL_SUB_DEL){
			parGroup[0] = (cb_par_g->adr_dst+i) & 0xff ;
			parGroup[1] = (cb_par_g->adr_dst+i) >> 8 & 0xff;
			parGroup[2] = groupID & 0xff;
			parGroup[3] = groupID >>8 & 0xff;
			parGroup[4] = 0x00;
			parGroup[5] = 0x10;

			mesh_cmd_sig_cfg_model_sub_set(parGroup, 6, cb_par_g);
		}
		else if(OpGroup == CFG_MODEL_SUB_DEL_ALL){
			parGroup[0] = (cb_par_g->adr_dst+i) & 0xff ;
			parGroup[1] = (cb_par_g->adr_dst+i) >> 8 & 0xff;
			parGroup[2] = 0x00;
			parGroup[3] = 0x10;

			mesh_cmd_sig_cfg_model_sub_set(parGroup, 4, cb_par_g);
		}
	}
}

void RD_SceenAuto(uint16_t sceenID, mesh_cb_fun_par_t *cb_par, uint16_t OpSceen){
	mesh_cb_fun_par_t *cb_par_s = cb_par;
	cb_par_s->op = OpSceen;
	cb_par_s->op_rsp = STATUS_NONE;
	cb_par_s->model_idx = 0;
	if(cb_par_s->adr_dst == ALL_NODE) cb_par_s->adr_dst = ele_adr_primary;

	if(OpSceen == SCENE_STORE_NOACK){
		for(int i=0; i<6; i++){
			RD_mesh_cmd_sig_scene_set_ll(sceenID+i, cb_par_s, lightness[i], temp[i]);
		}
	}
	else if(OpSceen == SCENE_DEL_NOACK){
		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[0][i];
			if(p->id != 0){
				rd_list_check_scene[numSceen] = p->id;
				numSceen++;
			}
		}
		if(numSceen > 0){
			foreach(i,numSceen){
				RD_mesh_cmd_sig_scene_set_ll(rd_list_check_scene[i], cb_par_s, 0, 0);
				rd_list_check_scene[i] = 0;
			}
			numSceen = 0;
		}
	}
}


void RD_Handle_AutoCreateGr(u8 *par, uint16_t Gw_Add_Buff, mesh_cb_fun_par_t *cb_par)
{
	uint16_t id_group = 0x0000;
	uint16_t id_group_type = 0x0000;
	uint16_t id_scene = 0;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, par, 8, Gw_Add_Buff, 2);

	id_group = (par[2] | par[3]<<8);
	id_group_type = id_group + groupType;
	id_scene = (par[4] | par[5]<<8);

	RD_GroupAuto(id_group, cb_par, CFG_MODEL_SUB_ADD);
	RD_GroupAuto(id_group_type, cb_par, CFG_MODEL_SUB_ADD);
	RD_SceenAuto(id_scene, cb_par, SCENE_STORE_NOACK);

	uart_CSend("Auto create Group default \n");
//	RD_SwitchAc4Ch_BlinkSet(5, 100);
}

void RD_Handle_AutoDeleteGr(u8 *par, uint16_t Gw_Add_Buff, mesh_cb_fun_par_t *cb_par)
{
	uint16_t id_group = 0x0000;
	uint16_t id_group_type = 0x0000;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, par, 8, Gw_Add_Buff, 2);

	id_group = (par[2] | par[3]<<8);
	id_group_type = id_group + groupType;

	RD_GroupAuto(id_group, cb_par, CFG_MODEL_SUB_DEL);
	RD_GroupAuto(id_group_type, cb_par, CFG_MODEL_SUB_DEL);
	RD_SceenAuto(id_scene, cb_par, SCENE_DEL_NOACK);

	uart_CSend("Auto delete Group default\n");
//	RD_SwitchAc4Ch_BlinkSet(5, 100);
}


