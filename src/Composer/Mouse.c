/*****************************

		マウス処理

 *****************************/

#include "Mouse.h"
#include "Composer.h"


Mouse	mouse;			// マウス状態

/************
    初期化
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
    稼働
 **********/
void	Mouse_update(void)
{
	uint16_t	_btn = (uint16_t)MS_GETDT();			// マウスボタン

	mouse.trigger = _btn & ~mouse.button;
	mouse.release = ~_btn & mouse.button;
	mouse.button = _btn;

	int		t = MS_CURGT();								// マウスカーソル座標

	mouse._x = t >> 16;
	mouse._y = t & 0xffff;
	mouse.x = mouse._x + mouse.offset_x;
	mouse.y = mouse._y + mouse.offset_y;
}

/*************************************
    オフセット設定
		引数	x, y = オフセット値
 *************************************/
void	Mouse_set_offset(int x, int y)
{
	mouse.offset_x = x;
	mouse.offset_y = y;
}

/**********
    描画
 **********/
void	Mouse_draw(void)
{
	SP_REGST(0 + (1 << 0x1f), mouse._x + 16, mouse._y + 16, SPR_CURSOR + (PAL_CURSOR << 8), 3);			// マウスカーソル
}

