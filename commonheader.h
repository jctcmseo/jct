#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <iostream>

typedef struct{
    int     command_option;         //명령어 종류
    int     sub_option;             //더미

    float   joint[6];               //관절각도
    float   tcp[6];                 //tcp 값

    float   vel;
    float   acc;

    float   current;                //본전
    float   voltage;                //본전

    float   wait_time;

    float   arc_on_para[6];         //전류/전압/시간
    float   arc_off_para[6];        //전류/전압/시간

    float   wire_para[3];

    float   weaving_para[6];

    float   a_axis_para[6];

    int     lv;                     //0 : 미교시, 1: 교시중, 2: 교시완료

    float   w_persent;

    float xx;                       // x시프트
    float yy;                       // y시프트
    float zz;                       // z시프트

    int data_int_0;                 //spare
    int data_int_1;                 //spare
    int data_int_2;                 //spare
    int data_int_3;                 //spare
    int data_int_4;                 //spare
    int data_int_5;                 //spare
    int data_int_6;                 //spare
    int data_int_7;                 //spare
    int data_int_8;                 //spare
    int data_int_9;                 //spare

    float data_float_0;             //spare
    float data_float_1;             //spare
    float data_float_2;             //spare
    float data_float_3;             //spare
    float data_float_4;             //spare
    float data_float_5;             //spare
    float data_float_6;             //spare
    float data_float_7;             //spare
    float data_float_8;             //spare
    float data_float_9;             //spare
}ST_DATA;

typedef struct{
    float current;                  //0
    float voltage;                  //1
    float speed;                    //2
    float time;                     //3
    int weaving_number;             //4
    float weaving_amp;              //5
    float weaving_time;             //6
    float on_current;               //7
    float on_voltage;               //8
    float on_time;                  //9
    float off_current;              //10
    float off_voltage;              //11
    float off_time;                 //12
    int   wire;                     //13
    float   w_persent;                //14

    int memory_int_0;               //15
    int memory_int_1;               //16
    int memory_int_2;               //17
    int memory_int_3;               //18
    int memory_int_4;               //19
    int memory_int_5;               //20
    int memory_int_6;               //21
    int memory_int_7;               //22
    int memory_int_8;               //23
    int memory_int_9;               //24

    float memory_float_0;           //25
    float memory_float_1;           //26
    float memory_float_2;           //27
    float memory_float_3;           //28
    float memory_float_4;           //29
    float memory_float_5;           //30
    float memory_float_6;           //31
    float memory_float_7;           //32
    float memory_float_8;           //33
    float memory_float_9;           //34
}ST_MEMORY;

#define MAX_SHARED_DATA     145

typedef union{
    unsigned int raw;
    struct{
        unsigned PW_48V_IN_STAT : 1;
        unsigned PW_48V_OUT_STAT : 1;
        unsigned PW_24V_IN_STAT : 1;
        unsigned PW_EM_SW_STAT : 1;
        unsigned PW_PC_SW_STAT : 1;
        unsigned PW_MC_SW_STAT : 1;
        unsigned PW_IPO_STAT : 1;
        unsigned TOOL_BTN_STAT : 1;
        unsigned DUMMY : 22;
        unsigned FLAG_LOAD : 1;
        unsigned FLAG_TRANS : 1;
    };
}PW_DATA_STRUCTURE;

typedef union{
    struct{
        char    header[4];
        // 0
        float   time;
        float   jnt_ref[6];
        float   jnt_ang[6];
        float   cur[6];
        // 19
        float   tcp_ref[6];
        float   tcp_pos[6];
        // 31
        float   analog_in[4];
        float   analog_out[4];
        int     digital_in[16];
        int     digital_out[16];
        // 71
        float   temperature_mc[6];
        // 77
        int     task_pc;        // int
        int     task_repeat;    // int
        int     task_run_id;    // int
        int     task_run_num;   // int
        int     task_run_time;  // int
        int     task_state;//1 or 2 or 3
        // 83
        float   default_speed;
        int     robot_state; // 1 or 3 idle or not idle

        // power_state
        PW_DATA_STRUCTURE     power_state; // total bit combination

        // 86
        float   tcp_target[6];
        int     jnt_info[6];
        // 98
        int     collision_detect_onoff; // -1 or 0 or 1

        // is_freedrive_mode
        // 2 bit = is free drive
        int     is_freedrive_mode;// 0 or 1

        // program_mode
        // 4 bit = ref on off
        int     program_mode;// 0 or 1 ref on/off
        // 101
        int     init_state_info;
        int     init_error;
        // 103
        float   tfb_analog_in[2];
        int     tfb_digital_in[2];
        int     tfb_digital_out[2];
        float   tfb_voltage_out;
        // 110
        // op_stat_collision_occur
        // 2 bit = op_stat_collision_occur
        int     op_stat_collision_occur;
        int     op_stat_sos_flag;
        // op_stat_self_collision
        // 2 bit = op_stat_self_collision
        int     op_stat_self_collision;

        int     op_stat_soft_estop_occur;
        int     op_stat_ems_flag;
        // 115
        int  information_chunk_2;
        int  information_chunk_3;
        // 117
        int     inbox_trap_flag[2];
        int     inbox_check_mode[2];
        // 121
        float   eft_fx;
        float   eft_fy;
        float   eft_fz;
        float   eft_mx;
        float   eft_my;
        float   eft_mz;
        // 127
        int     information_chunk_4;
        // 128
        float   extend_io1_analog_in[4];
        float   extend_io1_analog_out[4];
        unsigned int extend_io1_digital_info;
        // 137
        float   aa_joint_ref[6];
        // 143
        unsigned int safety_board_stat_info;
        // 144
    }sdata;
    float fdata[MAX_SHARED_DATA];
    int idata[MAX_SHARED_DATA];
}systemSTAT;

#endif // COMMONHEADER_H
