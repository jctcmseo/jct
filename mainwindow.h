#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTimer>
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QScrollBar>
#include <QRect>
#include <QHostInfo>
#include <stdlib.h>
#include <windows.h>
#include <lmcons.h>
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <qdir>

#include <QtWidgets>                // FTP 때문에 추가
#include <QNetworkAccessManager>    // FTP 때문에 추가
#include <QNetworkReply>            // FTP 때문에 추가
#include <QNetworkRequest>          // FTP 때문에 추가

#include <stdio.h>
#include <iostream>

#include "commonheader.h"

//#define     WILL_USE_AUTO_UI_ON

#define     VALUE_ARC_WAIT_TIME         5

#define     MSG_JCT_TITLE                   "JCT WelSystem"
#define     MSG_NO_CONNECTION               "통신이 연결되지 않았습니다 ... !!!"
#define     MSG_TIMEOUT_FILE_TRANSFER       "프로그램 전송 시간 초과 ... !!!"
#define     MSG_TIMEOUT_LOAD                "프로그램 로드 시간 초과 ... !!!"
#define     MSG_TIMEOUT_CHECK_RUN           "프로그램 재생 시간 초과 ... !!!"
#define     MSG_OTHER_PROGRAM_IS_RUN        "아직 다른 프로그램이 재생 중 입니다 ... !!!"
#define     MSG_UN_TEACHED_INFORMATION      "교시되지 않은 지점이 존재합니다 ...!!!"
#define     MSG_WELDING_DATA_SIZE_SMALL     "불완전한 데이터는 저장 불가능 합니다 ...!!!"
#define     MSG_WELDING_DATA_SIZE_SMALL2    "불완전한 데이터로 생성 및 재생 불가능 합니다 ...!!!"
#define     MSG_WRONG_PROGRAM_LINE_NUMBER   "실행 불가능한 프로그램 라인 번호 입니다 ... !!!"

#define     DIN_PORT_EMG                4
#define     DIN_PORT_TEACHING_DONE      6
#define     DIN_PORT_TEACHING_BACK      5
#define     DIN_PORT_SIGNAL_WAIT        2
#define     DOUT_PORT_TIG_WELDER        11
#define     DOUT_PORT_GIVE_ME_SIGNAL    0

enum WELSYS_COMMNAND_TYPE{
    WEL_CMD_NONE = 0,
    WEL_CMD_WAIT_TIME,//대기 시간
    WEL_CMD_WAIT_DIN,//대기 신호
    WEL_CMD_MOVE_L,//이동 직선
    WEL_CMD_MOVE_J,//이동 자유
    WEL_CMD_MOVE_PRO_L,//용접 직선
    WEL_CMD_MOVE_PRO_C,//용접 곡선
    WEL_CMD_MOVE_PRO_C_CONVERT,//전환 (command_data용)
    WEL_CMD_GAJUB,//가접
    WEL_CMD_WEAVING_L,//위빙
    WEL_CMD_WEAVING_L_REF_1,
    WEL_CMD_WEAVING_L_REF_2,
    WEL_CMD_INIT_J,//초기 이동 J
    WEL_CMD_INIT_L,//초기 이동 L
    WEL_CMD_FINAL_L,//최종 이동 L
    WEL_CMD_FINAL_J,//최종 이동 J
    WEL_CMD_ONEPOINT_WELD,//용접 부가축 + MOV L
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer              commandtimer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    systemSTAT   sys_status;
    void getuser();

    void rb_soket_on();

    void SetTableFormat();

    void Update_TW_1();

    void Update_TW_1_command_data();

    void Update_TW_10();

    void Update_TW_10_welding_data();

    void Update_modify_data();

    void                RBFTP_Transfer(void);                   // FTP 때문에 추가
    void                Real_List_Add(int insert_point);        // FTP 때문에 추가

    QVector<ST_DATA>    command_data;
    QVector<ST_DATA>    welding_data;
    QVector<ST_DATA>    modify_command_data;
    QVector<ST_DATA>    modify_welding_data;

    int                 is_first_check;
    int                 is_first_count;
    int                 real_simul_count;
    int                 booting_check;
    int                 TLR_step;
    unsigned int        TLR_time_out_count;
    int                 old_TRANSMIT_FLAG;
    int                 old_LOAD_FLAG;

    float               setting_air_move_J_vel;
    float               setting_air_move_J_acc;
    float               setting_air_move_L_vel;
    float               setting_air_move_L_acc;
    int                 setting_pc_ip_address[4];
    int                 setting_rb_ip_address[4];
    int                 setting_is_tig_welder;
    int                 setting_is_axis7;
    int                 setting_is_axis8;
    int                 setting_is_axis9;
    int                 setting_is_sound;
    int                 setting_is_wire;
    int                 setting_is_foot;
    int                 setting_is_robotfree;
    int                 setting_is_weld_play;
    int                 setting_arc_retry_vel;
    float               setting_arc_retry_time;
    float               setting_air_Axis_0_vel;
    float               setting_air_Axis_0_acc;
    float               setting_air_Axis_1_vel;
    float               setting_air_Axis_1_acc;
    float               setting_air_Axis_2_vel;
    float               setting_air_Axis_2_acc;
    int                 setting_memory_data[6];

    int                 setting_is_weld_type;

    float               home_axis0;
    float               home_axis1;
    float               home_axis2;
    float               home_axis3;
    float               home_axis4;
    float               home_axis5;
    float               home_axis6;
    float               home_axis7;
    float               home_axis8;
    float               home_axis9;


    void                Setting_Speed_And_IP_Load(void);
    void                Setting_Speed_And_IP_Save(void);

    void                Setting_Memory_Load(void);
    void                Setting_Memory_Save(void);

    void                Handler_Trans_Load_Run(void);
    void                Handler_IO(void);

    void                Script_Maker(QString work_name, unsigned int start_index);

    QString             Script_Wait_Time(float TIME);
    QString             Script_Wait_Digital_Input(int port_num);
    QString             Script_SpeedBar(int percentage);
    QString             Script_Digital_Out(int portnum, int high_low);

    QString             Script_Move_J(float J0, float J1, float J2, float J3, float J4, float J5, float VEL, float ACC);
    QString             Script_Move_L(float X, float Y, float Z, float RX, float RY, float RZ, float VEL, float ACC);

    QString             Script_Move_PRO_Clear(void);
    QString             Script_Move_PRO_Add(float X, float Y, float Z, float RX, float RY, float RZ, float VEL, int OPTION, float OPTION_PARA);
    QString             Script_Move_PRO_Run(float ACC, int OPTION_ORIENTATION);
    QString             Script_Move_PRO_Add_Script(QString my_script);
    QString             Script_JCT_Set(float weld_A, int weld_V_option, float weld_V, float tig_wire_speed, int w_persent);
    QString             Script_action_dout(int val);
    QString             Script_JCT_TIG_WIRE(float vel);

    QString             Script_Thread(void);
    QString             Script_Post_Program(void);

    QString             Script_Arc_On(float time_init, float vel, float acc, float weld_A, int weld_V_option, float weld_V, float time_wait, float time_end, int option1, int option2, int option_blind_wait);
    QString             Script_Arc_Off(float time_init, float weld_A, int weld_V_option, float weld_V, float time_wait, float time_end);
    QString             Script_Arc_Set(float vel, float acc, float weld_A, int weld_V_option, float weld_V);

    QString             Script_Weaving(int type, float L1, float L2, float V1, float V2, float T1, float T2, float T3, float T4, float bend, float offset, float scale, float set1x, float set1y, float set1z, float set1rx, float set1ry, float set1rz, float set2x, float set2y, float set2z, float set2rx, float set2ry, float set2rz, float swing);
    QString             Script_move_waypoint(int type,int pointtype,float robot_vel, float robot_acc, float axis_vel, float axis_acc,float J0, float J1, float J2, float J3, float J4, float J5,float X, float Y, float Z, float RX, float RY, float RZ,float Axis7,float Axis8,float Axis9);
    QString             Script_aux_motor_move_multi(int use_a0,int use_a1,int use_a2,int use_a3,int use_a4,int use_a5,float a0_pos,float a1_pos,float a2_pos,float a3_pos,float a4_pos,float a5_pos,float a0_vel,float a1_vel,float a2_vel,float a3_vel,float a4_vel,float a5_vel,float a0_acc,float a1_acc,float a2_acc,float a3_acc,float a4_acc,float a5_acc,int finish);
    QString             Script_rb_xyz_value_shift(float xx,float yy, float zz);

    QString             Script_tcp_Weave_motion(int weavingtype, int TorchAxis, int Tilt, int Rotation, int Distortion, float L1, float L2, float V1, float V2, float T1, float T2, float T3, float T4, float scale, float offset, float bend, float swing, int plane, int Dragrate);

    // Cobot Control API -------------------
    // <CobotInit>
    // : initialize Cobot
    void CobotInit();

    // <MoveJoint>
    // : move to target posture in joint coordinate
    // joint1~joint6 : target joint angle in deg unit
    // spd : speed parameter (0~1: user define   or   -1: default setting)
    // acc : acceleration parameter (0~1: user define   or   -1: default setting)
    void MoveJoint(float joint1, float joint2, float joint3, float joint4, float joint5, float joint6, float spd = -1, float acc = -1);

    // <MoveTCP>
    // : move to target posture in cartesian coordinate
    // x, y, z : target TCP(tool center point) position in mm unit
    // rx, ry, rz : target TCP orientation (Yaw-Pitch-Roll Euler angle) in degree unit
    // spd : speed parameter (0~1: user define   or   -1: default setting)
    // acc : acceleration parameter (0~1: user define   or   -1: default setting)
    void MoveTCP(float x, float y, float z, float rx, float ry, float rz, float spd = -1, float acc = -1);

    // <MoveCircle_ThreePoint>
    // : move current position to final position while it follows circle trajectory
    // : the circle trajectory is derived from current, first, and final position
    // type : 0 - try to follow both input position and orientation
    //        1 - orientation will be fixed to current orientation
    //        2 - orientation will be changed perpendicularly starting from current orientation
    // x1, y1, z1 : first position in mm unit
    // rx1, ry1, rz1 : first orientation (Yaw-Pitch-Roll Euler angle) in degree unit
    // x2, y2, z2 : final position in mm unit
    // rx2, ry2, rz2 : final orientation (Yaw-Pitch-Roll Euler angle) in degree unit
    // spd : speed parameter (0~1: user define   or   -1: default setting)
    // acc : acceleration parameter (0~1: user define   or   -1: default setting)
    void MoveCircle_ThreePoint(int type, float x1, float y1, float z1, float rx1, float ry1, float rz1, float x2, float y2, float z2, float rx2, float ry2, float rz2, float spd = -1, float acc = -1);

