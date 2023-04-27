/**************************

		���C��

 **************************/

#include "common.h"
#include "app.h"
#include "Sound.h"
#include "Composer\Composer.h"
#include <io.h>


/******************
    �t�F�[�h�C��
 ******************/
void	fade_in(void)
{
	CONTRAST(-2);
}

/********************
    �t�F�[�h�A�E�g
 ********************/
void	fade_out(void)
{
	CONTRAST(0);
}


/***************************************
    �t�@�C���ǂݍ���
			����	name = �t�@�C����
			�߂�l	�t�@�C���f�[�^
 ***************************************/
uint8_t*	load_file(char const* name)
{
	FILE*		fp;
	long		size;
	uint8_t*	p;

	if ( (fp = fopen(name, "rb")) == NULL ) {
		set_error("�t�@�C�� \"%s\" ���J���܂���\n", name);
		return	NULL;
	}
	size = filelength(fileno(fp));			// �t�@�C���̑傫��
	if ( (p = malloc(size)) == NULL ) {
		set_error("������������܂���\n");
		fclose(fp);
		return	NULL;
	}
	fread(p, 1, size, fp);					// �ǂݍ���
	fclose(fp);

	return	p;
}


/***************************************************
    �X�v���C�g�ǂݍ���
			����	sp_name  = �X�v���C�g�t�@�C��
					pal_name = �p���b�g�t�@�C��
			�߂�l	����������
 ***************************************************/
Bool	load_sprite(const char* sp_name, const char* pal_name)
{
	uint8_t*	buf;

	if ( (buf = malloc(0x8000)) == NULL ) {
		set_error("������������܂���\n");
		return	FALSE;
	}

	FILE*	fp;
	size_t	size;

	if ( (fp = fopen(sp_name, "rb")) == NULL ) {
		set_error("�p�^�[���t�@�C�� \"%s\" ���J���܂���\n", sp_name);
		free(buf);
		return	FALSE;
	}
	size = fread(buf, 0x80, 0x100, fp);
	fclose(fp);

	for (int i = 0; i < size; i++) {
		SP_DEFCG(i, 1, buf + i*0x80);		// �X�v���C�g��`
	}

	if ( (fp = fopen(pal_name, "rb")) == NULL ) {
		set_error("�p���b�g�t�@�C�� \"%s\" ���J���܂���\n", pal_name);
		free(buf);
		return	FALSE;
	}
	size = fread(buf, sizeof(uint16_t)*0x10, 0x0f, fp);
	fclose(fp);

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < 0x10; i++) {
			SPALET((1 << 31) + i, j + 1, ((uint16_t*)buf)[j*0x10 + i]);		// �p���b�g��`
		}
	}

	free(buf);
	return	TRUE;
}


static
char	error_message[128] = "\0";			// �G���[���b�Z�[�W

/****************************************
    �G���[�ݒ�
		����	err = �G���[���b�Z�[�W
 ****************************************/
void	set_error(const char* mes, ...)
{
	va_list		args;

	va_start(args, mes);
	vsprintf(error_message, mes, args);
	va_end(args);
}


volatile uint16_t	vsync_cnt = 0;			// ���������J�E���^

/************
    ���C��
 ************/
int		main(int argc, char* argv[])
{
void	v_sync(void);			// �����������荞��

	int		crt_mode;						// ���X�̉�ʃ��[�h

	crt_mode = CRTMOD(-1);					// ��ʃ��[�h�ۑ�
	CRTMOD(14);								// 256x256(65536�F)
	TGUSEMD(0, 2);							// �O���t�B�b�N��ʎg�p
	TGUSEMD(1, 2);							// �e�L�X�g��ʎg�p
	C_CUROFF();								// �J�[�\����\��
	MS_INIT();								// �}�E�X������
	MS_CUROF();								// �}�E�X�J�[�\����\��
	G_CLR_ON();								// �O���t�B�b�N��ʕ\��

	SP_INIT();								// �X�v���C�g��ʏ�����
	SP_ON();								// �X�v���C�g��ʕ\��

	if ( !Sound_init() ) {					// �T�E���h�Ǘ�������
		set_error("ZMUSIC���풓���Ă��܂���\n");
		goto exit;
	}

	srand((unsigned int)TIMEGET());			// ����������


	if ( Composer_init((argc < 2) ? NULL : argv[1]) ) {			// ��ȏ�����
		VDISPST((UBYTE*)v_sync, 0, 1);		// �����A�����Ԋ��荞�ݐݒ�
		while ( Composer_update() ) {		// ��ȉғ�
			rand();
			if ( vsync_cnt > 1 ) {
				vsync_cnt = 1;
			}
			while ( vsync_cnt < 2 );
			vsync_cnt = 0;

			Composer_draw();				// ��ȕ`��
		}
		VDISPST(NULL, 0, 0);				// �����A�����Ԋ��荞�ݒ�~
		Composer_quit();					// ��ȏI��
	}

exit:
	Sound_quit();							// �T�E���h�Ǘ��I��
	clear_text();							// �e�L�X�g��ʃN���A
	TGUSEMD(0, 3);							// �O���t�B�b�N��ʎg�p�ς�
	TGUSEMD(1, 3);							// �e�L�X�g��ʎg�p�ς�
	CRTMOD(crt_mode);						// ��ʃ��[�h���A
	CONTRAST(-2);							// �R���g���X�g��߂�
	C_CURON();								// �J�[�\���\��
	KFLUSHIO(0xff);							// �L�[�o�b�t�@�N���A
	MS_INIT();								// �}�E�X������

	if ( error_message[0] ) {				// �G���[
		puts(error_message);
		return	1;
	}
	return	0;
}
