//====================================
// �C���N���[�h
//====================================
#include "AD12.h"
//====================================
// �O���[�o���ϐ��̐錾
//====================================


//�@�^�C�}�֘A
static char				ADTimer10;	// AD�ϊ��J�E���g�p

//�@�Z���T�֘A
//  AD�ϊ����ʊi�[
uint16_t            A0_Sen[8];              //AD0�`�����l���̊i�[��
uint16_t            A1_Sen[14];             //AD1�`�����l���̊i�[��

short               Angle0;                 //�T�[�{�Z���^�[�l
short	            sensorG_th = GATE_VAL;	// �Q�[�g�J���������l


///////////////////////////////////////////////////
// ���W���[���� inttrruptAD0
// �����T�v   	AD0�̕ϊ��I�����荞��
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void inttrruptAD0(void) {
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL2,&potentio);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL4,&gatesensor);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL5,&sensor5);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL6,&sensor4);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL7,&sensor3);
}
///////////////////////////////////////////////////
// ���W���[���� inttrruptAD1
// �����T�v   	AD1�̕ϊ��I�����荞��
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void inttrruptAD1(void) {
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL8,&sensor2);
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL9,&sensor1);
}
void sensorthreshold(){
      
}