    // <MoveCircle_Axis>
    // : move current position to final position while it follows circle trajectory
    // : the circle trajectory is derived from current position, center position, axis, and rotation angle
    // type : 0 - try to follow both input position and orientation
    //        1 - orientation will be fixed to current orientation
    //        2 - orientation will be changed perpendicularly starting from current orientation
    // cx, cy, cz : center position in mm unit
    // ax, ay, az : axis representation (norminal)
    // rot_angle: rotation angle in degree unit
    // spd : speed parameter (0~1: user define   or   -1: default setting)
    // acc : acceleration parameter (0~1: user define   or   -1: default setting)
    void MoveCircle_Axis(int type, float cx, float cy, float cz, float ax, float ay, float az, float rot_angle, float spd, float acc);

    // <MoveJointBlend_Clear>
    // : clear joint blend list
    void MoveJointBlend_Clear();

    // <MoveJointBlend_AddPoint>
    // : add point to the joint blend list
    // : only the last point's 'vel' and 'acc' will be applied
    // joint1~joint6 : target joint angle in deg unit
    // spd : speed parameter (0~1: user define   or   -1: default setting)
    // acc : acceleration parameter (0~1: user define   or   -1: default setting)
    void MoveJointBlend_AddPoint(float joint1, float joint2, float joint3, float joint4, float joint5, float joint6, float spd = -1, float acc = -1);

    // <MoveJointBlend_MovePoint>
    // : start to move all the points in the joint blend list
    void MoveJointBlend_MovePoint();

    // <MoveTCPBlend_Clear>
    // : clear TCP blend list
    void MoveTCPBlend_Clear();

    // <MoveTCPBlend_AddPoint>
    // : add point to the TCP blend list
    // : only the last point's 'vel' and 'acc' will be applied
    // radius : blend distance in mm unit
    // x, y, z : target TCP(tool center point) position in mm unit
    // rx, ry, rz : target TCP orientation (Yaw-Pitch-Roll Euler angle) in degree unit
    // spd : speed parameter (0~1: user define   or   -1: default setting)
    // acc : acceleration parameter (0~1: user define   or   -1: default setting)
    void MoveTCPBlend_AddPoint(float radius, float x, float y, float z, float rx, float ry, float rz, float spd = -1, float acc = -1);

    // <MoveTCPBlend_MovePoint>
    // : start to move all the points in the joint blend list
    void MoveTCPBlend_MovePoint();

    // <ControlBoxDigitalOut>
    // control digital out ports in control box
    // d0~d15 : digital out value (0 or 1)
    void ControlBoxDigitalOut(int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, int d9, int d10, int d11, int d12, int d13, int d14, int d15);

    // <ControlBoxAnalogOut>
    // control analog out ports in control box
    // a0~a3 : analog out value in voltage unit (0~10)
    void ControlBoxAnalogOut(float a0, float a1, float a2, float a3);

    // <ToolOut>
    // control digital out ports and voltage level in tool flange board
    // volt : reference voltage of tool flange board in voltage unit(0, 12, 24)
    // d0, d1 : digital out value (0 or 1)
    void ToolOut(int volt, int d0, int d1);

    // <ProgramMode_Real>
    // change to 'real robot' mode -- robot will move
    void ProgramMode_Real();

    // <ProgramMode_Simulation>
    // change to 'simulation' mode -- robot will not move except teaching
    void ProgramMode_Simulation();

    // <MotionPause>
    // pause the current motion
    void MotionPause();

    // <MotionHalt>
    // halt the current motion
    // !! CAUTION : user would better escape the motion sequence
    //            : if not, the next motion will be activated immediately
    void MotionHalt();

    // <MotionResume>
    // resume the paused motion
    void MotionResume();

    // <CollisionResume>
    // resume the motion which is paused due to external collision
    void CollisionResume();
    // -------------------------------------




    int IsMotionIdle();
    // Socket Part =====================================
#define FOLD_START___SOCKET_PART  {
public slots:
    // Command Socket---
    void onConnectedCmd();
    void onDisconnectedCmd();
    void onReadyReadCmd();
    // Data Socket---
    void onConnectedData();
    void onDisconnectedData();
    void onReadyReadData();
    // Connection Timer
    void onConnectionTimer();

private:
    QTimer  sockConnectionTimer;
    // Socket---
    QTcpSocket  sockCmd;
    QTcpSocket  sockData;
    bool    sockConnectionStatusCmd;
    bool    sockConnectionStatusData;
    // Data Read---
    QByteArray  recvBuf;
    int cmdConfirmFlag;
    int moveCmdFlag;
    int moveCmdCnt;
    unsigned int popup_timer;
#define FOLD_END___SOCKET_PART    }
// =================================================
public slots:
    void Loop_Command();

private slots:
    void BaseSpeedChange(float spd);

    void RBFTP_replyFinished(QNetworkReply*);

    void RBFTP_loadError(QNetworkReply::NetworkError);

    void setting_Memory_Save_after();

    void setting_data_condition();

    void resume_Collision(void);

    void REFRESH_clicked();

    void save_MessageBox();

    void load_MessageBox();

    void on_HS_BASE_SPEED_valueChanged(int value);
// ===========================================================
#define PB_A_1_PART_START   {
private slots:

    void on_PB_POWER_A0_clicked();

    void on_PB_POWER_A1_clicked();

    void on_PB_A_1_0_clicked();

    void on_PB_A_1_1_clicked();

    void on_PB_A_1_2_clicked();

    void on_PB_A_1_3_clicked();
#define PB_A_1_PART_END }
// ===========================================================
#define PB_B_0_PART_START   {
private slots:
    void on_PB_B_0_0_clicked();

    void on_PB_B_0_1_clicked();

    void on_PB_B_0_2_clicked();

    void on_PB_B_0_3_clicked();

    void on_PB_B_0_4_clicked();

    void on_PB_B_0_5_clicked();

    void on_PB_B_0_6_clicked();

    void on_PB_B_0_7_clicked();

    void on_PB_B_0_Add_clicked();

    void on_PB_B_0_Mod_clicked();

    void on_PB_B_0_Del_clicked();

    void on_PB_B_0_Set_clicked();

    void on_PB_B_0_Back_clicked();

    void on_PB_B0_1_clicked();

    void on_PB_B0_2_clicked();

    void on_PB_B0_3_clicked();

    void on_PB_B0_4_clicked();

    void on_PB_B0_5_clicked();

    void on_PB_B0_6_clicked();

    void on_PB_B0_7_clicked();

    void on_PB_B0_8_clicked();

    void on_PB_B0_9_clicked();

    void on_PB_B0_10_clicked();

    void on_PB_B0_11_clicked();

    //B0R1_key {

    void B0R1_key_view();

    void B0R1_key_clicked_number(QString number);

    void on_PB_B0R1_key_0_clicked();

    void on_PB_B0R1_key_1_clicked();

    void on_PB_B0R1_key_2_clicked();

    void on_PB_B0R1_key_3_clicked();

    void on_PB_B0R1_key_4_clicked();

    void on_PB_B0R1_key_5_clicked();

    void on_PB_B0R1_key_6_clicked();

    void on_PB_B0R1_key_7_clicked();

    void on_PB_B0R1_key_8_clicked();

    void on_PB_B0R1_key_9_clicked();

    void on_PB_B0R1_key_minus_clicked();

    void on_PB_B0R1_key_back_clicked();

    void on_PB_B0R1_key_dot_clicked();

    void on_PB_B0R1_key_enter_clicked();

    void on_PB_B0R1_key_exit_clicked();

    // B0R1_key }

    void on_LE_B0_A_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_V_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_S_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_T_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_W_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_WT_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_L_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_ONA_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_ONV_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_ONT_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_OFA_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_OFV_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_OFT_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_WU_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_Per_11_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B0_A_11_selectionChanged();

    void on_LE_B0_V_11_selectionChanged();

    void on_LE_B0_S_11_selectionChanged();

    void on_LE_B0_T_11_selectionChanged();

    void on_LE_B0_W_11_selectionChanged();

    void on_LE_B0_WT_11_selectionChanged();

    void on_LE_B0_L_11_selectionChanged();

    void on_LE_B0_ONA_11_selectionChanged();

    void on_LE_B0_ONV_11_selectionChanged();

    void on_LE_B0_ONT_11_selectionChanged();

    void on_LE_B0_OFA_11_selectionChanged();

    void on_LE_B0_OFV_11_selectionChanged();

    void on_LE_B0_OFT_11_selectionChanged();

    void on_LE_B0_WU_11_selectionChanged();

    void on_LE_B0_Per_11_selectionChanged();

    //B1R1_key {

    void B1R1_key_view();

    void B1R1_key_clicked_number(QString number);

    void on_PB_B1R1_key_0_clicked();

    void on_PB_B1R1_key_1_clicked();

    void on_PB_B1R1_key_2_clicked();

    void on_PB_B1R1_key_3_clicked();

    void on_PB_B1R1_key_4_clicked();

    void on_PB_B1R1_key_5_clicked();

    void on_PB_B1R1_key_6_clicked();

    void on_PB_B1R1_key_7_clicked();

    void on_PB_B1R1_key_8_clicked();

    void on_PB_B1R1_key_9_clicked();

    void on_PB_B1R1_key_minus_clicked();

    void on_PB_B1R1_key_back_clicked();

    void on_PB_B1R1_key_dot_clicked();

    void on_PB_B1R1_key_enter_clicked();

    void on_PB_B1R1_key_exit_clicked();

    // B1R1_key }

    void on_TW_1_cellDoubleClicked(int row, int column);

#define PB_B_0_PART_END }
// ===========================================================
#define PB_B_1_PART_START   {
private slots:
    void on_PB_B_1_Back_clicked();

    void on_PB_B_1_GAS_pressed();

    void on_PB_B_1_GAS_released();

    void on_PB_B_1_Fwd_pressed();

    void on_PB_B_1_Fwd_released();

    void on_PB_B_1_Bwd_pressed();

    void on_PB_B_1_Bwd_released();

    void on_PB_B_1_Set_clicked();

    void on_TW_10_cellDoubleClicked(int row, int column);

#define PB_B_1_PART_END }
// ===========================================================
#define PB_B_2_PART_START   {
private slots:
    void on_PB_B_2_0_clicked();

    void on_PB_B_2_Back_clicked();

    void on_PB_B_2_Mod_clicked();

    void on_PB_B_2_Play_clicked();

    void make_and_run(unsigned int index_num);

    void on_PB_B_2_Pause_clicked();

    void PROGRAM_RESUME();

    void on_PB_B_2_Stop_clicked();

    void on_PB_B_2_nPlay_clicked();

    void on_PB_B_2_Save_clicked();

    //B2C01_key {

    void B2C01_key_view();

    void B2C01_key_clicked_number(QString number);

    void on_PB_B2C01_key_dot_clicked();

    void on_PB_B2C01_key_0_clicked();

    void on_PB_B2C01_key_1_clicked();

    void on_PB_B2C01_key_2_clicked();

    void on_PB_B2C01_key_3_clicked();

    void on_PB_B2C01_key_4_clicked();

    void on_PB_B2C01_key_5_clicked();

    void on_PB_B2C01_key_6_clicked();

