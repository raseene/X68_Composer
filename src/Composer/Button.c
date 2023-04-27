/*****************************

		ボタン

 *****************************/

#include "Button.h"
#include "Mouse.h"
#include "Composer.h"
#include "Sound.h"


/*********************************
    初期化
		引数	_x, _y = 位置
				_w, _h = 大きさ
 *********************************/
void	Button_init(Button* this, int _x, int _y, int _w, int _h)
{
	this->fill.vram_page = 2;
	this->fill.x  = _x;
	this->fill.y  = _y;
	this->fill.x1 = _w;
	this->fill.y1 = _h;
	this->fill.fill_patn = 0x55aa;

	TXFILL(&this->fill);
	this->fill.vram_page = 3;

	this->focus = FALSE;
	this->se    = SE_CLICK;
}

/**************
    リセット
 **************/
void	Button_reset(Button* this)
{
	if ( this->focus ) {
		this->focus = FALSE;
		this->fill.fill_patn = 0x0000;
		TXFILL(&this->fill);
	}
}

/******************************
    稼働
		戻り値	決定されたか
 ******************************/
Bool	Button_update(Button* this)
{
	struct TXFILLPTR*	fill = &this->fill;

	if ( (mouse.y >= fill->y) && (mouse.y < fill->y + fill->y1) && (mouse.x >= fill->x) && (mouse.x < fill->x + fill->x1) ) {
		if ( !this->focus ) {
			if ( !(mouse.button & MS_LEFT) ) {
				this->focus = TRUE;
				fill->fill_patn = 0x55aa;
				TXFILL(fill);
			}
		}
		else if ( mouse.trigger & MS_LEFT ) {
			play_pcm(this->se);
		}
		else if ( mouse.release & MS_LEFT ) {
			return	TRUE;
		}
	}
	else {
		Button_reset(this);
	}
	return	FALSE;
}


void	draw_mono_pattern(int, int, uint8_t const*, uint8_t*);			// 1色パターン描画

/*****************************************
    初期化
		引数	_x, _y = 位置
				_w, _h = 大きさ
				_data  = パターンデータ
 *****************************************/
void	PatButton_init(PatButton* this, int _x, int _y, int _w, int _h, uint8_t const* _data)
{
	uint8_t*	vram = (uint8_t*)0xe40000 + _x/8 + _y*0x80;

	draw_mono_pattern(_w/8, _h, _data, vram);
	this->vram = vram + 0x20000;
	this->data = _data;

	this->fill.vram_page = 3;
	this->fill.x  = _x;
	this->fill.y  = _y;
	this->fill.x1 = _w;
	this->fill.y1 = _h;
	this->fill.fill_patn = 0;

	this->focus  = FALSE;
	this->active = TRUE;
	this->se     = SE_CLICK;
}

/******************************
    稼働
		戻り値	決定されたか
 ******************************/
Bool	PatButton_update(PatButton* this)
{
	struct TXFILLPTR*	fill = &this->fill;
	Bool	focus = ((mouse.y >= fill->y) && (mouse.y < fill->y + fill->y1) && (mouse.x >= fill->x) && (mouse.x < fill->x + fill->x1)),
			ret = FALSE;

	if ( this->focus ) {
		if ( focus && !(mouse.button & MS_LEFT) ) {
			focus = FALSE;
			ret = TRUE;
		}
	}
	else if ( focus ) {
		if ( this->active && (mouse.trigger & MS_LEFT) ) {
			play_pcm(this->se);
		}
		else {
			focus = FALSE;
		}
	}

	if ( focus ) {
		if ( !this->focus ) {
			this->focus = TRUE;
			draw_mono_pattern(fill->x1/8, fill->y1, this->data, this->vram);
		}
	}
	else {
		if ( this->focus ) {
			this->focus = FALSE;
			TXFILL(fill);
		}
	}

	return	ret;
}

