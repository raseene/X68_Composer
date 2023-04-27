#ifndef	___NOTE_H___
#define	___NOTE_H___

#include "common.h"


// �����̏��
enum
{
	ON,				// �I��
	OFF,			// �I��s��
	ACTIVE,			// �I����
};


/**********
    ����
 **********/
typedef struct
{
	short	state;				// ���
	short	key;				// �������鉹��
	short	key_data[2];		// �����f�[�^
	Bool	inner;				// ����/�O��

	uint16_t	sprite;			// �x�[�X�X�v���C�g
	uint16_t*	spr_buf;		// �X�v���C�g�o�b�t�@
} Note;


void	Note_init(Note*, int, short, short, uint16_t*);			// ������
void	Note_set_state(Note*, short);							// ��Ԑݒ�
void	Note_flash(Note*, int);									// �����t���b�V��
uint8_t	Note_save(Note*);										// �ۑ��p�f�[�^
void	Note_load(Note*, uint8_t);								// �f�[�^��蕜��

#endif