    void on_PB_B2C01_key_7_clicked();

    void on_PB_B2C01_key_8_clicked();

    void on_PB_B2C01_key_9_clicked();

    void on_PB_B2C01_key_minus_clicked();

    void on_PB_B2C01_key_back_clicked();

    void on_PB_B2C01_key_enter_clicked();

    void on_PB_B2C01_key_exit_clicked();

    //B2C01_key }

    void on_LE_B_2_nPlay_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B_2_nPlay_selectionChanged();

    //B2C1_key {

    void B2C1_key_view();

    void B2C1_key_clicked_number(QString number);

    void on_PB_B2C1_key_0_clicked();

    void on_PB_B2C1_key_1_clicked();

    void on_PB_B2C1_key_2_clicked();

    void on_PB_B2C1_key_3_clicked();

    void on_PB_B2C1_key_4_clicked();

    void on_PB_B2C1_key_5_clicked();

    void on_PB_B2C1_key_6_clicked();

    void on_PB_B2C1_key_7_clicked();

    void on_PB_B2C1_key_8_clicked();

    void on_PB_B2C1_key_9_clicked();

    void on_PB_B2C1_key_q_clicked();

    void on_PB_B2C1_key_w_clicked();

    void on_PB_B2C1_key_e_clicked();

    void on_PB_B2C1_key_r_clicked();

    void on_PB_B2C1_key_t_clicked();

    void on_PB_B2C1_key_y_clicked();

    void on_PB_B2C1_key_u_clicked();

    void on_PB_B2C1_key_i_clicked();

    void on_PB_B2C1_key_o_clicked();

    void on_PB_B2C1_key_p_clicked();

    void on_PB_B2C1_key_a_clicked();

    void on_PB_B2C1_key_s_clicked();

    void on_PB_B2C1_key_d_clicked();

    void on_PB_B2C1_key_f_clicked();

    void on_PB_B2C1_key_g_clicked();

    void on_PB_B2C1_key_h_clicked();

    void on_PB_B2C1_key_j_clicked();

    void on_PB_B2C1_key_k_clicked();

    void on_PB_B2C1_key_l_clicked();

    void on_PB_B2C1_key_z_clicked();

    void on_PB_B2C1_key_x_clicked();

    void on_PB_B2C1_key_c_clicked();

    void on_PB_B2C1_key_v_clicked();

    void on_PB_B2C1_key_b_clicked();

    void on_PB_B2C1_key_n_clicked();

    void on_PB_B2C1_key_m_clicked();

    void on_PB_B2C1_key_minus_clicked();

    void on_PB_B2C1_key_back_clicked();

    void on_PB_B2C1_key_enter_clicked();

    void on_PB_B2C1_key_exit_clicked();

    //B2C1_key }

    void on_LE_B_2_Save_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B_2_Save_selectionChanged();

    void on_PB_B2C2_1_clicked();

    void on_PB_B2C2_2_clicked();

    void on_PB_B2C2_3_clicked();

    void on_PB_B2C2_4_clicked();

    void on_PB_B2C2_5_clicked();

    void on_PB_B2C2_6_clicked();

    void on_PB_B2C2_7_clicked();

    void on_PB_B2C2_8_clicked();

    void on_PB_B2C2_9_clicked();

    void on_PB_B2C2_10_clicked();

    void on_PB_B2C2_11_clicked();

    void on_PB_B2C2_12_clicked();

    void on_PB_B2C2_13_clicked();

    void on_PB_B2C2_14_clicked();

    void on_PB_B2C2_15_clicked();

    void on_PB_B2C2_16_clicked();

    void on_PB_B2C2_17_clicked();

    void on_PB_B2C2_18_clicked();

    void on_PB_B2C2_19_clicked();

    void on_PB_B2C2_20_clicked();

    void on_PB_B2C2_21_clicked();

    void on_PB_B2C2_22_clicked();

    void on_PB_B2C2_23_clicked();

    void on_PB_B2C2_24_clicked();

    void on_PB_B2C2_25_clicked();

    void on_PB_B2C2_26_clicked();

    void on_PB_B2C2_27_clicked();

    void on_PB_B2C2_28_clicked();

    void on_PB_B2C2_29_clicked();

    void on_PB_B2C2_30_clicked();

    void on_PB_B2C2_31_clicked();

    void on_PB_B2C2_32_clicked();

    void on_PB_B2C2_33_clicked();

    void on_PB_B2C2_34_clicked();

    void on_PB_B2C2_35_clicked();

    void on_PB_B2C2_36_clicked();

    void on_PB_B2C2_37_clicked();

    void on_PB_B2C2_38_clicked();

    void on_PB_B2C2_39_clicked();

    void on_PB_B2C2_40_clicked();

    void on_PB_B2C2_41_clicked();

    void on_PB_B2C2_42_clicked();

    void on_PB_B2C2_43_clicked();

    void on_PB_B2C2_44_clicked();

    void on_PB_B2C2_45_clicked();

    void on_PB_B2C2_46_clicked();

    void on_PB_B2C2_47_clicked();

    void on_PB_B2C2_48_clicked();

    void on_PB_B2C2_49_clicked();

    void on_PB_B2C2_50_clicked();

    void on_PB_B2C2_back_clicked();

#define PB_B_2_PART_END }
// ===========================================================
#define PB_C_0_PART_START   {
private slots:
    void on_PB_C_0_0_clicked();

    void on_PB_C_0_Back_clicked();

    void on_PB_C_0_Load_1_clicked();

    void on_PB_C_0_Load_2_clicked();

    void on_PB_C_0_Load_3_clicked();

    void on_PB_C_0_Load_4_clicked();

    void on_PB_C_0_Load_5_clicked();

    void on_PB_C_0_Load_6_clicked();

    void on_PB_C_0_Load_7_clicked();

    void on_PB_C_0_Load_8_clicked();

    void on_PB_C_0_Load_9_clicked();

    void on_PB_C_0_Load_10_clicked();

    void on_PB_C_0_Set_clicked();

    void on_PB_C0C1_1_clicked();

    void on_PB_C0C1_2_clicked();

    void on_PB_C0C1_3_clicked();

    void on_PB_C0C1_4_clicked();

    void on_PB_C0C1_5_clicked();

    void on_PB_C0C1_6_clicked();

    void on_PB_C0C1_7_clicked();

    void on_PB_C0C1_8_clicked();

    void on_PB_C0C1_9_clicked();

    void on_PB_C0C1_10_clicked();

    void on_PB_C0C1_11_clicked();

    void on_PB_C0C1_12_clicked();

    void on_PB_C0C1_13_clicked();

    void on_PB_C0C1_14_clicked();

    void on_PB_C0C1_15_clicked();

    void on_PB_C0C1_16_clicked();

    void on_PB_C0C1_17_clicked();

    void on_PB_C0C1_18_clicked();

    void on_PB_C0C1_19_clicked();

    void on_PB_C0C1_20_clicked();

    void on_PB_C0C1_21_clicked();

    void on_PB_C0C1_22_clicked();

    void on_PB_C0C1_23_clicked();

    void on_PB_C0C1_24_clicked();

    void on_PB_C0C1_25_clicked();

    void on_PB_C0C1_26_clicked();

    void on_PB_C0C1_27_clicked();

    void on_PB_C0C1_28_clicked();

    void on_PB_C0C1_29_clicked();

    void on_PB_C0C1_30_clicked();

    void on_PB_C0C1_31_clicked();

    void on_PB_C0C1_32_clicked();

    void on_PB_C0C1_33_clicked();

    void on_PB_C0C1_34_clicked();

    void on_PB_C0C1_35_clicked();

    void on_PB_C0C1_36_clicked();

    void on_PB_C0C1_37_clicked();

    void on_PB_C0C1_38_clicked();

    void on_PB_C0C1_39_clicked();

    void on_PB_C0C1_40_clicked();

    void on_PB_C0C1_41_clicked();

    void on_PB_C0C1_42_clicked();

    void on_PB_C0C1_43_clicked();

    void on_PB_C0C1_44_clicked();

    void on_PB_C0C1_45_clicked();

    void on_PB_C0C1_46_clicked();

    void on_PB_C0C1_47_clicked();

    void on_PB_C0C1_48_clicked();

    void on_PB_C0C1_49_clicked();

    void on_PB_C0C1_50_clicked();

    void on_PB_C0C1_back_clicked();

    //C7C0_key {

        void C7C0_key_view();

        void C7C0_key_clicked_number(QString number);

        void on_PB_C7C0_key_dot_clicked();

        void on_PB_C7C0_key_0_clicked();

        void on_PB_C7C0_key_1_clicked();

        void on_PB_C7C0_key_2_clicked();

        void on_PB_C7C0_key_3_clicked();

        void on_PB_C7C0_key_4_clicked();

        void on_PB_C7C0_key_5_clicked();

        void on_PB_C7C0_key_6_clicked();

        void on_PB_C7C0_key_7_clicked();

        void on_PB_C7C0_key_8_clicked();

        void on_PB_C7C0_key_9_clicked();

        void on_PB_C7C0_key_minus_clicked();

        void on_PB_C7C0_key_back_clicked();

        void on_PB_C7C0_key_enter_clicked();

        void on_PB_C7C0_key_exit_clicked();


#define PB_C_0_PART_END }
// ===========================================================
#define PB_D_0_PART_START   {
private slots:
    void on_PB_D_0_Back_clicked();

    void on_PB_D_0_Set_clicked();

    void on_PB_D_0_0_clicked();

    void on_PB_D_0_1_clicked();

    void on_PB_D_0_2_clicked();

    void on_PB_D_0_Use_Axis7_clicked();

    void on_PB_D_0_Unuse_Axis7_clicked();

    void on_PB_D_0_Use_Axis8_clicked();

    void on_PB_D_0_Unuse_Axis8_clicked();

    void on_PB_D_0_Use_Axis9_clicked();

    void on_PB_D_0_Unuse_Axis9_clicked();

    void on_PB_D_0_Use_Sound_clicked();

    void on_PB_D_0_Unuse_Sound_clicked();

    void on_PB_D_0_Use_Tig_clicked();

    void on_PB_D_0_Unuse_Tig_clicked();

    void on_PB_D_0_Use_Wire_clicked();

    void on_PB_D_0_Unuse_Wire_clicked();

    void on_PB_D_0_Use_Foot_clicked();

    void on_PB_D_0_Unuse_Foot_clicked();

    // D0C0R1_key {

    void D0C0R1_key_view();

    void D0C0R1_key_clicked_number(QString number);

    void on_PB_D0C0R1_key_0_clicked();

    void on_PB_D0C0R1_key_1_clicked();

    void on_PB_D0C0R1_key_2_clicked();

    void on_PB_D0C0R1_key_3_clicked();

    void on_PB_D0C0R1_key_4_clicked();

    void on_PB_D0C0R1_key_5_clicked();

    void on_PB_D0C0R1_key_6_clicked();

    void on_PB_D0C0R1_key_7_clicked();

