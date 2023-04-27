/*

	�y�l�t�r�h�b�D�w�p���C�u�����w�b�_�t�@�C��

	   ZMLIB.H Version 2.00 (C) Z.Nishikawa

*/

int	m_alloc( int track_no, int buffer_size );
int	m_assign( int channel_no, int track_no );
int	m_vget( int tone_no, char *data_ptr );
int	m_vset( int tone_no, char *data_ptr );
int	m_tempo( int tempo );		/* tempo=-1�Ń��N�G�X�g */
int	m_trk( int track_no, char *MML_ptr );
int	m_free( int track_no );
int	m_play( int track_no1, int track_no2, int track_no3, int track_no4,
		int track_no5, int track_no6, int track_no7, int track_no8,
		int track_no9, int track_no10 );
		/* track_no1=0 �őS�g���b�N���t�J�n */
		/* track_no?=0 �܂��� 'NASI' �ȍ~�𖳎�����B */
int	m_stat( int track_bit_pattern );	/* track_bit_pattern=0 �őS�`�����l������ */
int	m_stop( int track_no1, int track_no2, int track_no3, int track_no4,
		int track_no5, int track_no6, int track_no7, int track_no8,
		int track_no9, int track_no10 );
		/* track_no1=0 �őS�g���b�N���t��~ */
		/* track_no?=0 �܂��� 'NASI' �ȍ~�𖳎�����B */
int	m_cont( int track_no1, int track_no2, int track_no3, int track_no4,
		int track_no5, int track_no6, int track_no7, int track_no8,
		int track_no9, int track_no10 );
		/* track_no1=0 �őS�g���b�N���t�p�� */
		/* track_no?=0 �܂��� 'NASI' �ȍ~�𖳎�����B */
void	m_init( void );
int	m_atoi( int track_no );
int	m_assign2( char *channel, int track_no );
void	m_ch( char *device );
int	m_pcmset( int note_no, char *filename, int pitch, int vol, int mix_note_no, int delay,
		  int cut, int reverse, int fade_in_out );
		/* int pitch�ȍ~�̃p�����[�^���ȗ�����ꍇ�� 'NASI' �Ƃ��邱�� */
void	m_pcmplay( int note_no, int pan, int freq );
void	m_rec( void );
void	m_rstop( void );
int	m_save( char *filename );
int	m_trans( char *filename );
int	m_fmvset( int tone_no, char *data_ptr );
int	m_out( int  d1, int  d2, int  d3, int  d4, int  d5, int  d6, int  d7, int  d8, 
	       int  d9, int d10 );
		/* d?=-1 �ȍ~�𖳎�����B */
int	m_dirout( char *adrs, int size );
		/* size�̏ȗ��s�� */
int	m_exc( char *adrs, int size );
		/* size�̏ȗ��s�� */
int	m_roland( int devID, int modelID, char *adrs, int size );
		/* size�̏ȗ��s�� */
int	m_total( void );
int	m_fadeout( int speed );
int	m_pcmcnf( char *filename );

int	sc55_v_reserve( char *adrs, int devID );
				/* size=16 */
int	sc55_reverb( char *adrs, int devID, int size );
				/* size=7 */
int	sc55_chorus( char *adrs, int devID, int size );
				/* size=8 */
int	sc55_part_setup( char part_no, char *adrs, int devID, int size );
				/* size=119 */
int	sc55_drum_setup( char map_no, char note_no, char *adrs, int devID, int size );
				/* size=8 */
int	sc55_print( char *message, int devID );
				/* size=32 */
int	sc55_display( int *pattern, int devID );

int	m_adpcm_block( char *filename );

int	mt32_p_reserve( char *adrs, int devID );
				/* size=9 */
int	mt32_reverb( char *adrs, int devID, int size );
				/* size=3 */
int	mt32_part_setup( char *adrs, int devID, int size );
				/* size=9 */
int	mt32_drum_setup( char note_no, char *adrs, int devID, int size );
				/* size=4 */
int	mt32_common( char timbre_no, char *timbre_name, char *adrs, int devID, int size );
				/* size=4 */
int	mt32_patch( char patch_no, char *adrs, int devID, int size );
				/* size=7 */
int	mt32_partial( char timbre_no, char partial_no, char *adrs, int devID, int size );
				/* size=58 */
int	mt32_print( char *message, int devID );
				/* size=20 */

int	m_print( char *message );
				/* size=96 */

int	u220_setup( char *adrs, int devID );
				/* size=7 */
int	u220_common( char *adrs, int devID );
				/* size=17 */
