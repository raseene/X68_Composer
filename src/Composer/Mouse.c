/*****************************

		�}�E�X����

 *****************************/

#include "Mouse.h"
#include "Composer.h"


Mouse	mouse;			// �}�E�X���

/************
    ������
 ************/
void	Mouse_init(void)
{
	mouse.offset_x = 0;
	mouse.offset_y = 0;
	mouse.button   = 0;
	mouse.trigger  = 0;
	mouse.release  = 0;
}

/**********
    �ғ�
 **********/
void	Mouse_update(void)
{
	uint16_t	_btn = (uint16_t)MS_GETDT();			// �}�E�X�{�^��

	mouse.trigger = _btn & ~mouse.button;
	mouse.release = ~_btn & mouse.button;
	mouse.button = _btn;

	int		t = MS_CURGT();								// �}�E�X�J�[�\�����W

	mouse._x = t >> 16;
	mouse._y = t & 0xffff;
	mouse.x = mouse._x + mouse.offset_x;
	mouse.y = mouse._y + mouse.offset_y;
}

/*************************************
    �I�t�Z�b�g�ݒ�
		����	x, y = �I�t�Z�b�g�l
 *************************************/
void	Mouse_set_offset(int x, int y)
{
	mouse.offset_x = x;
	mouse.offset_y = y;
}

/**********
    �`��
 **********/
void	Mouse_draw(void)
{
	SP_REGST(0 + (1 << 0x1f), mouse._x + 16, mouse._y + 16, SPR_CURSOR + (PAL_CURSOR << 8), 3);			// �}�E�X�J�[�\��
}

