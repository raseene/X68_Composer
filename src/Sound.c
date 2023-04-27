/*****************************

		�T�E���h�Ǘ�

 *****************************/

#include "Sound.h"
#include "app.h"


/*** �T�E���h�f�[�^ *******/
typedef struct
{
	uint8_t*	data;			// �f�[�^�A�h���X
	uint8_t*	bgm;			// BGM�A�h���X
	uint8_t*	se;				// SE�A�h���X
} SoundData;

static SoundData*	sound_data = NULL;			// �T�E���h�f�[�^
static Bool			init_flag = FALSE;			// �������t���O


/************
    ������
 ************/
Bool	Sound_init(void)
{
	init_flag = FALSE;
	sound_data = NULL;
	if ( zm_ver() & 0xffff ) {
		init_flag = TRUE;
		m_init();							// ����������
		return	TRUE;
	}
	return	FALSE;
}

/**********
    �I��
 **********/
void	Sound_quit(void)
{
	if ( init_flag ) {
		m_stop(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		if ( sound_data ) {					// �T�E���h�f�[�^���
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
    �T�E���h�f�[�^�ǂݍ���
			����	_file = ZMD�t�@�C��
			�߂�l	�ǂݍ��ݐ�����
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
			n++;							// �f�[�^��
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
    ADPCM�f�[�^�ǂݍ���
		����	_file = ZPD�t�@�C��
 *************************************/
Bool	load_adpcm(char const* _file)
{
	if ( init_flag ) {
		if ( m_adpcm_block((char*)_file) ) {
			set_error("�t�@�C�� \"%s\" ���J���܂���\n", _file);
			return	FALSE;
		}
	}
	return	TRUE;
}

/**********************************
    BGM�Đ�
		����	n = �T�E���h�ԍ�
 **********************************/
void	play_bgm(int n)
{
	if ( init_flag ) {
		asm volatile (
			"	movea.l	%0,a1\n"
			"	clr.l	d2\n"
			"	moveq.l	#$11,d1\n"
			"	trap	#3\n"
		:	/* �o�� */
		:	/* ���� */	"irm" (sound_data[n].bgm)	// ���� %0
		:	/* �j�� */	"d0", "d1", "d2", "a1"
		);
	}
}

/************
   BGM��~
 ************/
void	stop_bgm(void)
{
	if ( init_flag ) {
		m_stop(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}

/***********************************
   BGM�t�F�[�h�A�E�g
		����	_speed = �X�s�[�h
 ***********************************/
void	fadeout_bgm(int _speed)
{
	if ( init_flag ) {
		m_fadeout(_speed);
	}
}

/**********************************
    SE�Đ�
		����	n = �T�E���h�ԍ�
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
		:	/* �o�� */
		:	/* ���� */	"irm" (sound_data[n].se),	// ���� %0
						"irm" (track)				// ���� %1
		:	/* �j�� */	"d0", "d1", "d2", "a1"
		);

		track = (track % 4) + 5;
	}
}

/********************************
    PCM�Đ�
		����	n = �m�[�g�ԍ�
 ********************************/
void	play_pcm(int n)
{
	if ( init_flag ) {
		m_pcmplay(n, 3, 4);
	}
}

