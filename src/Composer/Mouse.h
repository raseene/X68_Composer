#ifndef	___MOUSE_H___
#define	___MOUSE_H___

#include "common.h"


#define	MS_LEFT		0xff00		// マウス左ボタン
#define	MS_RIGHT	0x00ff		// マウス右ボタン

/************
    マウス
 ************/
typedef struct
{
	int		x;					// カーソル位置
	int		y;
	uint16_t	button;			// ボタンの状態
	uint16_t	trigger;
	uint16_t	release;

	int		_x;					// 実座標
	int		_y;
	int		offset_x;			// オフセット
	int		offset_y;
} Mouse;

extern Mouse	mouse;			// マウス状態


void	Mouse_init(void);					// 初期化
void	Mouse_update(void);					// 稼働
void	Mouse_set_offset(int, int);			// オフセット設定
void	Mouse_draw(void);					// 描画

#endif
