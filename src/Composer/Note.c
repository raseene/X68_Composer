/**************************

		����

 **************************/

#include "Note.h"
#include "Composer.h"


/********************************************
    ������
		����	_time = ��
				_key0, _key1 = ����
				_buf  = �X�v���C�g�o�b�t�@
 ********************************************/
void	Note_init(Note* this, int _time, short _key0, short _key1, uint16_t* _buf)
{
	this->key_data[0] = this->key = _key0;
	this->key_data[1] = _key1;
	if ( _key1 == 0 ) {								// ����
		this->inner = TRUE;
		this->state = ACTIVE;
	}
	else {											// �O��
		this->inner = FALSE;
		this->state = OFF;
	}
	this->spr_buf = _buf;							// �X�v���C�g�o�b�t�@

	this->sprite = BG_NOTE + (_time/8 % 2) + (_time % 2)*4;
	if ( !this->inner ) {							// �O��
		this->sprite += 2;
	}

	Note_set_state(this, this->state);				// �X�v���C�g�ݒ�
}

/*******************************
    ��Ԑݒ�
		����	_state = ���
 *******************************/
void	Note_set_state(Note* this, short _state)
{
	this->state = _state;

	static const
	uint16_t	palet[] =
	{
		PAL_ON << 8,			// ON
		PAL_DARK << 8,			// OFF
		PAL_NOTE << 8,			// ACTIVE
	};

	uint16_t	spr = this->sprite | palet[_state];

	this->spr_buf[0]   = spr;						// �X�v���C�g�ݒ�
	this->spr_buf[4*8] = spr + 10;
}

/****************************************
    �����t���b�V��
		����	t = �t���b�V���J�E���^
 ****************************************/
void	Note_flash(Note* this, int t)
{
	if ( this->state == ON ) {
		uint16_t	spr = this->sprite;

		spr |= (t < 2) ? ((PAL_FLASH + t) << 8) : (PAL_ON << 8);
		this->spr_buf[0]   = spr;					// �X�v���C�g�ݒ�
		this->spr_buf[4*8] = spr + 10;
	}
}


/************************
    �ۑ��p�f�[�^
		�߂�l	�f�[�^
 ************************/
uint8_t		Note_save(Note* this)
{
	return	(uint8_t)((this->key << 2) | this->state);
}

/********************
    �f�[�^��蕜��
 ********************/
void	Note_load(Note* this, uint8_t data)
{
	this->key = (short)(data >> 2);
	Note_set_state(this, (short)(data & 0x3));
}

