#ifndef	___SOUND_H___
#define	___SOUND_H___

#include "ZMUSIC.H"
#include "common.h"


Bool	Sound_init(void);				// ������
void	Sound_quit(void);				// �I��
Bool	load_sound(char const**);		// �T�E���h�f�[�^�ǂݍ���
Bool	load_adpcm(char const*);		// ADPCM�f�[�^�ǂݍ���
void	play_bgm(int);					// BGM�Đ�
void	stop_bgm(void);					// BGM��~
void	fadeout_bgm(int);				// BGM�t�F�[�h�A�E�g
void	play_se(int);					// SE�Đ�
void	play_pcm(int);					// PCM�Đ�

#endif
