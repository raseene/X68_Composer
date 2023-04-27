#ifndef	___MOUSE_H___
#define	___MOUSE_H___

#include "common.h"


#define	MS_LEFT		0xff00		// �}�E�X���{�^��
#define	MS_RIGHT	0x00ff		// �}�E�X�E�{�^��

/************
    �}�E�X
 ************/
typedef struct
{
	int		x;					// �J�[�\���ʒu
	int		y;
	uint16_t	button;			// �{�^���̏��
	uint16_t	trigger;
	uint16_t	release;

	int		_x;					// �����W
	int		_y;
	int		offset_x;			// �I�t�Z�b�g
	int		offset_y;
} Mouse;

extern Mouse	mouse;			// �}�E�X���


void	Mouse_init(void);					// ������
void	Mouse_update(void);					// �ғ�
void	Mouse_set_offset(int, int);			// �I�t�Z�b�g�ݒ�
void	Mouse_draw(void);					// �`��

#endif
