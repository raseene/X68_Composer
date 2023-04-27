/*****************************

		サウンド管理

 *****************************/

#include "Sound.h"
#include "app.h"


/*** サウンドデータ *******/
typedef struct
{
	uint8_t*	data;			// データアドレス
	uint8_t*	bgm;			// BGMアドレス
	uint8_t*	se;				// SEアドレス
} SoundData;

static SoundData*	sound_data = NULL;			// サウンドデータ
static Bool			init_flag = FALSE;			// 初期化フラグ


/************
    初期化
 ************/
Bool	Sound_init(void)
{
	init_flag = FALSE;
	sound_data = NULL;
	if ( zm_ver() & 0xffff ) {
		init_flag = TRUE;
		m_init();							// 音源初期化
		return	TRUE;
	}
	return	FALSE;
}

/**********
    終了
 **********/
void	Sound_quit(void)
{
	if ( init_flag ) {
		m_stop(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		if ( sound_data ) {					// サウンドデータ解放
			SoundData*	p = sound_data;
			while ( p->data ) {
				free(p->data);
				p++;
			}
			free(sound_data);
		}
	}
}


/*****************************************
    サウンドデータ読み込み
			引数	_file = ZMDファイル
			戻り値	読み込み成功か
 *****************************************/
Bool	load_sound(char const** _file)
{
	if ( !init_flag ) {
		return	TRUE;
	}

	int		n = 0;
	{
		char const**	p = _file;

		while ( *p++ ) {
			n++;							// データ数
		}
		sound_data = malloc(sizeof(SoundData)*(n + 1));
	}

	for (int i = 0; i < n; i++) {
		if ( (sound_data[i].data = load_file(_file[i])) == NULL ) {
			return	FALSE;
		}
		sound_data[i].bgm = sound_data[i].data + 7;		// BGM
		uint8_t*	p = sound_data[i].bgm;
		while ( *p++ != 0xff ) ;
		if ( *p == 0xff ) {
			p++;
		}
		sound_data[i].se = p;							// SE
	}
	sound_data[n].data = NULL;
	return	TRUE;
}

/*************************************
    ADPCMデータ読み込み
		引数	_file = ZPDファイル
 *************************************/
Bool	load_adpcm(char const* _file)
{
	if ( init_flag ) {
		if ( m_adpcm_block((char*)_file) ) {
			set_error("ファイル \"%s\" が開けません\n", _file);
			return	FALSE;
		}
	}
	return	TRUE;
}

/**********************************
    BGM再生
		引数	n = サウンド番号
 **********************************/
void	play_bgm(int n)
{
	if ( init_flag ) {
		asm volatile (
			"	movea.l	%0,a1\n"
			"	clr.l	d2\n"
			"	moveq.l	#$11,d1\n"
			"	trap	#3\n"
		:	/* 出力 */
		:	/* 入力 */	"irm" (sound_data[n].bgm)	// 引数 %0
		:	/* 破壊 */	"d0", "d1", "d2", "a1"
		);
	}
}

/************
   BGM停止
 ************/
void	stop_bgm(void)
{
	if ( init_flag ) {
		m_stop(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}

/***********************************
   BGMフェードアウト
		引数	_speed = スピード
 ***********************************/
void	fadeout_bgm(int _speed)
{
	if ( init_flag ) {
		m_fadeout(_speed);
	}
}

/**********************************
    SE再生
		引数	n = サウンド番号
 **********************************/
void	play_se(int n)
{
	if ( init_flag ) {
		static int	track = 5;

		sound_data[n].se[7] = (uint8_t)(track - 1);
		asm volatile (
			"	movea.l	%0,a1\n"
			"	move.l	%1,d2\n"
			"	moveq.l	#$12,d1\n"
			"	trap	#3\n"
		:	/* 出力 */
		:	/* 入力 */	"irm" (sound_data[n].se),	// 引数 %0
						"irm" (track)				// 引数 %1
		:	/* 破壊 */	"d0", "d1", "d2", "a1"
		);

		track = (track % 4) + 5;
	}
}

/********************************
    PCM再生
		引数	n = ノート番号
 ********************************/
void	play_pcm(int n)
{
	if ( init_flag ) {
		m_pcmplay(n, 3, 4);
	}
}