int	u220_drum_setup( char *adrs, int devID );
				/* size=7 */
int	u220_part_setup( char part_no, char *adrs, int devID );
				/* size=13 */
int	u220_timbre( char timbre_no, char *timbre_name, char *adrs, int devID );
				/* size=26 */
int	u220_drum_inst( char note_no, char *adrs, int devID, int size );
				/* size=20 */
int	u220_print( char *message, int devID );
				/* size=12 */

int	m1_midi_ch( char *midi_ch_list );
				/* size=8 */
int	m1_part_setup( char *track_param );
				/* size=40 */
int	m1_effect_setup( char *effect_param );
				/* size=25 */
int	m1_print( char *message );
				/* size=10 */
int	send_to_m1( int devID );

int	zmd_play( char *filename );
void	m_debug( char mode );
int	m_count( char count );
int	fm_master( char volume );
int	m_mute( int ch_no1, int ch_no2, int ch_no3, int ch_no4,
		int ch_no5, int ch_no6, int ch_no7, int ch_no8,
		int ch_no9, int ch_no10 );
		/* ch_no1=0 �őS�g���b�N���t�p�� */
		/* ch_no?=0 �܂��� 'NASI' �ȍ~�𖳎�����B */
int	m_solo( int ch_no1, int ch_no2, int ch_no3, int ch_no4,
		int ch_no5, int ch_no6, int ch_no7, int ch_no8,
		int ch_no9, int ch_no10 );
		/* ch_no1=0 �őS�g���b�N���t�p�� */
		/* ch_no?=0 �܂��� 'NASI' �ȍ~�𖳎�����B */
int	m_wave_form( char wave_no, char loop_type, int loop_point,
			int *wave_data, int size );
int	m_wave_form2( char wave_no, char loop_type, int loop_point,
			short int *wave_data, int size );

int	sc55_init( int devID );
int	mt32_init( int devID );

void	adpcm_to_pcm( char *source, int size, short int *destination );
		/* destination�̔z��T�C�Y��source�̂S�{�K�v
		   �܂��Asize��ADPCM�f�[�^�̌� */
void	pcm_to_adpcm( short int *source, int size, char *destination );
		/* destination�̔z��T�C�Y��source��1/4�{�K�v
		   �܂��Asize��PCM�f�[�^�̌� */

void	exec_zms( char *zms_line );

int	m_inp( char inp_mode );	/* inp_mode��0�Ń��[�v���[�h */

int	zm_ver( void );

int	m_trk2( char *MML_ptr,
		int track_no1, int track_no2, int track_no3 ,int track_no4,
		int track_no5, int track_no6, int track_no7 ,int track_no8 );
		/* track_no?=0 �܂��� 'NASI' �ȍ~�𖳎�����B */

int	zm_work( char trk_num, int work_offset );
		/* ���t�g���b�N���[�N�̒l���o�C�g�P�ʂŕԂ� */

/*
	�@��{�I�ɂw�|�a�`�r�h�b�p�O���֐��ł���l�t�r�h�b�y�D�e�m�b��
	�R���p�`�ɍ���Ă��܂����A�ꕔ�̌���d�l�̈Ⴂ����A�݊��łȂ�
	�֐�������܂��B
	�@�w�|�a�`�r�h�b�ł͔z��̗v�f�����֐����Ŏ����F�m���邱�Ƃ�
	�ł��܂����b����ł͂��ꂪ�ł��܂���B����āA�w�|�a�`�r�h�b�ł�
	�p�����[�^�̌������ȗ��ł����֐����A�b����ł͏ȗ��ł��Ȃ��Ƃ�����
	�d�l�ύX���Ȃ��ꂽ�֐�������܂��B

		m_dirout()
		m_exc()
		m_roland()

	  �܂��A����ɁA�w�|�a�`�r�h�b�ł̓p�����[�^���������Ȃ��Ă�
	�悩�����֐����b����ł͏�������悤�Ȏd�l�ɕύX���ꂽ���̂�����܂��B

		sc55_reverb()
		sc55_chorus()
		sc55_part_setup()
		sc55_drum_setup()
		mt32_reverb()
		mt32_part_setup()
		mt32_drum_setup()
		mt32_common()
		mt32_patch()
		mt32_partial()
		u220_drum_inst()

	  �l�t�r�h�b�y�D�e�m�b�ɂ͂Ȃ������R�}���h���V�݂���Ă��܂��B

		m_wave_form2()
		�g�`�������o�^�R�}���h#2 (short int��p��/�z��f�[�^���H�Ȃ�)

*/