    void on_PB_D0C0R1_key_8_clicked();

    void on_PB_D0C0R1_key_9_clicked();

    void on_PB_D0C0R1_key_minus_clicked();

    void on_PB_D0C0R1_key_back_clicked();

    void on_PB_D0C0R1_key_dot_clicked();

    void on_PB_D0C0R1_key_enter_clicked();

    void on_PB_D0C0R1_key_exit_clicked();

    // D0C0R1_key }

    void on_LE_D_0_A1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_V10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_S10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONA10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_A1_selectionChanged();

    void on_LE_D_0_A2_selectionChanged();

    void on_LE_D_0_A3_selectionChanged();

    void on_LE_D_0_A4_selectionChanged();

    void on_LE_D_0_A5_selectionChanged();

    void on_LE_D_0_A6_selectionChanged();

    void on_LE_D_0_A7_selectionChanged();

    void on_LE_D_0_A8_selectionChanged();

    void on_LE_D_0_A9_selectionChanged();

    void on_LE_D_0_A10_selectionChanged();

    void on_LE_D_0_V1_selectionChanged();

    void on_LE_D_0_V2_selectionChanged();

    void on_LE_D_0_V3_selectionChanged();

    void on_LE_D_0_V4_selectionChanged();

    void on_LE_D_0_V5_selectionChanged();

    void on_LE_D_0_V6_selectionChanged();

    void on_LE_D_0_V7_selectionChanged();

    void on_LE_D_0_V8_selectionChanged();

    void on_LE_D_0_V9_selectionChanged();

    void on_LE_D_0_V10_selectionChanged();

    void on_LE_D_0_S1_selectionChanged();

    void on_LE_D_0_S2_selectionChanged();

    void on_LE_D_0_S3_selectionChanged();

    void on_LE_D_0_S4_selectionChanged();

    void on_LE_D_0_S5_selectionChanged();

    void on_LE_D_0_S6_selectionChanged();

    void on_LE_D_0_S7_selectionChanged();

    void on_LE_D_0_S8_selectionChanged();

    void on_LE_D_0_S9_selectionChanged();

    void on_LE_D_0_S10_selectionChanged();

    void on_LE_D_0_ONA1_selectionChanged();

    void on_LE_D_0_ONA2_selectionChanged();

    void on_LE_D_0_ONA3_selectionChanged();

    void on_LE_D_0_ONA4_selectionChanged();

    void on_LE_D_0_ONA5_selectionChanged();

    void on_LE_D_0_ONA6_selectionChanged();

    void on_LE_D_0_ONA7_selectionChanged();

    void on_LE_D_0_ONA8_selectionChanged();

    void on_LE_D_0_ONA9_selectionChanged();

    void on_LE_D_0_ONA10_selectionChanged();

    // D0C0L1_key {

    void D0C0L1_key_view();

    void D0C0L1_key_clicked_number(QString number);

    void on_PB_D0C0L1_key_0_clicked();

    void on_PB_D0C0L1_key_1_clicked();

    void on_PB_D0C0L1_key_2_clicked();

    void on_PB_D0C0L1_key_3_clicked();

    void on_PB_D0C0L1_key_4_clicked();

    void on_PB_D0C0L1_key_5_clicked();

    void on_PB_D0C0L1_key_6_clicked();

    void on_PB_D0C0L1_key_7_clicked();

    void on_PB_D0C0L1_key_8_clicked();

    void on_PB_D0C0L1_key_9_clicked();

    void on_PB_D0C0L1_key_minus_clicked();

    void on_PB_D0C0L1_key_back_clicked();

    void on_PB_D0C0L1_key_dot_clicked();

    void on_PB_D0C0L1_key_enter_clicked();

    void on_PB_D0C0L1_key_exit_clicked();

    // D0C0L1_key }

    void on_LE_D_0_ONV1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONT10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFA10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFV10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT6_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT7_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT8_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT9_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_OFT10_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_ONV1_selectionChanged();

    void on_LE_D_0_ONV2_selectionChanged();

    void on_LE_D_0_ONV3_selectionChanged();

    void on_LE_D_0_ONV4_selectionChanged();

    void on_LE_D_0_ONV5_selectionChanged();

    void on_LE_D_0_ONV6_selectionChanged();

    void on_LE_D_0_ONV7_selectionChanged();

    void on_LE_D_0_ONV8_selectionChanged();

    void on_LE_D_0_ONV9_selectionChanged();

    void on_LE_D_0_ONV10_selectionChanged();

    void on_LE_D_0_ONT1_selectionChanged();

    void on_LE_D_0_ONT2_selectionChanged();

    void on_LE_D_0_ONT3_selectionChanged();

    void on_LE_D_0_ONT4_selectionChanged();

    void on_LE_D_0_ONT5_selectionChanged();

    void on_LE_D_0_ONT6_selectionChanged();

    void on_LE_D_0_ONT7_selectionChanged();

    void on_LE_D_0_ONT8_selectionChanged();

    void on_LE_D_0_ONT9_selectionChanged();

    void on_LE_D_0_ONT10_selectionChanged();

    void on_LE_D_0_OFA1_selectionChanged();

    void on_LE_D_0_OFA2_selectionChanged();

    void on_LE_D_0_OFA3_selectionChanged();

    void on_LE_D_0_OFA4_selectionChanged();

    void on_LE_D_0_OFA5_selectionChanged();

    void on_LE_D_0_OFA6_selectionChanged();

    void on_LE_D_0_OFA7_selectionChanged();

    void on_LE_D_0_OFA8_selectionChanged();

    void on_LE_D_0_OFA9_selectionChanged();

    void on_LE_D_0_OFA10_selectionChanged();

    void on_LE_D_0_OFV1_selectionChanged();

    void on_LE_D_0_OFV2_selectionChanged();

    void on_LE_D_0_OFV3_selectionChanged();

    void on_LE_D_0_OFV4_selectionChanged();

    void on_LE_D_0_OFV5_selectionChanged();

    void on_LE_D_0_OFV6_selectionChanged();

    void on_LE_D_0_OFV7_selectionChanged();

    void on_LE_D_0_OFV8_selectionChanged();

    void on_LE_D_0_OFV9_selectionChanged();

    void on_LE_D_0_OFV10_selectionChanged();

    void on_LE_D_0_OFT1_selectionChanged();

    void on_LE_D_0_OFT2_selectionChanged();

    void on_LE_D_0_OFT3_selectionChanged();

    void on_LE_D_0_OFT4_selectionChanged();

    void on_LE_D_0_OFT5_selectionChanged();

    void on_LE_D_0_OFT6_selectionChanged();

    void on_LE_D_0_OFT7_selectionChanged();

    void on_LE_D_0_OFT8_selectionChanged();

    void on_LE_D_0_OFT9_selectionChanged();

    void on_LE_D_0_OFT10_selectionChanged();

    // D0C1R1_key {

    void D0C1R1_key_view();

    void D0C1R1_key_clicked_number(QString number);

    void on_PB_D0C1R1_key_0_clicked();

    void on_PB_D0C1R1_key_1_clicked();

    void on_PB_D0C1R1_key_2_clicked();

    void on_PB_D0C1R1_key_3_clicked();

    void on_PB_D0C1R1_key_4_clicked();

    void on_PB_D0C1R1_key_5_clicked();

    void on_PB_D0C1R1_key_6_clicked();

    void on_PB_D0C1R1_key_7_clicked();

    void on_PB_D0C1R1_key_8_clicked();

    void on_PB_D0C1R1_key_9_clicked();

    void on_PB_D0C1R1_key_minus_clicked();

    void on_PB_D0C1R1_key_back_clicked();

    void on_PB_D0C1R1_key_dot_clicked();

    void on_PB_D0C1R1_key_enter_clicked();

    void on_PB_D0C1R1_key_exit_clicked();

    // D0C1R1_key }

    void on_LE_D_0_Movj_Vel_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Movj_Acc_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Movl_Vel_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Movl_Acc_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Arc_retry_vel_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Arc_retry_time_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Axis_0_Vel_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Axis_0_Acc_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Axis_1_Vel_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Axis_1_Acc_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Axis_2_Vel_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Axis_2_Acc_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_data_0_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_data_1_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_data_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_data_3_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_data_4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_data_5_cursorPositionChanged(int arg1, int arg2);

    void on_LE_D_0_Movj_Vel_selectionChanged();

    void on_LE_D_0_Movj_Acc_selectionChanged();

    void on_LE_D_0_Movl_Vel_selectionChanged();

    void on_LE_D_0_Movl_Acc_selectionChanged();

    void on_LE_D_0_Arc_retry_vel_selectionChanged();

    void on_LE_D_0_Arc_retry_time_selectionChanged();

    void on_LE_D_0_Axis_0_Vel_selectionChanged();

    void on_LE_D_0_Axis_0_Acc_selectionChanged();

    void on_LE_D_0_Axis_1_Vel_selectionChanged();

    void on_LE_D_0_Axis_1_Acc_selectionChanged();

    void on_LE_D_0_Axis_2_Vel_selectionChanged();

    void on_LE_D_0_Axis_2_Acc_selectionChanged();

    void on_LE_D_0_data_0_selectionChanged();

    void on_LE_D_0_data_1_selectionChanged();

    void on_LE_D_0_data_2_selectionChanged();

    void on_LE_D_0_data_3_selectionChanged();

    void on_LE_D_0_data_4_selectionChanged();

    void on_LE_D_0_data_5_selectionChanged();
#define PB_D_0_PART_END }
// ===========================================================
#define PB_E_0_PART_START   {
private slots:
    void on_PB_E_0_Back_clicked();

    void on_PB_E_1_clicked();

    void on_PB_E_2_clicked();

    void on_PB_E_3_clicked();

    void on_PB_E_4_clicked();

    void on_PB_E_5_clicked();

    void on_PB_E_6_clicked();

    void on_PB_T5_0_clicked();

    void on_PB_T5_1_clicked();

    void on_PB_T5_2_clicked();

    void on_PB_T5_3_clicked();

    void on_PB_T5_4_clicked();

    void on_PB_T5_5_clicked();

    void on_PB_T5_6_clicked();

    void on_PB_E_7_clicked();

    void on_PB_E_8_clicked();

    void on_PB_E_9_clicked();

    void on_PB_E_10_clicked();

    void video_positionChanged(qint64 position);

    void video_durationChanged(qint64 position);

#define PB_E_0_PART_END }
// ===========================================================
    void on_PB_E0R0_Play_clicked();

    void on_PB_E0R0_Pause_clicked();

    void on_PB_E0R0_Stop_clicked();

    void on_S_E0R0_sliderMoved(int position);

    void on_PB_E0R1_Play_clicked();

    void on_PB_E0R1_Pause_clicked();

    void on_PB_E0R1_Stop_clicked();

    void on_S_E0R1_sliderMoved(int position);

    void on_PB_E0R2_Play_clicked();

    void on_PB_E0R2_Pause_clicked();

