/*****************************

		作曲メイン

 *****************************/

#include "Composer.h"
#include "app.h"
#include "Note.h"
#include "Sound.h"
#include "Mouse.h"
#include "Button.h"


// コード
enum
{
	C = 0, C7,
	D, D7, Dm, Dm7,
	E, E7, Em, Em7,
	F, F7, Fm,
	G, G7, Gm,
	A7, Am, Am7, Ais, Ais7,
	Hm,
};

static const
short	chord_data[][6][2] =				// コード構成音
{
	{{ 7}, { 9, 11}, {12}, {14, 14}, {16}, {17, 17}},			// C
	{{ 7}, {10},     {12}, {14, 14}, {16}, {17, 17}},			// C7
	{{ 6}, { 7,  7}, { 9}, {11, 12}, {14}, {16, 16}},			// D
	{{ 6}, { 7,  7}, { 9}, {12},     {14}, {16, 16}},			// D7
	{{ 5}, { 7,  7}, { 9}, {11, 12}, {14}, {16, 16}},			// Dm
	{{ 5}, { 7,  7}, { 9}, {12},     {14}, {16, 16}},			// Dm7
	{{ 8}, { 9,  9}, {11}, {12, 14}, {16}, {17, 17}},			// E
	{{ 8}, { 9,  9}, {11}, {14},     {16}, {17, 17}},			// E7
	{{ 7}, { 9,  9}, {11}, {12, 14}, {16}, {17, 17}},			// Em
	{{ 7}, { 9,  9}, {11}, {14},     {16}, {17, 17}},			// Em7
	{{ 9}, {11, 11}, {12}, {14, 16}, {17}, {19, 19}},			// F
	{{ 9}, {11, 11}, {12}, {15},     {17}, {19, 19}},			// F7
	{{ 8}, {11, 11}, {12}, {14, 16}, {17}, {19, 19}},			// Fm
	{{ 7}, { 9,  9}, {11}, {12, 12}, {14}, {16, 17}},			// G
	{{ 7}, { 9,  9}, {11}, {12, 12}, {14}, {17}},				// G7
	{{ 7}, { 9,  9}, {10}, {12, 12}, {14}, {16, 17}},			// Gm
	{{ 9}, {11, 11}, {13}, {14, 14}, {16}, {19}},				// A7
	{{ 9}, {11, 11}, {12}, {14, 14}, {16}, {17, 19}},			// Am
	{{ 9}, {11, 11}, {12}, {14, 14}, {16}, {19}},				// Am7
	{{ 5}, { 7,  7}, {10}, {11, 12}, {14}, {16, 16}},			// A#
	{{ 5}, { 8},     {10}, {11, 12}, {14}, {16, 16}},			// A#7
	{{ 6}, { 7,  8}, {11}, {12, 12}, {14}, {16, 16}},			// Bm
};

static const
char*	chord_name[] =						// コード名
{
	"C", "C\xf4\x01",
	"D", "D\xf4\x01", "Dm", "Dm\xf4\x01",
	"E", "E\xf4\x01", "Em", "Em\xf4\x01",
	"F", "F\xf4\x01", "Fm",
	"G", "G\xf4\x01", "Gm",
	"A\xf4\x01", "Am", "Am\xf4\x01", "A#", "A#\xf4\x01",
	"Bm",
};


static const
short	chord_progression[][4] = 			// コード進行
{
	{C, F, G7, C},
	{C, C7, F, Fm},
	{C, Gm, F, Fm},
	{C, D, F, C},
	{C7, C7, F7, F7},
	{Dm7, G7, Em7, Am7},
	{F, G, Am, Am},
	{Am, G, F, E},
	{Am, C, D, E},
	{Am, Ais7, Am, Ais7},
	{Am, Am, Am, Am},
	{Am, Dm, E7, Am},
	{Am, F, G, C},
};

