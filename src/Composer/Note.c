/**************************

		音符

 **************************/

#include "Note.h"
#include "Composer.h"


/********************************************
    初期化
		引数	_time = 拍
				_key0, _key1 = 音程
				_buf  = スプライトバッファ
 ********************************************/
void	Note_init(Note* this, int _time, short _key0, short _key1, uint16_t* _buf)
{
	this->key_data[0] = this->key = _key0;
	this->key_data[1] = _key1;
	if ( _key1 == 0 ) {								// 内音
		this->inner = TRUE;
		this->state = ACTIVE;
	}
	else {											// 外音
		this->inner = FALSE;
		this->state = OFF;
	}
	this->spr_buf = _buf;							// スプライトバッファ

	this->sprite = BG_NOTE + (_time/8 % 2) + (_time % 2)*4;
	if ( !this->inner ) {							// 外音
		this->sprite += 2;
	}

	Note_set_state(this, this->state);				// スプライト設定
}

/*******************************
    状態設定
		引数	_state = 状態
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

	this->spr_buf[0]   = spr;						// スプライト設定
	this->spr_buf[4*8] = spr + 10;
}

/****************************************
    発音フラッシュ
		引数	t = フラッシュカウンタ
 ****************************************/
void	Note_flash(Note* this, int t)
{
	if ( this->state == ON ) {
		uint16_t	spr = this->sprite;

		spr |= (t < 2) ? ((PAL_FLASH + t) << 8) : (PAL_ON << 8);
		this->spr_buf[0]   = spr;					// スプライト設定
		this->spr_buf[4*8] = spr + 10;
	}
}


/************************
    保存用データ
		戻り値	データ
 ************************/
uint8_t		Note_save(Note* this)
{
	return	(uint8_t)((this->key << 2) | this->state);
}

/********************
    データより復元
 ********************/
void	Note_load(Note* this, uint8_t data)
{
	this->key = (short)(data >> 2);
	Note_set_state(this, (short)(data & 0x3));
}