    void on_PB_E0R2_Stop_clicked();

    void on_S_E0R2_sliderMoved(int position);

    void on_PB_E0R3_Play_clicked();

    void on_PB_E0R3_Pause_clicked();

    void on_PB_E0R3_Stop_clicked();

    void on_S_E0R3_sliderMoved(int position);

    void on_PB_E0R4_Play_clicked();

    void on_PB_E0R4_Pause_clicked();

    void on_PB_E0R4_Stop_clicked();

    void on_S_E0R4_sliderMoved(int position);

    void on_PB_E0R5_Play_clicked();

    void on_PB_E0R5_Pause_clicked();

    void on_PB_E0R5_Stop_clicked();

    void on_S_E0R5_sliderMoved(int position);

    void on_PB_E0R6_Play_clicked();

    void on_PB_E0R6_Pause_clicked();

    void on_PB_E0R6_Stop_clicked();

    void on_S_E0R6_sliderMoved(int position);

    void on_PB_E0R7_Play_clicked();

    void on_PB_E0R7_Pause_clicked();

    void on_PB_E0R7_Stop_clicked();

    void on_S_E0R7_sliderMoved(int position);

    void on_PB_E0R8_Play_clicked();

    void on_PB_E0R8_Pause_clicked();

    void on_PB_E0R8_Stop_clicked();

    void on_S_E0R8_sliderMoved(int position);

    void on_PB_E0R9_Play_clicked();

    void on_PB_E0R9_Pause_clicked();

    void on_PB_E0R9_Stop_clicked();

    void on_S_E0R9_sliderMoved(int position);

    void on_PB_E0R10_Play_clicked();

    void on_PB_E0R10_Pause_clicked();

    void on_PB_E0R10_Stop_clicked();

    void on_S_E0R10_sliderMoved(int position);

    void on_PB_E0R11_Play_clicked();

    void on_PB_E0R11_Pause_clicked();

    void on_PB_E0R11_Stop_clicked();

    void on_S_E0R11_sliderMoved(int position);

    void on_PB_E0R12_Play_clicked();

    void on_PB_E0R12_Pause_clicked();

    void on_PB_E0R12_Stop_clicked();

    void on_S_E0R12_sliderMoved(int position);

    void on_PB_E0R13_Play_clicked();

    void on_PB_E0R13_Pause_clicked();

    void on_PB_E0R13_Stop_clicked();

    void on_S_E0R13_sliderMoved(int position);

    void on_PB_E0R14_Play_clicked();

    void on_PB_E0R14_Pause_clicked();

    void on_PB_E0R14_Stop_clicked();

    void on_S_E0R14_sliderMoved(int position);

    void on_PB_E0R15_Play_clicked();

    void on_PB_E0R15_Pause_clicked();

    void on_PB_E0R15_Stop_clicked();

    void on_S_E0R15_sliderMoved(int position);

#define Data_0_PART_START {
// ===========================================================
    void on_BTN_MODE_BASE_clicked();

    void on_BTN_MODE_LH_clicked();

    void on_BTN_MODE_HOME_clicked();

    void on_BTN_MODE_RH_clicked();

    void on_BTN_EXIT_1_clicked();

    void update_TW_Home();

    void load_TW_Home();

    void save_TW_Home();

    //B4R1_key {

    void B4R1_key_view();

    void B4R1_key_clicked_number(QString number);

    void on_PB_B4R1_key_0_clicked();

    void on_PB_B4R1_key_1_clicked();

    void on_PB_B4R1_key_2_clicked();

    void on_PB_B4R1_key_3_clicked();

    void on_PB_B4R1_key_4_clicked();

    void on_PB_B4R1_key_5_clicked();

    void on_PB_B4R1_key_6_clicked();

    void on_PB_B4R1_key_7_clicked();

    void on_PB_B4R1_key_8_clicked();

    void on_PB_B4R1_key_9_clicked();

    void on_PB_B4R1_key_minus_clicked();

    void on_PB_B4R1_key_back_clicked();

    void on_PB_B4R1_key_dot_clicked();

    void on_PB_B4R1_key_enter_clicked();

    void on_PB_B4R1_key_exit_clicked();

    // B4R1_key }

    void on_TW_Home_cellDoubleClicked(int row, int column);

#define Data_0_PART_END }
// ===========================================================
    void on_PB_B_4_Back_clicked();

    void on_PB_B_4_Set_clicked();

    void on_BTN_Load_Base_clicked();

    void on_BTN_Load_Line_clicked();

    void on_PB_A3C1_back_clicked();

    void on_PB_A3C2_back_clicked();

    void on_BTN_FILE_LOAD_LH_clicked();

    void on_BTN_FILE_LOAD_RH_clicked();

    void on_BTN_Load_Line_OK_clicked();

    void on_PB_C_3_Play_clicked();

    void on_PB_C_3_Pause_clicked();

    void on_PB_C_3_Stop_clicked();

    void Load_Home_make();

    void Load_LH_make();

    void Load_RH_make();

    void on_PB_A3C3_back_clicked();

    void on_BTN_Save_Tag_LH_1_clicked();

    void on_BTN_Save_Main_LH_1_clicked();

    void on_BTN_Save_Tag_LH_2_clicked();

    void on_BTN_Save_Main_LH_2_clicked();

    void on_BTN_Save_Tag_LH_3_clicked();

    void on_BTN_Save_Main_LH_3_clicked();

    void on_BTN_Save_Tag_LH_4_clicked();

    void on_BTN_Save_Main_LH_4_clicked();

    void on_BTN_Save_Tag_LH_5_clicked();

    void on_BTN_Save_Main_LH_5_clicked();

    void on_BTN_Save_Tag_LH_6_clicked();

    void on_BTN_Save_Main_LH_6_clicked();

    void on_BTN_Save_Tag_LH_7_clicked();

    void on_BTN_Save_Main_LH_7_clicked();

    void on_BTN_Save_Tag_LH_8_clicked();

    void on_BTN_Save_Main_LH_8_clicked();

    void on_BTN_Save_Tag_LH_9_clicked();

    void on_BTN_Save_Main_LH_9_clicked();

    void on_BTN_Save_Tag_LH_10_clicked();

    void on_BTN_Save_Main_LH_10_clicked();

    void on_BTN_Save_Tag_LH_11_clicked();

    void on_BTN_Save_Main_LH_11_clicked();

    void on_BTN_Save_Tag_LH_12_clicked();

    void on_BTN_Save_Main_LH_12_clicked();

    void on_BTN_Save_Tag_LH_13_clicked();

    void on_BTN_Save_Main_LH_13_clicked();

    void on_BTN_Save_Tag_LH_14_clicked();

    void on_BTN_Save_Main_LH_14_clicked();

    void on_BTN_Save_Tag_LH_15_clicked();

    void on_BTN_Save_Main_LH_15_clicked();

    void on_BTN_Save_Tag_LH_16_clicked();

    void on_BTN_Save_Main_LH_16_clicked();

    void on_BTN_Save_Tag_LH_17_clicked();

    void on_BTN_Save_Main_LH_17_clicked();

    void on_BTN_Save_Tag_LH_18_clicked();

    void on_BTN_Save_Main_LH_18_clicked();

    void on_BTN_Save_Tag_LH_19_clicked();

    void on_BTN_Save_Main_LH_19_clicked();

    void on_BTN_Save_Tag_LH_20_clicked();

    void on_BTN_Save_Main_LH_20_clicked();

    void on_BTN_Save_Tag_RH_1_clicked();

    void on_BTN_Save_Main_RH_1_clicked();

    void on_BTN_Save_Tag_RH_2_clicked();

    void on_BTN_Save_Main_RH_2_clicked();

    void on_BTN_Save_Tag_RH_3_clicked();

    void on_BTN_Save_Main_RH_3_clicked();

    void on_BTN_Save_Tag_RH_4_clicked();

    void on_BTN_Save_Main_RH_4_clicked();

    void on_BTN_Save_Tag_RH_5_clicked();

    void on_BTN_Save_Main_RH_5_clicked();

    void on_BTN_Save_Tag_RH_6_clicked();

    void on_BTN_Save_Main_RH_6_clicked();

    void on_BTN_Save_Tag_RH_7_clicked();

    void on_BTN_Save_Main_RH_7_clicked();

    void on_BTN_Save_Tag_RH_8_clicked();

    void on_BTN_Save_Main_RH_8_clicked();

    void on_BTN_Save_Tag_RH_9_clicked();

    void on_BTN_Save_Main_RH_9_clicked();

    void on_BTN_Save_Tag_RH_10_clicked();

    void on_BTN_Save_Main_RH_10_clicked();

    void on_BTN_Save_Tag_RH_11_clicked();

    void on_BTN_Save_Main_RH_11_clicked();

    void on_BTN_Save_Tag_RH_12_clicked();

    void on_BTN_Save_Main_RH_12_clicked();

    void on_BTN_Save_Tag_RH_13_clicked();

    void on_BTN_Save_Main_RH_13_clicked();

    void on_BTN_Save_Tag_RH_14_clicked();

    void on_BTN_Save_Main_RH_14_clicked();

    void on_BTN_Save_Tag_RH_15_clicked();

    void on_BTN_Save_Main_RH_15_clicked();

    void on_BTN_Save_Tag_RH_16_clicked();

    void on_BTN_Save_Main_RH_16_clicked();

    void on_BTN_Save_Tag_RH_17_clicked();

    void on_BTN_Save_Main_RH_17_clicked();

    void on_BTN_Save_Tag_RH_18_clicked();

    void on_BTN_Save_Main_RH_18_clicked();

    void on_BTN_Save_Tag_RH_19_clicked();

    void on_BTN_Save_Main_RH_19_clicked();

    void on_BTN_Save_Tag_RH_20_clicked();

    void on_BTN_Save_Main_RH_20_clicked();

    void on_PB_B2C3_back_clicked();

    void on_BTN_Load_Tag_LH_1_clicked();

    void on_BTN_Load_Main_LH_1_clicked();

    void on_BTN_Load_Tag_LH_2_clicked();

    void on_BTN_Load_Main_LH_2_clicked();

    void on_BTN_Load_Tag_LH_3_clicked();

    void on_BTN_Load_Main_LH_3_clicked();

    void on_BTN_Load_Tag_LH_4_clicked();

    void on_BTN_Load_Main_LH_4_clicked();

    void on_BTN_Load_Tag_LH_5_clicked();

    void on_BTN_Load_Main_LH_5_clicked();

    void on_BTN_Load_Tag_LH_6_clicked();

    void on_BTN_Load_Main_LH_6_clicked();

    void on_BTN_Load_Tag_LH_7_clicked();

    void on_BTN_Load_Main_LH_7_clicked();

    void on_BTN_Load_Tag_LH_8_clicked();

    void on_BTN_Load_Main_LH_8_clicked();

    void on_BTN_Load_Tag_LH_9_clicked();

    void on_BTN_Load_Main_LH_9_clicked();

