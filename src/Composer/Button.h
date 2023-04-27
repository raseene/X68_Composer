#ifndef	___BUTTON_H___
#define	___BUTTON_H___

#include "common.h"


/************
    ボタン
 ************/
typedef struct
{
	struct TXFILLPTR	fill;		// 位置・大きさ
	Bool	focus;					// フォーカス
	int		se;						// クリック時のSE
} Button;

void	Button_init(Button*, int, int, int, int);		// 初期化
void	Button_reset(Button*);							// リセット
Bool	Button_update(Button*);							// 稼働


/********************
    パターンボタン
 ********************/
typedef struct
{
	struct TXFILLPTR	fill;		// 位置・大きさ
	uint8_t const*		data;		// パターンデータ
	uint8_t*			vram;		// 描画先
	Bool	focus;					// フォーカス
	Bool	active;					// 押下可能か
	int		se;						// クリック時のSE
} PatButton;

void	PatButton_init(PatButton* , int, int, int, int, uint8_t const*);		// 初期化
Bool	PatButton_update(PatButton*);					// 稼働

#endif
