#ifndef	___BUTTON_H___
#define	___BUTTON_H___

#include "common.h"


/************
    �{�^��
 ************/
typedef struct
{
	struct TXFILLPTR	fill;		// �ʒu�E�傫��
	Bool	focus;					// �t�H�[�J�X
	int		se;						// �N���b�N����SE
} Button;

void	Button_init(Button*, int, int, int, int);		// ������
void	Button_reset(Button*);							// ���Z�b�g
Bool	Button_update(Button*);							// �ғ�


/********************
    �p�^�[���{�^��
 ********************/
typedef struct
{
	struct TXFILLPTR	fill;		// �ʒu�E�傫��
	uint8_t const*		data;		// �p�^�[���f�[�^
	uint8_t*			vram;		// �`���
	Bool	focus;					// �t�H�[�J�X
	Bool	active;					// �����\��
	int		se;						// �N���b�N����SE
} PatButton;

void	PatButton_init(PatButton* , int, int, int, int, uint8_t const*);		// ������
Bool	PatButton_update(PatButton*);					// �ғ�

#endif