    void on_BTN_Load_Tag_LH_10_clicked();

    void on_BTN_Load_Main_LH_10_clicked();

    void on_BTN_Load_Tag_LH_11_clicked();

    void on_BTN_Load_Main_LH_11_clicked();

    void on_BTN_Load_Tag_LH_12_clicked();

    void on_BTN_Load_Main_LH_12_clicked();

    void on_BTN_Load_Tag_LH_13_clicked();

    void on_BTN_Load_Main_LH_13_clicked();

    void on_BTN_Load_Tag_LH_14_clicked();

    void on_BTN_Load_Main_LH_14_clicked();

    void on_BTN_Load_Tag_LH_15_clicked();

    void on_BTN_Load_Main_LH_15_clicked();

    void on_BTN_Load_Tag_LH_16_clicked();

    void on_BTN_Load_Main_LH_16_clicked();

    void on_BTN_Load_Tag_LH_17_clicked();

    void on_BTN_Load_Main_LH_17_clicked();

    void on_BTN_Load_Tag_LH_18_clicked();

    void on_BTN_Load_Main_LH_18_clicked();

    void on_BTN_Load_Tag_LH_19_clicked();

    void on_BTN_Load_Main_LH_19_clicked();

    void on_BTN_Load_Tag_LH_20_clicked();

    void on_BTN_Load_Main_LH_20_clicked();

    void on_BTN_Load_Tag_RH_1_clicked();

    void on_BTN_Load_Main_RH_1_clicked();

    void on_BTN_Load_Tag_RH_2_clicked();

    void on_BTN_Load_Main_RH_2_clicked();

    void on_BTN_Load_Tag_RH_3_clicked();

    void on_BTN_Load_Main_RH_3_clicked();

    void on_BTN_Load_Tag_RH_4_clicked();

    void on_BTN_Load_Main_RH_4_clicked();

    void on_BTN_Load_Tag_RH_5_clicked();

    void on_BTN_Load_Main_RH_5_clicked();

    void on_BTN_Load_Tag_RH_6_clicked();

    void on_BTN_Load_Main_RH_6_clicked();

    void on_BTN_Load_Tag_RH_7_clicked();

    void on_BTN_Load_Main_RH_7_clicked();

    void on_BTN_Load_Tag_RH_8_clicked();

    void on_BTN_Load_Main_RH_8_clicked();

    void on_BTN_Load_Tag_RH_9_clicked();

    void on_BTN_Load_Main_RH_9_clicked();

    void on_BTN_Load_Tag_RH_10_clicked();

    void on_BTN_Load_Main_RH_10_clicked();

    void on_BTN_Load_Tag_RH_11_clicked();

    void on_BTN_Load_Main_RH_11_clicked();

    void on_BTN_Load_Tag_RH_12_clicked();

    void on_BTN_Load_Main_RH_12_clicked();

    void on_BTN_Load_Tag_RH_13_clicked();

    void on_BTN_Load_Main_RH_13_clicked();

    void on_BTN_Load_Tag_RH_14_clicked();

    void on_BTN_Load_Main_RH_14_clicked();

    void on_BTN_Load_Tag_RH_15_clicked();

    void on_BTN_Load_Main_RH_15_clicked();

    void on_BTN_Load_Tag_RH_16_clicked();

    void on_BTN_Load_Main_RH_16_clicked();

    void on_BTN_Load_Tag_RH_17_clicked();

    void on_BTN_Load_Main_RH_17_clicked();

    void on_BTN_Load_Tag_RH_18_clicked();

    void on_BTN_Load_Main_RH_18_clicked();

    void on_BTN_Load_Tag_RH_19_clicked();

    void on_BTN_Load_Main_RH_19_clicked();

    void on_BTN_Load_Tag_RH_20_clicked();

    void on_BTN_Load_Main_RH_20_clicked();

    void load_MessageBox_LH();

    void load_MessageBox_RH();

    void line_load_lh();

    void line_load_rh();

    void on_RB_GAJUB_clicked();

    void on_RB_ONEPOINT_WELD_clicked();

    void on_BTN_mode_LH_clicked();

    void on_BTN_mode_RH_clicked();

    void on_TW_10_cellClicked(int row, int column);

    void on_TW_1_cellPressed(int row, int column);

#define JOG_PART_START {
    void on_PB_B1R0_Smooth_clicked();

    void on_PB_B1R0_Tick_clicked();

    void on_PB_B1R0_Joint_clicked();

    void on_PB_B1R0_Global_clicked();

    void on_PB_B1R0_User_clicked();

    void on_PB_B1R0_Joint_plus_1_pressed();

    void on_PB_B1R0_Joint_plus_1_released();

    void on_PB_B1R0_Joint_minus_1_pressed();

    void on_PB_B1R0_Joint_minus_1_released();

    void on_PB_B1R0_Joint_plus_2_pressed();

    void on_PB_B1R0_Joint_plus_2_released();

    void on_PB_B1R0_Joint_minus_2_pressed();

    void on_PB_B1R0_Joint_minus_2_released();

    void on_PB_B1R0_Joint_plus_3_pressed();

    void on_PB_B1R0_Joint_plus_3_released();

    void on_PB_B1R0_Joint_minus_3_pressed();

    void on_PB_B1R0_Joint_minus_3_released();

    void on_PB_B1R0_Joint_plus_4_pressed();

    void on_PB_B1R0_Joint_plus_4_released();

    void on_PB_B1R0_Joint_minus_4_pressed();

    void on_PB_B1R0_Joint_minus_4_released();

    void on_PB_B1R0_Joint_plus_5_pressed();

    void on_PB_B1R0_Joint_plus_5_released();

    void on_PB_B1R0_Joint_minus_5_pressed();

    void on_PB_B1R0_Joint_minus_5_released();

    void on_PB_B1R0_Joint_plus_6_pressed();

    void on_PB_B1R0_Joint_plus_6_released();

    void on_PB_B1R0_Joint_minus_6_pressed();

    void on_PB_B1R0_Joint_minus_6_released();

    void on_PB_B1R0_Global_plus_x_pressed();

    void on_PB_B1R0_Global_plus_x_released();

    void on_PB_B1R0_Global_minus_x_pressed();

    void on_PB_B1R0_Global_minus_x_released();

    void on_PB_B1R0_Global_plus_y_pressed();

    void on_PB_B1R0_Global_plus_y_released();

    void on_PB_B1R0_Global_minus_y_pressed();

    void on_PB_B1R0_Global_minus_y_released();

    void on_PB_B1R0_Global_plus_z_pressed();

    void on_PB_B1R0_Global_plus_z_released();

    void on_PB_B1R0_Global_minus_z_pressed();

    void on_PB_B1R0_Global_minus_z_released();

    void on_PB_B1R0_Global_plus_rx_pressed();

    void on_PB_B1R0_Global_plus_rx_released();

    void on_PB_B1R0_Global_minus_rx_pressed();

    void on_PB_B1R0_Global_minus_rx_released();

    void on_PB_B1R0_Global_plus_ry_pressed();

    void on_PB_B1R0_Global_plus_ry_released();

    void on_PB_B1R0_Global_minus_ry_pressed();

    void on_PB_B1R0_Global_minus_ry_released();

    void on_PB_B1R0_Global_plus_rz_pressed();

    void on_PB_B1R0_Global_plus_rz_released();

    void on_PB_B1R0_Global_minus_rz_pressed();

    void on_PB_B1R0_Global_minus_rz_released();

    void on_PB_B1R0_User_plus_x_pressed();

    void on_PB_B1R0_User_plus_x_released();

    void on_PB_B1R0_User_minus_x_pressed();

    void on_PB_B1R0_User_minus_x_released();

    void on_PB_B1R0_User_plus_y_pressed();

    void on_PB_B1R0_User_plus_y_released();

    void on_PB_B1R0_User_minus_y_pressed();

    void on_PB_B1R0_User_minus_y_released();

    void on_PB_B1R0_User_plus_z_pressed();

    void on_PB_B1R0_User_plus_z_released();

    void on_PB_B1R0_User_minus_z_pressed();

    void on_PB_B1R0_User_minus_z_released();

    void on_PB_B1R0_User_plus_rx_pressed();

    void on_PB_B1R0_User_plus_rx_released();

    void on_PB_B1R0_User_minus_rx_pressed();

    void on_PB_B1R0_User_minus_rx_released();

    void on_PB_B1R0_User_plus_ry_pressed();

    void on_PB_B1R0_User_plus_ry_released();

    void on_PB_B1R0_User_minus_ry_pressed();

    void on_PB_B1R0_User_minus_ry_released();

    void on_PB_B1R0_User_plus_rz_pressed();

    void on_PB_B1R0_User_plus_rz_released();

    void on_PB_B1R0_User_minus_rz_pressed();

    void on_PB_B1R0_User_minus_rz_released();
#define JOG_PART_END }
    // D0C2R1_key {

    void D0C2R1_key_view();

    void D0C2R1_key_clicked_number(QString number);

    void on_PB_D0C2R1_key_0_clicked();

    void on_PB_D0C2R1_key_1_clicked();

    void on_PB_D0C2R1_key_2_clicked();

    void on_PB_D0C2R1_key_3_clicked();

    void on_PB_D0C2R1_key_4_clicked();

    void on_PB_D0C2R1_key_5_clicked();

    void on_PB_D0C2R1_key_6_clicked();

    void on_PB_D0C2R1_key_7_clicked();

    void on_PB_D0C2R1_key_8_clicked();

    void on_PB_D0C2R1_key_9_clicked();

    void on_PB_D0C2R1_key_minus_clicked();

    void on_PB_D0C2R1_key_back_clicked();

    void on_PB_D0C2R1_key_dot_clicked();

    void on_PB_D0C2R1_key_enter_clicked();

    void on_PB_D0C2R1_key_exit_clicked();

    // D0C2R1_key }

    void on_PB_D_0_Use_Analogweld_clicked();

    void on_PB_D_0_Unuse_Analogweld_clicked();

    void on_PB_D_0_Use_Digitalweld_clicked();

    void on_PB_D_0_Unuse_Digitalweld_clicked();

    void on_PB_D_0_Use_Froniusweld_clicked();

    void on_PB_D_0_Unuse_Froniusweld_clicked();

    void on_PB_D_0_Use_Esabweld_clicked();

    void on_PB_D_0_Unuse_Esabweld_clicked();

    void on_BTN_EXIT_2_clicked();

    void on_BTN_MODE_BASE_2_clicked();

    void on_BTN_MODE_HOME_2_clicked();

    void on_BTN_MODE_JIG_1_clicked();

    void on_BTN_MODE_JIG_2_clicked();

    void on_BTN_MODE_JIG_3_clicked();

    void on_PB_A3C4_back_clicked();

    void on_BTN_Load_Line_OK_2_clicked();

    void on_PB_A3C4_0_clicked();

    void on_PB_A3C4_1_clicked();

    void on_BTN_Save_JIG_1_No_1_clicked();

    void on_BTN_Save_JIG_1_No_2_clicked();