static const
char*	progression_name[] =				// コード進行名
{
	"  C""\xf4\x00"" F""\xf4\x00"" G""\xf4\x01""""\xf4\x00""C  ",
	"  C""\xf4\x00"" C""\xf4\x01""""\xf4\x00""F""\xf4\x00"" Fm ",
	"  C""\xf4\x00"" Gm""\xf4\x00""F""\xf4\x00"" Fm ",
	"  C""\xf4\x00"" D""\xf4\x00"" F""\xf4\x00"" C  ",
	"  C""\xf4\x01""""\xf4\x00""C""\xf4\x01""""\xf4\x00""F""\xf4\x01""""\xf4\x00""F""\xf4\x01"" ",
	"Dm""\xf4\x01""""\xf4\x00""G""\xf4\x01""""\xf4\x00""Em""\xf4\x01""""\xf4\x00""Am""\xf4\x01""",
	"  F""\xf4\x00"" G""\xf4\x00"" Am""\xf4\x00""Am ",
	"  Am""\xf4\x00""G""\xf4\x00"" F""\xf4\x00"" E  ",
	"  Am""\xf4\x00""C""\xf4\x00"" D""\xf4\x00"" E  ",
	" Am""\xf4\x00""A#""\xf4\x01""""\xf4\x00""Am""\xf4\x00""A#""\xf4\x01""",
	"  Am""\xf4\x00""Am""\xf4\x00""Am""\xf4\x00""Am ",
	"  Am""\xf4\x00""Dm""\xf4\x00""E""\xf4\x01""""\xf4\x00""Am ",
	"  Am""\xf4\x00""F""\xf4\x00"" G""\xf4\x00"" C  ",
	"ランダムで選択",
};


static const
short	bass_pattern[][8] =					// ベースパターン
{
	{ 0,-1, 0,-1, 0,-1, 0,-1},
	{ 0,-1, 2,-1, 4,-1, 6,-1},
	{ 2,-1, 0,-1, 2,-1, 0,-1},
	{ 0, 2, 0, 2, 0, 2, 0, 2},
	{ 2, 4, 6, 8, 2, 4, 6, 8},
	{ 0,-1,-1,-1, 0,-1,-1,-1},
};


static const
int		tempo_speed[] =						// テンポ別速度
{
	10, 12, 15, 20, 24,
};

static const
char*	tempo_text[] =						// テンポ表示文字列
{
	"138", "166", "2O8", "277", "332",
};



// 実行段階
enum
{
	PHASE_CHORD,			// コード進行選択
	PHASE_BASS,				// ベースパターン選択
	PHASE_PLAY,				// 演奏
};

static int	phase;			// 実行段階
static int	cnt;			// カウンタ
static int	tempo;			// テンポ
static int	slide_cnt;		// 画面スライド用カウンタ
static int	exit_cnt;		// 移行カウンタ
static int	mute_cnt;		// 消音カウンタ

static int	prog_num;		// コード進行番号
static int	bass_num;		// ベースパターン番号
static int	play_num;		// 演奏中の番号

static Note			note[4*8][11];			// 音符

static uint16_t		bg_note[11*2][4*8];		// 音符BG
static uint8_t		zmd_tone[8][16];		// 音程ZMDデータ
static uint8_t*		pic_bass;				// ベースパターン画像
static uint8_t		save_header;			// 保存データヘッダー


// ボタン
enum
{
	BTN_CHORD	= 0,				// コード進行
	BTN_BASS	= BTN_CHORD + 14,	// ベースバターン
	BTN_MAX		= BTN_BASS + 7,

	BTN_EXIT	= 0,				// 終了

	BTN_DOWN	= 0,				// テンポ ←
	BTN_UP,							// テンポ →
	BTN_CANCEL,						// 戻る
	PAT_BTN_MAX,
};

static Button		button[BTN_MAX];		// ボタン
static PatButton	pat_button[PAT_BTN_MAX];



static Bool		init_sound(void);					// サウンド初期化
static void		init_select(void);					// 選択画面初期化
static Bool		init_play(uint8_t const* data);		// 演奏初期化

/*****************************************
    初期化
		引数	_dir = セーブファイル名
		戻り値	初期化成功か
 *****************************************/
Bool	Composer_init(char const* name)
{
int		apic_load(const char*, int, int);		// PICファイル読み込み

	clear_text();								// テキスト画面クリア
	B_LOCATE(9, 7);
	puts("Now Loading...");

	B_WPOKE((UWORD*)0xe82600, 0x0020);			// グラフィック画面OFF
	B_WPOKE((UWORD*)0xe82500, 0x06e4);			// プライオリティ設定

	if ( apic_load("GRAPHIC\\BACK.PIC", 0, 0) ) {								// 背景PIC描画
//		set_error("ファイル \"GRAPHIC\\BACK.PIC\" が開けません\n");
//		return	FALSE;
	}

	if ( !load_sprite("GRAPHIC\\COMPOSER.SP", "GRAPHIC\\COMPOSER.PAL") ) {		// スプライト読み込み
		return	FALSE;
	}
	BGCTRLST(1, 1, 1);							// BG画面クリア
	BGSCRLST(1 + (1 << 31), 0, 0x400 - 2);		// BG位置設定

	if ( (pic_bass = load_file("GRAPHIC\\BASSPAT.DAT")) == NULL ) {				// ベースパターン画像
		return	FALSE;
	}

	{											// 外字設定
		static const
		uint8_t		font_hyphen[16] =
		{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011000,
			0b00011000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
		},
		font_7[16] =
		{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b01111000,
			0b00001000,
			0b00010000,
			0b00010000,
			0b00010000,
			0b00100000,
			0b00100000,
			0b00000000,
			0b00000000,
		};

		DEFCHR(8, 0xf400, (UBYTE*)&font_hyphen[0]);
		DEFCHR(8, 0xf401, (UBYTE*)&font_7[0]);
	}
	if ( !init_sound() ) {						// サウンド初期化
		return	FALSE;
	}
	Mouse_init();								// マウス初期化


	B_WPOKE((UWORD*)0xe82600, 0x0000);			// テキスト画面OFF
	CONTRAST(0);
	{											// テキストパレット設定
		static const
		uint16_t	text_palet[] =
		{
			RGB(30, 29, 28),
								RGB(1, 1, 1),
			RGB(30, 29, 28),
												RGB(20, 14, 0),
			RGB(30, 29, 28),
								RGB(1, 1, 1),
			RGB(30, 29, 28),
																			RGB(8, 14, 20),
																			RGB(0,  8, 16),
																			RGB(20, 14, 8),
																			RGB(16,  8, 0),
												RGB(31, 30, 8),
			RGB(30, 29, 28),
								RGB(1, 1, 1),
			RGB(30, 29, 28),
		};

		for (int i = 0; i < 15; i++) {
			TPALET2(1 + i, text_palet[i]);
		}
	}


	if ( name == NULL ) {
		tempo = 2;
		save_header = 0xff;						// 保存データヘッダー
		init_select();							// 選択画面初期化
	}
	else {
		uint8_t*	data = load_file(name);

		if ( data == NULL ) {
			return	FALSE;
		}
		if ( !init_play(data) ) {				// 演奏画面初期化
			free(data);
			return	FALSE;
		}
		free(data);
	}
	B_WPOKE((UWORD*)0xe82600, 0x006f);			// 画面ON

	return	TRUE;
}

/********************
    サウンド初期化
 ********************/
static
Bool	init_sound(void)
{
	static const
	char*	sound_name[] =				// サウンドファイル
	{
		"SOUND\\TONE.ZMD",
		NULL
	};

	if ( !load_sound(sound_name) || !load_adpcm("SOUND\\COMPOSER.ZPD") ) {		// サウンドデータ読み込み
		return	FALSE;
	}

	static const
	uint8_t		zmd_data[16] =
	{
		0, 1,							// トラック数
		0x00, 0x00, 0x00, 0x02,			// 相対アドレス
		0x00, 0,						// チャンネル番号
		0xa0, 1,						// 音色
		0xb6, 127 - 120,				// 音量
		0x30, 0x30, 0x30,				// 音程
		0xff,
	};

	uint8_t*		p0 = &zmd_tone[0][0];		// 音程ZMDデータ
	uint8_t const*	p1;

	for (uint8_t i = 0; i < 8; i++) {
		p1 = &zmd_data[0];
		for (int j = 0; j < 16; j++) {
			*p0++ = *p1++;
		}
		zmd_tone[i][7] = i;						// チャンネル番号
	}

	play_bgm(0);								// 音色設定
	return	TRUE;
}

/**********
    終了
 **********/
void	Composer_quit(void)
{
	free(pic_bass);
}


void	draw_text(int, int, char const*);		// テキスト描画

/****************
    テンポ描画
 ****************/
static
void	set_tempo(void)
{
	draw_text((phase == PHASE_PLAY) ? 7 : (32 + 7), 12, tempo_text[tempo]);
	pat_button[BTN_DOWN].active = (tempo > 0);
	pat_button[BTN_UP].active = (tempo < 5 - 1);
	cnt -= cnt % tempo_speed[tempo];
	m_tempo((int)(55.46*30)*tempo_speed[tempo]/240);
}

/************************
    テンポ変更UI初期化
 ************************/
static
void	init_tempo(void)
{
	static const
	uint8_t		pat_down[24*3] =				// テンポダウン
	{
		0b00000000, 0b00000000, 0b11000000,
		0b00000000, 0b00000001, 0b11100000,
		0b00000000, 0b00000011, 0b10100000,
		0b00000000, 0b00000111, 0b10100000,
		0b00000000, 0b00001111, 0b10100000,
		0b00000000, 0b00011111, 0b10100000,
		0b00000000, 0b00111111, 0b10100000,
		0b00000000, 0b01111111, 0b10100000,
		0b00000000, 0b11111111, 0b10100000,
		0b00000001, 0b11111111, 0b10100000,
		0b00000011, 0b11111111, 0b10100000,
		0b00000111, 0b11111111, 0b10100000,
		0b00000110, 0b11111111, 0b10100000,
		0b00000011, 0b01111111, 0b10100000,
		0b00000001, 0b10111111, 0b10100000,
		0b00000000, 0b11011111, 0b10100000,
		0b00000000, 0b01101111, 0b10100000,
		0b00000000, 0b00110111, 0b10100000,
		0b00000000, 0b00011011, 0b10100000,
		0b00000000, 0b00001101, 0b10100000,
		0b00000000, 0b00000110, 0b10100000,
		0b00000000, 0b00000011, 0b01100000,
		0b00000000, 0b00000001, 0b11100000,
		0b00000000, 0b00000000, 0b11000000,
	};

	static const
	uint8_t		pat_up[24*3] =					// テンポアップ
	{
		0b00000011, 0b00000000, 0b00000000,
		0b00000111, 0b10000000, 0b00000000,
		0b00000110, 0b11000000, 0b00000000,
		0b00000101, 0b01100000, 0b00000000,
		0b00000101, 0b10110000, 0b00000000,
		0b00000101, 0b11011000, 0b00000000,
		0b00000101, 0b11101100, 0b00000000,
		0b00000101, 0b11110110, 0b00000000,
		0b00000101, 0b11111011, 0b00000000,
		0b00000101, 0b11111101, 0b10000000,
		0b00000101, 0b11111110, 0b11000000,
		0b00000101, 0b11111111, 0b01100000,
		0b00000101, 0b11111111, 0b11100000,
		0b00000101, 0b11111111, 0b11000000,
		0b00000101, 0b11111111, 0b10000000,
		0b00000101, 0b11111111, 0b00000000,
		0b00000101, 0b11111110, 0b00000000,
		0b00000101, 0b11111100, 0b00000000,
		0b00000101, 0b11111000, 0b00000000,
		0b00000101, 0b11110000, 0b00000000,
		0b00000101, 0b11100000, 0b00000000,
		0b00000101, 0b11000000, 0b00000000,
		0b00000111, 0b10000000, 0b00000000,
		0b00000011, 0b00000000, 0b00000000,
	};

	int		x = (phase == PHASE_PLAY) ? 0 : 32;

	PatButton_init(&pat_button[BTN_DOWN], x*8 + 0*8, 8, 3*8, 24, &pat_down[0]);
	PatButton_init(&pat_button[BTN_UP], x*8 + 10*8, 8, 3*8, 24, &pat_up[0]);

	draw_text(x + 3, 12, "♪=");
	set_tempo();
}

/****************
    テンポ変更
 ****************/
static
void	control_tempo(void)
{
	if ( PatButton_update(&pat_button[BTN_DOWN]) ) {
		tempo--;
		set_tempo();
	}
	else if ( PatButton_update(&pat_button[BTN_UP]) ) {
		tempo++;
		set_tempo();
	}
}


/*****************************************
    音符再生
		引数	key = 音程
				vol = 音量（127：最大）
 *****************************************/
static
void	play_note(short key, short vol)
{
	static uint8_t	track = 0;

	uint8_t*	p = &zmd_tone[track][0];

	p[11] = (uint8_t)(127 - vol);				// 音量
	p[12] = (uint8_t)(0x30 + key);				// 音程
	asm volatile (
		"	movea.l	%0,a1\n"
		"	move.l	%1,d2\n"
		"	moveq.l	#$12,d1\n"
		"	trap	#3\n"
	:	/* 出力 */
	:	/* 入力 */	"irm" (p),					// 引数 %0
					"irm" (track + 1)			// 引数 %1
	:	/* 破壊 */	"d0", "d1", "d2", "a1"
	);
	track = ++track % 8;
}


/********************
    選択画面初期化
 ********************/
static
void	init_select(void)
{
void	draw_pattern(int, int, uint8_t const*);			// パターン描画

	phase		= PHASE_CHORD;
	slide_cnt	= -1;
	exit_cnt	= 0;
	play_num	= -1;

	m_tempo(120);


	clear_text();								// テキスト画面クリア
	BGTEXTCL(1, 0x100);							// BG消去
	for (int i = 0; i < 12; i++) {				// スプライト消去
		SP_REGST(i + (1 + (1 << 0x1f)), 0, 0, 0, 0);
	}

	draw_text(8, 20, "コード進行 選択");
	for (int i = 0; i < 14; i++) {				// コード進行ボタン
		int		x = 1 + (i % 2)*16,
				y = 52 + (i/2)*29;

		draw_text(x, y, progression_name[i]);
		Button_init(&button[BTN_CHORD + i], x*8 - 4, y + 3, 120, 16);
	}


	draw_text(38, 48, "ベースパターン 選択");
	for (int i = 0; i < 6; i++) {				// ベースパターンボタン
		int		x = 32 + 2 + (i % 3)*10,
				y = 80 + (i/3)*72;

		draw_pattern(x, y, pic_bass + i*(64/8*48*2));
		Button_init(&button[BTN_BASS + i], x*8 - 4, y - 4, 72, 56);
	}
	draw_text(56, 224, "無し");
	Button_init(&button[BTN_BASS + 6], 54*8, 218, 64, 28);

	init_tempo();								// テンポ変更UI初期化

	static const
	uint8_t		pat_arrow[22*3] =				// 戻るボタン
	{
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b01111000, 0b00000000,
		0b00000000, 0b11011000, 0b00000000,
		0b00000001, 0b10101000, 0b00000000,
		0b00000011, 0b01101000, 0b00000000,
		0b00000110, 0b11101111, 0b11111110,
		0b00001101, 0b11100000, 0b00000011,
		0b00011011, 0b11111111, 0b11111101,
		0b00110111, 0b11111111, 0b11111101,
		0b01101111, 0b11111111, 0b11111101,
		0b11011111, 0b11111111, 0b11111101,
		0b11011111, 0b11111111, 0b11111101,
		0b01101111, 0b11111111, 0b11111101,
		0b00110111, 0b11111111, 0b11111101,
		0b00011011, 0b11111111, 0b11111101,
		0b00001101, 0b11100000, 0b00000011,
		0b00000110, 0b11101111, 0b11111110,
		0b00000011, 0b01101000, 0b00000000,
		0b00000001, 0b10101000, 0b00000000,
		0b00000000, 0b11011000, 0b00000000,
		0b00000000, 0b01111000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
	};

	PatButton_init(&pat_button[BTN_CANCEL], 256 + 1*8, 222, 3*8, 22, &pat_arrow[0]);
	pat_button[BTN_CANCEL].se = SE_CANCEL;


	fade_in();
}


/********************
    コード進行選択
 ********************/
static
void	update_chord(void)
{
	if ( slide_cnt > 0 ) {						// 移行中
		if ( --slide_cnt == 0 ) {
			Mouse_set_offset(0, 0);
		}
	}
	else {
		slide_cnt = -1;

		int		t = -1;

		prog_num = -1;
		for (int i = 0; i < 14; i++) {			// コード進行選択ボタン
			if ( Button_update(&button[BTN_CHORD + i]) ) {
				prog_num = i;
				break;
			}
			if ( button[BTN_CHORD + i].focus ) {
				t = i;
			}
		}
		if ( prog_num >= 0 ) {
			if ( prog_num == 13 ) {				// ランダム選択
				prog_num = rand() % 13;
			}
			phase		= PHASE_BASS;
			play_num	= -1;
			slide_cnt	= 7;

			for (int i = 0; i < 7; i++) {
				Button_reset(&button[BTN_BASS + i]);
			}
			m_tempo((int)(55.46*30)*tempo_speed[tempo]/240);
		}
		else if ( play_num != t ) {
			play_num = t;
			cnt = 4*4*7 - 6;
		}

		if ( (play_num >= 0) && (play_num < 13) ) {			// コード進行選択中
			if ( modu(cnt, 7) == 0 ) {						// コード音程再生
				int		i = (divs(cnt, 7) % 4) + 0;

				play_note(chord_data[chord_progression[play_num][divs(cnt, 4*7)]][modu(i*2, 6)][0] + divs(i, 3)*12, 112);
			}
			cnt = modu(++cnt, 4*4*7);
		}
	}
}


/************************
    ベースパターン選択
 ************************/
static
void	update_bass(void)
{
	if ( exit_cnt > 0 ) {
		if ( --exit_cnt == 0 ) {
			init_play(NULL);					// 演奏初期化
		}
	}
	else if ( slide_cnt > 0 ) {					// 移行中
		if ( --slide_cnt == 0 ) {
			Mouse_set_offset(256, 0);
		}
	}
	else {
		slide_cnt = -1;

		if ( (play_num >= 0) && (play_num < 6) ) {
			cnt = modu(cnt + tempo_speed[tempo], 120*8*4);
			if ( modu(cnt, 120) == 0 ) {		// ベース音程再生
				short	t = bass_pattern[play_num][divs(cnt, 120) % 8];

				if ( t >= 0 ) {
					play_note(chord_data[chord_progression[prog_num][divs(cnt, 120*8)]][modu(t, 6)][0] + divs(t, 6)*12, 112);
				}
			}
		}

		int		t = -1;

		bass_num = -1;
		for (int i = 0; i < 7; i++) {			// ベースパターン選択ボタン
			if ( Button_update(&button[BTN_BASS + i]) ) {
				bass_num = i;
				break;
			}
			if ( button[BTN_BASS + i].focus ) {
				t = i;
			}
		}
		if ( play_num != t ) {
			play_num = t;
			cnt = 120*(4*8 - 1);
		}
		if ( bass_num >= 0 ) {					// ベースパターン決定
			exit_cnt = 20;
			fade_out();
		}
		else if ( PatButton_update(&pat_button[BTN_CANCEL]) ) {			// コード進行選択に戻る
			phase		= PHASE_CHORD;
			play_num	= -1;
			slide_cnt	= 7;

			for (int i = 0; i < 14; i++) {
				Button_reset(&button[BTN_CHORD + i]);
			}
			m_tempo(120);
		}

		control_tempo();						// テンポ変更
	}
}


static short	note_on(int, int);						// 音符選択
static void		init_note(void);						// 音符初期化
static Bool		load_score(uint8_t const* data);		// 譜面復元

/************************************
    演奏初期化
		引数	復元データ
		戻り値	初期化に成功したか
 ************************************/
static
Bool	init_play(uint8_t const* data)
{
	phase		= PHASE_PLAY;
	cnt			= -120*2;
	exit_cnt	= 0;
	mute_cnt	= 0;

	if ( data == NULL ) {
		init_note();							// 音符初期化

		if ( bass_num < 6 ) {					// ベースパターン
			short const*	bass = &bass_pattern[bass_num][0];

			for (int i = 0; i < 4*8; i++) {
				if ( bass[i % 8] >= 0 ) {
					note_on(i, bass[i % 8]);
				}
			}
		}
	}
	else if ( !load_score(data) ) {				// 譜面復元
		return	FALSE;
	}


	clear_text();								// テキスト画面クリア
	SCROLL(8, 0, 0);
	Mouse_set_offset(0, 0);

	for (int i = 0; i < 4; i++) {				// コード名
		draw_text(i*8, 48, chord_name[chord_progression[prog_num][i]]);
	}

	init_tempo();								// テンポ変更UI初期化

	draw_text(27, 12, "終了");					// 終了ボタン
	Button_init(&button[BTN_EXIT], 212, 8, 39, 24);

	static const
	struct TBOXPTR	btn_frame[3] =				// ボタン枠
	{
		{3,	212 - 1, 8 - 1, 42, 27,	0xffff},
		{0,	212 - 1, 8 - 1, 42, 27,	0xffff},
		{3,	212 - 2, 8 - 2, 42, 27,	0xffff},
	};

	for (int i = 0; i < 3; i++) {
		TXBOX((struct TBOXPTR*)&btn_frame[i]);
	}

	fade_in();
	return	TRUE;
}

/****************
    音符初期化
 ****************/
static
void	init_note(void)
{
	for (int i = 0; i < 4*8; i++) {
		short	_progression = chord_progression[prog_num][i/8];

		for (int j = 0; j < 11; j++) {
			short const*	_key = chord_data[_progression][j % 6];
			short			_octave = (short)(divs(j, 6)*12);

			Note_init(&note[i][j], i, _key[0] + _octave, (_key[1] > 0) ? (_key[1] + _octave) : 0, &bg_note[(10 - j)*2][i]);
		}
	}
}


/**********
    演奏
 **********/
static
void	update_play(void)
{
	if ( exit_cnt > 0 ) {
		if ( --exit_cnt == 0 ) {
			save_header = (uint8_t)(((tempo + 5) << 4) | prog_num);			// 保存データヘッダー
			init_select();						// 選択画面初期化
		}
		return;
	}

	if ( cnt >= 0 ) {
		if ( modu(cnt, 120) == 0 ) {			// 発音
			Note*	n = &note[divs(cnt, 120)][0];

			for (int i = 0; i < 11; i++, n++) {
				if ( n->state == ON ) {
					play_note(n->key, 116 - mute_cnt);
				}
			}
		}

		Note*	n = &note[divs(cnt, 120)][0];
		int		t = divs(cnt, 30) % 4;

		for (int i = 0; i < 11; i++) {			// 発音フラッシュ
			Note_flash(n++, t);
		}
	}

	cnt += tempo_speed[tempo];					// 進行
	if ( cnt >= 120*8*4 ) {
		cnt = 0;
	}
	if ( mute_cnt > 0 ) {
		mute_cnt--;
	}

	if ( mouse.trigger & MS_LEFT ) {			// 音符入力
		int		x = mouse.x/8,
				y = 10 - (mouse.y - 8*8 - 2)/16;

		if ( (y >= 0) && (y < 11) && (x >= 0) && (x < 4*8) ) {
			short	key = note_on(x, y);		// 音符ON/OFF

			if ( key > 0 ) {
				play_note(key, 120);
				mute_cnt = 30;
			}
			else if ( key < 0 ) {
				play_pcm(SE_CANCEL);
			}
		}
	}

	control_tempo();							// テンポ変更

	if ( Button_update(&button[BTN_EXIT]) ) {	// "終了"ボタン
		exit_cnt = 20;
		fade_out();
	}
}

static void		check_note(void);				// 音符選択チェック

/******************************
    音符選択
		引数	x, y = 位置
		戻り値	選択時の音程
 ******************************/
static
short	note_on(int x, int y)
{
	Note*	n = &note[x][y];

	switch ( n->state ) {
	  case OFF :
		break;

	  case ACTIVE :
		Note_set_state(n, ON);					// 音符ON
		check_note();							// 音符選択チェック
		return	n->key;

	  case ON :
		Note_set_state(n, ACTIVE);				// 音符OFF
		check_note();							// 音符選択チェック
		return	-1;
	}
	return	0;
}

/**********************
    音符選択チェック
 **********************/
static
void	check_note(void)
{
	uint16_t	active;
	int			limit;
	Note		*before[4*8], *after[4*8], *p;

	active = 0;
	limit = 0;
	p = NULL;
	for (int x = 4*8 - 1; x >= 0; x--) {
		Note*		n = &note[x][0];
		uint16_t	k = 1, t = 0;

		if ( x < limit ) {
			active = 0;
			limit = 0;
		}
		after[x] = p;
		for (int i = 0; i < 11; i++, n++, k <<= 1) {
			if ( n->state == ON ) {
				p = &note[x][0];
			}

			if ( n->inner ) {					// 内音
				if ( n->state == ON ) {
					t |= k | (k >> 1) | (k << 1);
				}
			}
			else if ( active & k ) {			// 外音有効
				if ( n->state == OFF ) {
					Note_set_state(n, ACTIVE);
				}
			}
			else {								// 外音無効
				if ( n->state != OFF ) {
					Note_set_state(n, OFF);
				}
			}
		}
		if ( t ) {
			active = t;
			limit = (x & ~7) - 8;
		}
	}

	active = 0xffff;
	p = NULL;
	for (int x = 0; x < 4*8; x++) {
		Note*		n = &note[x][0];
		uint16_t	k = 1;

		before[x] = p;
		for (int i = 0; i < 11; i++, n++, k <<= 1) {
			if ( n->state == ON ) {
				p = &note[x][0];
			}

			if ( n->inner && (n->state == ON) ) {		// 内音ON
				active = 0xffff;
			}
		}
		n = &note[x][0];
		k = 1;
		uint16_t	t = active;
		for (int i = 0; i < 11; i++, n++, k <<= 1) {
			if ( n->inner ) {					// 内音
				if ( t & k ) {					// 内音有効
					if ( n->state == OFF ) {
						Note_set_state(n, ACTIVE);
					}
				}
				else {							// 内音無効
					if ( n->state != OFF ) {
						Note_set_state(n, OFF);
					}
				}
			}
			else if ( n->state == ON ) {		// 外音
				active &= k | (k >> 1) | (k << 1);
			}
		}
	}

	for (int x = 0; x < 4*8; x++) {
		Note*		n = &note[x][0];
		uint16_t	k = 1;
		int			num = 0;
		uint32_t	semitone = 0;
		Note		*ap = after[x], *bp = before[x];

		for (int i = 0; i < 11; i++, n++, k <<= 1) {
			if ( n->state == ON ) {
				num++;							// 発音数
				semitone |= ((1 | (1 << 12) | (1 << 12*2)) << modu(n->key - 5, 12));
			}
			else if ( !n->inner && (n->state == ACTIVE) ) {			// 外音音程
				n->key = n->key_data[0];
				if ( ap != NULL ) {
					if ( ap[i + 1].state == ON ) {					// → 上 内音
						n->key = n->key_data[1];
						if ( bp && (bp[i].state == ON) && (bp[i].key >= n->key) ) {			// 同 外音 →
							n->key = (bp[i].key + ap[i + 1].key)/2;
						}
					}
					else if ( ap[i - 1].state == ON ) {				// → 下 内音
						if ( bp && (bp[i].state == ON) && (bp[i].key <= n->key) ) {			// 同 外音 →
							n->key = (bp[i].key + ap[i - 1].key + 1)/2;
						}
					}
					else if ( (ap[i].state == ON) && bp ) {			// → 同 外音
						if ( bp[i].state == ON ) {					// 同 外音 →
							short	key = bp[i].key + ap[i].key;
							if ( bp[i].key > ap[i].key ) {
								key++;
							}
							n->key = key/2;
						}
						else if ( bp[i + 1].state == ON ) {			// 上 内音 →
							n->key = (n->key_data[1] > ap[i].key) ? n->key_data[1] : (bp[i + 1].key + ap[i].key)/2;
						}
						else if ( bp[i - 1].state == ON ) {			// 下 内音 →
							n->key = (n->key_data[0] < ap[i].key) ? n->key_data[0] : (bp[i - 1].key + ap[i].key + 1)/2;
						}
					}
				}
			}
		}
		n = &note[x][0];
		if ( num >= 4 ) {						// 発音数オーバー
			for (int i = 0; i < 11; i++, n++) {
				if ( n->state == ACTIVE ) {
					Note_set_state(n, OFF);
				}
			}
		}
		else {									// 半音チェック
			semitone = (semitone << 1) | (semitone >> 1);			// 半音
			for (int i = 0; i < 11; i++, n++) {
				if ( (n->state == ACTIVE) && (semitone & (1 << (n->key - 5))) ) {
					if ( n->inner ) {
						Note_set_state(n, OFF);
					}
					else if ( !(semitone & (1 << (n->key_data[1] - 5))) ) {
						n->key = n->key_data[1];
					}
					else if ( !(semitone & (1 << (n->key_data[0] - 5))) ) {
						n->key = n->key_data[0];
					}
					else {
						Note_set_state(n, OFF);
					}
				}
			}
		}
	}
}


#define	SAVE_FILE	"COMPOSER.SAV"

/******************************
    譜面保存
		戻り値	保存できたか
 ******************************/
static
Bool	save_score(void)
{
	uint8_t		*data, *p;

	if ( (data = malloc(1 + 4*8*11)) == NULL ) {
		goto error;
	}
	p = data;
	*p++ = save_header;							// テンポ・コード進行

	Note*	n = &note[0][0];

	for (int i = 0; i < 4*8*11; i++) {			// 音符
		*p++ = Note_save(n++);
	}

	FILE*	fp;

	if ( (fp = fopen(SAVE_FILE, "wb")) == NULL ) {			// ファイルオープン
		free(data);
		goto error;
	}
	fwrite(data, 1 + 4*8*11, 1, fp);			// データ書き込み
	fclose(fp);

	free(data);
	return	TRUE;

error:
	set_error("セーブデータの書き込みに失敗しました\n");
	return	FALSE;
}

/***********************************
    譜面復元
		引数	data = 復元データ
		戻り値	復元できたか
 ***********************************/
static
Bool	load_score(uint8_t const* data)
{
	save_header = *data++;
	tempo    = (int)(save_header >> 4) - 5;		// テンポ
	prog_num = (int)(save_header & 0x0f);		// コード進行
	if ( !((tempo >= 0) && (tempo < 5) && (prog_num >= 0) && (prog_num < 13)) ) {
		set_error("セーブデータが正しくありません\n");
		return	FALSE;
	}

	init_note();								// 音符初期化

	Note*	n = &note[0][0];

	for (int i = 0; i < 4*8*11; i++) {			// 音符復元
		Note_load(n++, *data++);
	}
	return	TRUE;
}


/****************************
    稼働
		戻り値	実行継続か
 ****************************/
Bool	Composer_update(void)
{
	Mouse_update();								// マウス稼働

	switch ( phase ) {
	  case PHASE_CHORD :			// コード進行選択
		update_chord();
		break;

	  case PHASE_BASS :				// ベースパターン選択
		update_bass();
		break;

	  case PHASE_PLAY :				// 演奏
		update_play();
		break;
	}

	if ( BITSNS(0) & 0x02 ) {					// ESCキー
		if ( phase == PHASE_PLAY ) {
			save_header = (uint8_t)(((tempo + 5) << 4) | prog_num);			// 保存データヘッダー
		}
		else if ( save_header == 0xff ) {
			return	FALSE;
		}
		save_score();							// 譜面保存
		return	FALSE;
	}
	return	TRUE;
}


/**********
    描画
 **********/
void	Composer_draw(void)
{
void	draw_note_bg(void);						// 音符BG転送

	Mouse_draw();								// マウスカーソル

	switch ( phase ) {
	  case PHASE_CHORD :			// コード進行選択
		if ( slide_cnt >= 0 ) {
			SCROLL(8, muls(slide_cnt, slide_cnt)*(256/(8*8)), 0);
		}
		break;

	  case PHASE_BASS :				// ベースパターン選択
		if ( slide_cnt >= 0 ) {
			SCROLL(8, 256 - muls(slide_cnt, slide_cnt)*(256/(8*8)), 0);
		}
		break;

	  case PHASE_PLAY :				// 演奏
		{
			int		x = divs(cnt, 15) + 16,		// ライン位置
					y = 56 + 2 + 16;

			for (int i = 0; i < 12; i++, y += 16) {
				SP_REGST(i + (1 + (1 << 0x1f)), x, y, SPR_LINE + (PAL_LINE << 8), 1);
			}

			draw_note_bg();						// 音符BG
		}
		break;
	}
}

