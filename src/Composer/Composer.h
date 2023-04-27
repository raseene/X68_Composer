#ifndef	___Composer_H___
#define	___Composer_H___

#include "common.h"


// BG番号
enum
{
	BG_NOTE		= 1,				// 音符
};

// スプライト番号
enum
{
	SPR_CURSOR	= 20/4,				// カーソル
	SPR_LINE,						// ライン
};

// パレット番号
enum
{
	PAL_NOTE	= 1,				// 音符
	PAL_DARK,						// 音符選択不可
	PAL_ON,							// 音符選択中
	PAL_FLASH,						// 音符フラッシュ
	PAL_CURSOR	= PAL_FLASH + 3,	// カーソル
	PAL_LINE,						// ライン
};


// SE番号
enum
{
	SE_CLICK	= 500,
	SE_CANCEL,
};


Bool	Composer_init(char const*);		// 初期化
void	Composer_quit(void);			// 終了
Bool	Composer_update(void);			// 稼働
void	Composer_draw(void);			// 描画

#endif