    void on_BTN_Save_JIG_1_No_3_clicked();

    void on_BTN_Save_JIG_1_No_4_clicked();

    void on_BTN_Save_JIG_1_No_5_clicked();

    void on_BTN_Save_JIG_1_No_6_clicked();

    void on_BTN_Save_JIG_1_No_7_clicked();

    void on_BTN_Save_JIG_1_No_8_clicked();

    void on_BTN_Save_JIG_1_No_9_clicked();

    void on_BTN_Save_JIG_1_No_10_clicked();

    void on_BTN_Save_JIG_1_No_11_clicked();

    void on_BTN_Save_JIG_1_No_12_clicked();

    void on_BTN_Save_JIG_1_No_13_clicked();

    void on_BTN_Save_JIG_1_No_14_clicked();

    void on_BTN_Save_JIG_1_No_15_clicked();

    void on_BTN_Save_JIG_1_No_16_clicked();

    void on_BTN_Save_JIG_1_No_17_clicked();

    void on_BTN_Save_JIG_1_No_18_clicked();

    void on_BTN_Save_JIG_1_No_19_clicked();

    void on_BTN_Save_JIG_1_No_20_clicked();

    void on_BTN_Save_JIG_1_No_21_clicked();

    void on_BTN_Save_JIG_1_No_22_clicked();

    void on_BTN_Save_JIG_1_No_23_clicked();

    void on_BTN_Save_JIG_1_No_24_clicked();

    void on_BTN_Save_JIG_1_No_25_clicked();

    void on_BTN_Save_JIG_1_No_26_clicked();

    void on_BTN_Save_JIG_1_No_27_clicked();

    void on_BTN_Save_JIG_1_No_28_clicked();

    void on_BTN_Save_JIG_1_No_29_clicked();

    void on_BTN_Save_JIG_1_No_30_clicked();

    void on_BTN_Save_JIG_1_No_31_clicked();

    void on_BTN_Save_JIG_1_No_32_clicked();

    void on_BTN_Save_JIG_1_No_33_clicked();

    void on_BTN_Save_JIG_1_No_34_clicked();

    void on_BTN_Save_JIG_1_No_35_clicked();

    void on_BTN_Save_JIG_1_No_36_clicked();

    void on_BTN_Save_JIG_1_No_37_clicked();

    void on_BTN_Save_JIG_1_No_38_clicked();

    void on_BTN_Save_JIG_1_No_39_clicked();

    void on_BTN_Save_JIG_1_No_40_clicked();

    void on_BTN_Save_JIG_2_No_1_clicked();

    void on_BTN_Save_JIG_2_No_2_clicked();

    void on_BTN_Save_JIG_2_No_3_clicked();

    void on_BTN_Save_JIG_2_No_4_clicked();

    void on_BTN_Save_JIG_2_No_5_clicked();

    void on_BTN_Save_JIG_2_No_6_clicked();

    void on_BTN_Save_JIG_2_No_7_clicked();

    void on_BTN_Save_JIG_2_No_8_clicked();

    void on_BTN_Save_JIG_2_No_9_clicked();

    void on_BTN_Save_JIG_2_No_10_clicked();

    void on_BTN_Save_JIG_2_No_11_clicked();

    void on_BTN_Save_JIG_2_No_12_clicked();

    void on_BTN_Save_JIG_2_No_13_clicked();

    void on_BTN_Save_JIG_2_No_14_clicked();

    void on_BTN_Save_JIG_2_No_15_clicked();

    void on_BTN_Save_JIG_2_No_16_clicked();

    void on_BTN_Save_JIG_2_No_17_clicked();

    void on_BTN_Save_JIG_2_No_18_clicked();

    void on_BTN_Save_JIG_2_No_19_clicked();

    void on_BTN_Save_JIG_2_No_20_clicked();

    void on_BTN_Save_JIG_2_No_21_clicked();

    void on_BTN_Save_JIG_2_No_22_clicked();

    void on_BTN_Save_JIG_2_No_23_clicked();

    void on_BTN_Save_JIG_2_No_24_clicked();

    void on_BTN_Save_JIG_2_No_25_clicked();

    void on_BTN_Save_JIG_2_No_26_clicked();

    void on_BTN_Save_JIG_2_No_27_clicked();

    void on_BTN_Save_JIG_2_No_28_clicked();

    void on_BTN_Save_JIG_2_No_29_clicked();

    void on_BTN_Save_JIG_2_No_30_clicked();

    void on_BTN_Save_JIG_2_No_31_clicked();

    void on_BTN_Save_JIG_2_No_32_clicked();

    void on_BTN_Save_JIG_2_No_33_clicked();

    void on_BTN_Save_JIG_2_No_34_clicked();

    void on_BTN_Save_JIG_2_No_35_clicked();

    void on_BTN_Save_JIG_2_No_36_clicked();

    void on_BTN_Save_JIG_2_No_37_clicked();

    void on_BTN_Save_JIG_2_No_38_clicked();

    void on_BTN_Save_JIG_2_No_39_clicked();

    void on_BTN_Save_JIG_2_No_40_clicked();

    void on_BTN_Save_JIG_3_No_1_clicked();

    void on_BTN_Save_JIG_3_No_2_clicked();

    void on_BTN_Save_JIG_3_No_3_clicked();

    void on_BTN_Save_JIG_3_No_4_clicked();

    void on_BTN_Save_JIG_3_No_5_clicked();

    void on_BTN_Save_JIG_3_No_6_clicked();

    void on_BTN_Save_JIG_3_No_7_clicked();

    void on_BTN_Save_JIG_3_No_8_clicked();

    void on_BTN_Save_JIG_3_No_9_clicked();

    void on_BTN_Save_JIG_3_No_10_clicked();

    void on_BTN_Save_JIG_3_No_11_clicked();

    void on_BTN_Save_JIG_3_No_12_clicked();

    void on_BTN_Save_JIG_3_No_13_clicked();

    void on_BTN_Save_JIG_3_No_14_clicked();

    void on_BTN_Save_JIG_3_No_15_clicked();

    void on_BTN_Save_JIG_3_No_16_clicked();

    void on_BTN_Save_JIG_3_No_17_clicked();

    void on_BTN_Save_JIG_3_No_18_clicked();

    void on_BTN_Save_JIG_3_No_19_clicked();

    void on_BTN_Save_JIG_3_No_20_clicked();

    void on_BTN_Save_JIG_3_No_21_clicked();

    void on_BTN_Save_JIG_3_No_22_clicked();

    void on_BTN_Save_JIG_3_No_23_clicked();

    void on_BTN_Save_JIG_3_No_24_clicked();

    void on_BTN_Save_JIG_3_No_25_clicked();

    void on_BTN_Save_JIG_3_No_26_clicked();

    void on_BTN_Save_JIG_3_No_27_clicked();

    void on_BTN_Save_JIG_3_No_28_clicked();

    void on_BTN_Save_JIG_3_No_29_clicked();

    void on_BTN_Save_JIG_3_No_30_clicked();

    void on_BTN_Save_JIG_3_No_31_clicked();

    void on_BTN_Save_JIG_3_No_32_clicked();

    void on_BTN_Save_JIG_3_No_33_clicked();

    void on_BTN_Save_JIG_3_No_34_clicked();

    void on_BTN_Save_JIG_3_No_35_clicked();

    void on_BTN_Save_JIG_3_No_36_clicked();

    void on_BTN_Save_JIG_3_No_37_clicked();

    void on_BTN_Save_JIG_3_No_38_clicked();

    void on_BTN_Save_JIG_3_No_39_clicked();

    void on_BTN_Save_JIG_3_No_40_clicked();

    void on_PB_B2C4_0_clicked();

    void on_PB_B2C4_1_clicked();

    void on_PB_B2C5_0_clicked();

    void on_PB_B2C5_1_clicked();

    void on_PB_B2C4_back_clicked();

    void on_PB_B2C5_back_clicked();

    void load_MessageBox_JIG1();

    void load_MessageBox_JIG2();

    void load_MessageBox_JIG3();

    void line_load_JIG1();

    void line_load_JIG2();

    void line_load_JIG3();

    void on_BTN_Load_JIG_1_No_1_clicked();

    void on_BTN_Load_JIG_1_No_2_clicked();

    void on_BTN_Load_JIG_1_No_3_clicked();

    void on_BTN_Load_JIG_1_No_4_clicked();

    void on_BTN_Load_JIG_1_No_5_clicked();

    void on_BTN_Load_JIG_1_No_6_clicked();

    void on_BTN_Load_JIG_1_No_7_clicked();

    void on_BTN_Load_JIG_1_No_8_clicked();

    void on_BTN_Load_JIG_1_No_9_clicked();

    void on_BTN_Load_JIG_1_No_10_clicked();

    void on_BTN_Load_JIG_1_No_11_clicked();

    void on_BTN_Load_JIG_1_No_12_clicked();

    void on_BTN_Load_JIG_1_No_13_clicked();

    void on_BTN_Load_JIG_1_No_14_clicked();

    void on_BTN_Load_JIG_1_No_15_clicked();

    void on_BTN_Load_JIG_1_No_16_clicked();

    void on_BTN_Load_JIG_1_No_17_clicked();

    void on_BTN_Load_JIG_1_No_18_clicked();

    void on_BTN_Load_JIG_1_No_19_clicked();

    void on_BTN_Load_JIG_1_No_20_clicked();

    void on_BTN_Load_JIG_1_No_21_clicked();

    void on_BTN_Load_JIG_1_No_22_clicked();

    void on_BTN_Load_JIG_1_No_23_clicked();

    void on_BTN_Load_JIG_1_No_24_clicked();

    void on_BTN_Load_JIG_1_No_25_clicked();

    void on_BTN_Load_JIG_1_No_26_clicked();

    void on_BTN_Load_JIG_1_No_27_clicked();

    void on_BTN_Load_JIG_1_No_28_clicked();

    void on_BTN_Load_JIG_1_No_29_clicked();

    void on_BTN_Load_JIG_1_No_30_clicked();

    void on_BTN_Load_JIG_1_No_31_clicked();

    void on_BTN_Load_JIG_1_No_32_clicked();

    void on_BTN_Load_JIG_1_No_33_clicked();

    void on_BTN_Load_JIG_1_No_34_clicked();

    void on_BTN_Load_JIG_1_No_35_clicked();

    void on_BTN_Load_JIG_1_No_36_clicked();

    void on_BTN_Load_JIG_1_No_37_clicked();

    void on_BTN_Load_JIG_1_No_38_clicked();

    void on_BTN_Load_JIG_1_No_39_clicked();

    void on_BTN_Load_JIG_1_No_40_clicked();

    void on_BTN_Load_JIG_2_No_1_clicked();

    void on_BTN_Load_JIG_2_No_2_clicked();

    void on_BTN_Load_JIG_2_No_3_clicked();

    void on_BTN_Load_JIG_2_No_4_clicked();

    void on_BTN_Load_JIG_2_No_5_clicked();

