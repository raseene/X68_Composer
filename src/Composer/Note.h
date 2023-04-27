#ifndef	___NOTE_H___
#define	___NOTE_H___

#include "common.h"


// 音符の状態
enum
{
	ON,				// 選択中
	OFF,			// 選択不可
	ACTIVE,			// 選択可
};


/**********
    音符
 **********/
typedef struct
{
	short	state;				// 状態
	short	key;				// 発音する音程
	short	key_data[2];		// 音程データ
	Bool	inner;				// 内音/外音

	uint16_t	sprite;			// ベーススプライト
	uint16_t*	spr_buf;		// スプライトバッファ
} Note;


void	Note_init(Note*, int, short, short, uint16_t*);			// 初期化
void	Note_set_state(Note*, short);							// 状態設定
void	Note_flash(Note*, int);									// 発音フラッシュ
uint8_t	Note_save(Note*);										// 保存用データ
void	Note_load(Note*, uint8_t);								// データより復元

#endif
