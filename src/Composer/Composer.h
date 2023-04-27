#ifndef	___Composer_H___
#define	___Composer_H___

#include "common.h"


// BG�ԍ�
enum
{
	BG_NOTE		= 1,				// ����
};

// �X�v���C�g�ԍ�
enum
{
	SPR_CURSOR	= 20/4,				// �J�[�\��
	SPR_LINE,						// ���C��
};

// �p���b�g�ԍ�
enum
{
	PAL_NOTE	= 1,				// ����
	PAL_DARK,						// �����I��s��
	PAL_ON,							// �����I��
	PAL_FLASH,						// �����t���b�V��
	PAL_CURSOR	= PAL_FLASH + 3,	// �J�[�\��
	PAL_LINE,						// ���C��
};


// SE�ԍ�
enum
{
	SE_CLICK	= 500,
	SE_CANCEL,
};


Bool	Composer_init(char const*);		// ������
void	Composer_quit(void);			// �I��
Bool	Composer_update(void);			// �ғ�
void	Composer_draw(void);			// �`��

#endif