    void on_BTN_Load_JIG_2_No_6_clicked();

    void on_BTN_Load_JIG_2_No_7_clicked();

    void on_BTN_Load_JIG_2_No_8_clicked();

    void on_BTN_Load_JIG_2_No_9_clicked();

    void on_BTN_Load_JIG_2_No_10_clicked();

    void on_BTN_Load_JIG_2_No_11_clicked();

    void on_BTN_Load_JIG_2_No_12_clicked();

    void on_BTN_Load_JIG_2_No_13_clicked();

    void on_BTN_Load_JIG_2_No_14_clicked();

    void on_BTN_Load_JIG_2_No_15_clicked();

    void on_BTN_Load_JIG_2_No_16_clicked();

    void on_BTN_Load_JIG_2_No_17_clicked();

    void on_BTN_Load_JIG_2_No_18_clicked();

    void on_BTN_Load_JIG_2_No_19_clicked();

    void on_BTN_Load_JIG_2_No_20_clicked();

    void on_BTN_Load_JIG_2_No_21_clicked();

    void on_BTN_Load_JIG_2_No_22_clicked();

    void on_BTN_Load_JIG_2_No_23_clicked();

    void on_BTN_Load_JIG_2_No_24_clicked();

    void on_BTN_Load_JIG_2_No_25_clicked();

    void on_BTN_Load_JIG_2_No_26_clicked();

    void on_BTN_Load_JIG_2_No_27_clicked();

    void on_BTN_Load_JIG_2_No_28_clicked();

    void on_BTN_Load_JIG_2_No_29_clicked();

    void on_BTN_Load_JIG_2_No_30_clicked();

    void on_BTN_Load_JIG_2_No_31_clicked();

    void on_BTN_Load_JIG_2_No_32_clicked();

    void on_BTN_Load_JIG_2_No_33_clicked();

    void on_BTN_Load_JIG_2_No_34_clicked();

    void on_BTN_Load_JIG_2_No_35_clicked();

    void on_BTN_Load_JIG_2_No_36_clicked();

    void on_BTN_Load_JIG_2_No_37_clicked();

    void on_BTN_Load_JIG_2_No_38_clicked();

    void on_BTN_Load_JIG_2_No_39_clicked();

    void on_BTN_Load_JIG_2_No_40_clicked();

    void on_BTN_Load_JIG_3_No_1_clicked();

    void on_BTN_Load_JIG_3_No_2_clicked();

    void on_BTN_Load_JIG_3_No_3_clicked();

    void on_BTN_Load_JIG_3_No_4_clicked();

    void on_BTN_Load_JIG_3_No_5_clicked();

    void on_BTN_Load_JIG_3_No_6_clicked();

    void on_BTN_Load_JIG_3_No_7_clicked();

    void on_BTN_Load_JIG_3_No_8_clicked();

    void on_BTN_Load_JIG_3_No_9_clicked();

    void on_BTN_Load_JIG_3_No_10_clicked();

    void on_BTN_Load_JIG_3_No_11_clicked();

    void on_BTN_Load_JIG_3_No_12_clicked();

    void on_BTN_Load_JIG_3_No_13_clicked();

    void on_BTN_Load_JIG_3_No_14_clicked();

    void on_BTN_Load_JIG_3_No_15_clicked();

    void on_BTN_Load_JIG_3_No_16_clicked();

    void on_BTN_Load_JIG_3_No_17_clicked();

    void on_BTN_Load_JIG_3_No_18_clicked();

    void on_BTN_Load_JIG_3_No_19_clicked();

    void on_BTN_Load_JIG_3_No_20_clicked();

    void on_BTN_Load_JIG_3_No_21_clicked();

    void on_BTN_Load_JIG_3_No_22_clicked();

    void on_BTN_Load_JIG_3_No_23_clicked();

    void on_BTN_Load_JIG_3_No_24_clicked();

    void on_BTN_Load_JIG_3_No_25_clicked();

    void on_BTN_Load_JIG_3_No_26_clicked();

    void on_BTN_Load_JIG_3_No_27_clicked();

    void on_BTN_Load_JIG_3_No_28_clicked();

    void on_BTN_Load_JIG_3_No_29_clicked();

    void on_BTN_Load_JIG_3_No_30_clicked();

    void on_BTN_Load_JIG_3_No_31_clicked();

    void on_BTN_Load_JIG_3_No_32_clicked();

    void on_BTN_Load_JIG_3_No_33_clicked();

    void on_BTN_Load_JIG_3_No_34_clicked();

    void on_BTN_Load_JIG_3_No_35_clicked();

    void on_BTN_Load_JIG_3_No_36_clicked();

    void on_BTN_Load_JIG_3_No_37_clicked();

    void on_BTN_Load_JIG_3_No_38_clicked();

    void on_BTN_Load_JIG_3_No_39_clicked();

    void on_BTN_Load_JIG_3_No_40_clicked();

    void on_BTN_mode_JIG_1_clicked();

    void on_BTN_mode_JIG_2_clicked();

    void on_BTN_mode_JIG_3_clicked();

    void on_BTN_FILE_LOAD_JIG_1_clicked();

    void on_BTN_FILE_LOAD_JIG_2_clicked();

    void on_BTN_FILE_LOAD_JIG_3_clicked();

    void on_PB_C_5_Play_clicked();

    void on_PB_C_5_Pause_clicked();

    void on_PB_C_5_Stop_clicked();

    void Load_JIG1_make();

    void Load_JIG2_make();

    void Load_JIG3_make();

    void on_PB_A3C5_back_clicked();

    void on_PB_A_Home_clicked();

    void on_PB_A_RobotPower_clicked();

    void on_PB_B_1_Air_pressed();

    void on_PB_B_1_Air_released();

    void on_LE_B1R0_mm_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B1R0_deg_cursorPositionChanged(int arg1, int arg2);

    void on_LE_B1R0_mm_selectionChanged();

    void on_LE_B1R0_deg_selectionChanged();

    void on_PB_SOKET_clicked();

    void on_PB_REAL_A1_clicked();

    void on_PB_ARM_ACT_A1_clicked();

    void on_PB_ARM_ACT_A2_clicked();

    void on_PB_REAL_A2_clicked();

    void on_PB_D_0_Use_robotfree_clicked();

    void on_PB_D_0_Unuse_robotfree_clicked();

    void on_PB_D_0_Use_Esabweld_Separated_clicked();

    void on_PB_D_0_Unuse_Esabweld_Separated_clicked();

    void on_PB_B_2_n_Fwd_pressed();

    void on_PB_B_2_n_Fwd_released();

    void on_PB_B_2_n_Mod_clicked();

    void on_PB_B_1_Line_Fwd_pressed();

    void on_PB_B_1_Line_Fwd_released();

    void on_PB_B_1_Line_Mod_clicked();

    void on_PB_B_1_Exit_clicked();

    void on_PB_B_1_Play_clicked();

    void on_PB_B_1_Line_Re_clicked();

    void on_PB_B_0_8_clicked();

    void on_PB_A3C7_back_clicked();

    void on_PB_C_7_Play_clicked();

    void on_PB_C_7_Pause_clicked();

    void on_PB_C_7_Stop_clicked();

    void Load_File_1_make();
    void Load_File_2_make();
    void Load_File_3_make();
    void Load_File_4_make();
    void Load_File_5_make();
    void Load_File_6_make();
    void Load_File_7_make();
    void Load_File_8_make();
    void Load_File_9_make();
    void Load_File_10_make();
    void Load_File_All_make();

    void on_PB_icv_sec_plus_clicked();

    void on_PB_icv_sec_minus_clicked();

    void on_PB_icv_x_plus_clicked();

    void on_PB_icv_x_minus_clicked();

    void on_PB_icv_y_plus_clicked();

    void on_PB_icv_y_minus_clicked();

    void on_PB_icv_z_plus_clicked();

    void on_PB_icv_z_minus_clicked();

    void on_PB_arc_set_plus_A_clicked();

    void on_PB_arc_set_minus_A_clicked();

    void on_PB_arc_set_plus_V_clicked();

    void on_PB_arc_set_minus_V_clicked();

    void aicv_set(float aicv_sec,int aicv_type, float aicv_x, float aicv_y, float aicv_z);

    void arc_welding_amphere_plus();

    void arc_welding_amphere_minus();

    void arc_welding_voltage_plus();

    void arc_welding_voltage_minus();

    void on_LE_icv_sec_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_sec_selectionChanged();

    void on_LE_icv_x_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_x_selectionChanged();

    void on_LE_icv_y_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_y_selectionChanged();

    void on_LE_icv_z_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_z_selectionChanged();

    void on_LE_arc_set_A_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_arc_set_A_2_selectionChanged();

    void on_LE_arc_set_V_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_arc_set_V_2_selectionChanged();

    void on_PB_icv_sec_plus_2_clicked();

    void on_PB_icv_sec_minus_2_clicked();

    void on_PB_icv_x_plus_2_clicked();

    void on_PB_icv_x_minus_2_clicked();

    void on_PB_icv_y_plus_2_clicked();

    void on_PB_icv_y_minus_2_clicked();

    void on_PB_icv_z_plus_2_clicked();

    void on_PB_icv_z_minus_2_clicked();

    void on_PB_arc_set_plus_A_2_clicked();

    void on_PB_arc_set_minus_A_2_clicked();

    void on_PB_arc_set_plus_V_2_clicked();

    void on_PB_arc_set_minus_V_2_clicked();

    void aicv_set_2(float aicv_sec,int aicv_type, float aicv_x, float aicv_y, float aicv_z);

    void arc_welding_amphere_plus_2();

    void arc_welding_amphere_minus_2();

    void arc_welding_voltage_plus_2();

    void arc_welding_voltage_minus_2();

    void on_LE_icv_sec_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_sec_2_selectionChanged();

    void on_LE_icv_x_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_x_2_selectionChanged();

    void on_LE_icv_y_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_y_2_selectionChanged();

    void on_LE_icv_z_2_cursorPositionChanged(int arg1, int arg2);

    void on_LE_icv_z_2_selectionChanged();

    void on_LE_arc_set_A_4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_arc_set_A_4_selectionChanged();

    void on_LE_arc_set_V_4_cursorPositionChanged(int arg1, int arg2);

    void on_LE_arc_set_V_4_selectionChanged();

    void on_PB_D_0_Use_weld_play_clicked();

    void on_PB_D_0_Unuse_weld_play_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply=nullptr;       // FTP 때문에 추가
    QFile *file=nullptr;                // FTP 때문에 추가

    QMediaPlayer *mMediaPlayer;
    QVideoWidget *mVideo;

    QString B0R1_input;
    QString B1R1_input;
    QString B2C01_input;
    QString B2C1_input;
    QString D0C0R1_input;
    QString D0C0L1_input;
    QString D0C1R1_input;
    QString D0C2R1_input;
    QString B4R1_input;
    QString C7C0_input;

};

#endif // MAINWINDOW_H
