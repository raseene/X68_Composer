#ifndef	___APP_H___
#define	___APP_H___

void		fade_in(void);								// �t�F�[�h�C��
void		fade_out(void);								// �t�F�[�h�A�E�g
uint8_t*	load_file(char const*);						// �t�@�C���ǂݍ���
Bool		load_sprite(const char*, const char*);		// �X�v���C�g�ǂݍ���
void		set_error(const char*, ...);				// �G���[�ݒ�

void		clear_text(void);							// �e�L�X�g��ʃN���A

#endif
