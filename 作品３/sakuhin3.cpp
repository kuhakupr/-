
//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resouce.h"
#include  <math.h>

//########## �}�N����` ##########
#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"�G�f��"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS			60	//FPS�̐��l	

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129		//0x0000�`0x0080�܂�

//�p�X�̒���
#define PATH_MAX			255	//255�����܂�
#define NAME_MAX			255	//255�����܂�

//�t�H���g
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

//�����̕`��
#define STR_DRAW_SIZE	24		//�t�H���g�̃T�C�Y
#define STR_DRAW_ROW_MAX	4	//������̍ő�s
#define STR_ROW_MAX		30		//�����s�̍ő�l
#define STR_COL_MAX		255		//������̍ő�l
#define STR_DRAW_SPEED	1		//������̕`�摬�x(���t���[�����ƂɁA�P�����`�悷�邩�H)


//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�摜�̃p�X
#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\haikei1.png")	//�w�i�̉摜
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\tsundere_boy2.png")	//�v���C���[�̉摜
#define IMAGE_PLAY_BACK          TEXT(".\\IMAGE\\haikei1.png")//�v���C�w�i
#define KariKyara    TEXT(".\\IMAGE\\icon.png")//���L����

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\title.png")		//�^�C�g���w�i�̉摜

#define IMAGE_END_COMP_PATH		TEXT(".\\IMAGE\\happy_end2.png")	//�G���h�R���v�摜
#define IMAGE_END_COMP_CNT		1			//�_�ŃJ�E���^
#define IMAGE_END_COMP_CNT_MAX	30			//�_�ŃJ�E���^MAX

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\Bad_End2.png")	//�G���h�t�H�[���摜
#define IMAGE_END_FAIL_CNT		1			//�_�ŃJ�E���^
#define IMAGE_END_FAIL_CNT_MAX	30			//�_�ŃJ�E���^MAX

#define IMAGE_BACK_REV_PATH		TEXT(".\\IMAGE\\haikei1.png")	//�w�i�̉摜
#define IMAGE_BACK_NUM			4								//�w�i�̉摜�̐�



//�G���[���b�Z�[�W
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//���y�̃p�X
#define MUSIC_BGM_PATH			TEXT(".\\MUSIC\\Title.mp3")	//BGM

#define MUSIC_BGM_TITLE_PATH		TEXT(".\\MUSIC\\class.mp3")	//�^�C�g����BGM
#define MUSIC_BGM_COMP_PATH			TEXT(".\\MUSIC\\happy_end.mp3")				//�R���v���[�gBGM
#define MUSIC_BGM_FAIL_PATH			TEXT(".\\MUSIC\\bad_end.mp3")					//�t�H�[���gBGM

#define GAME_MAP_TATE_MAX	9	//�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX	13	//�}�b�v�̉��̐�
#define GAME_MAP_KIND_MAX	2	//�}�b�v�̎�ނ̐�

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map2.png")		//�}�b�v�̉摜

#define MAP_DIV_WIDTH		64	//�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT		64	//�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE		10	//�摜���c�ɕ������鐔
#define MAP_DIV_YOKO		4	//�摜�����ɕ������鐔
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�摜�𕪊����鑍��

//�G���[���b�Z�[�W
#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

#define GOAL_ERR_TITLE		TEXT("�S�[���ʒu�G���[")
#define GOAL_ERR_CAPTION	TEXT("�S�[���ʒu�����܂��Ă��܂���")

//�I���_�C�A���O�p
#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)����
	k = 0,	//��
	t = 9,	//�ʘH
	s = 2,	//�X�^�[�g
	g = 3	//�S�[��
};	//�}�b�v�̎��

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_IBENTO,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum GAME_END {
	GAME_END_COMP,	//�R���v���[�g
	GAME_END_FAIL	//�t�H�[���g
};	//�Q�[���̏I�����

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//�L�����N�^�[�̃X�s�[�h

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//�L�����N�^�[�̃����[�h

//int�^��POINT�\����
typedef struct STRUCT_I_POINT
{
	int x = -1;	//���W��������
	int y = -1;	//���W��������
}iPOINT;

//�}�E�X�\����
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInput�̒l������
	int WheelValue = 0;	//�}�E�X�z�C�[���̉�]��(���̓v���X�l / ��O�̓}�C�i�X�l)
	iPOINT Point;		//�}�E�X�̍��W������
	iPOINT OldPoint;	//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^������(���O)������
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^�����͂�����
}MOUSE;

//�t�H���g�\����
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//�p�X
	char name[NAME_MAX];		//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}IMAGE;	//�摜�\����

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
}MUSIC;	//���y�\����



typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY
	RECT coll;					//�����蔻��
	iPOINT collBeforePt;		//������O�̍��W

}CHARA;	//�L�����N�^�[�\����

typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;		//IMAGE�\����
	BOOL IsDraw;
}IMAGE_BACK;	//�w�i�摜�̍\����




typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;		//IMAGE�\����
	double angle;		//��]��
	double angleMAX;	//��]��MAX
	double rate;		//�g�嗦
	double rateMAX;		//�g�嗦MAX

}IMAGE_ROTA;	//��]�g�傷��摜�̍\����

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;		//IMAGE�\����
	int Cnt;			//�_�ŃJ�E���^
	int CntMAX;			//�_�ł��鎞��MAX
	BOOL IsDraw;		//�`��ł��邩�H

}IMAGE_BLINK;	//�_�ł���摜�̍\����

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP_DIV_NUM];			//���������̒e�̉摜�n���h�����擾
	int kind[MAP_DIV_NUM];				//�}�b�v�̎��
	int width;							//��
	int height;							//����
}MAPCHIP;	//MAP_IMAGE�\����

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//�}�b�v�̎��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}MAP;	//MAP�\����

//########## �O���[�o���ϐ� ##########
//FPS�֘A
int StartTimeFps;				//����J�n����
int CountFps;					//�J�E���^
float CalcFps;					//�v�Z����
int SampleNumFps = GAME_FPS;	//���ς����T���v����

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[256] = { '\0' };			//���ׂẴL�[�̏�Ԃ�����
char OldAllKeyState[256] = { '\0' };	//���ׂẴL�[�̏��(���O)������

//�}�E�X�̍��W���擾
MOUSE mouse;

FONT FontTanu32;	//���ʂ������}�W�b�N�F�傫��32�@�̃t�H���g�\����

int GameScene;		//�Q�[���V�[�����Ǘ�

int GameEndKind;					//�Q�[���̏I�����
RECT GoalRect = { -1,-1, -1, -1 };	//�S�[���̓����蔻��

IMAGE_BACK ImageBack[IMAGE_BACK_NUM];	//�Q�[���̔w�i

IMAGE ImageTitleBK;						//�^�C�g���w�i�̉摜
IMAGE Image;  //�w�i�摜
IMAGE_BLINK ImageTitleSTART;			//�^�C�g���X�^�[�g�̉摜
IMAGE karikyara;
IMAGE_BLINK ImageEndCOMP;				//�G���h�R���v�̉摜
IMAGE_BLINK ImageEndFAIL;				//�G���h�t�H�[���̉摜

CHARA player;		//�Q�[���̃L����

int DrawPointX, DrawPointY;	// ������`��̈ʒu
int RowPos;					// ������̍s��
int ColPos;					// ������̗�
BOOL EndFlag = FALSE;		// ������I���t���O
char OneMojiBuf[3];			// �P�������ꎞ�L���z��(�P�������{\0)
char DrawStringBuf[STR_DRAW_ROW_MAX][STR_COL_MAX];		// �`�悷�镶���������
int DefaultFontSize;								// �f�t�H���g�̃t�H���g�T�C�Y���擾
RECT rectString = { 0,GAME_HEIGHT - STR_DRAW_SIZE * STR_DRAW_ROW_MAX,GAME_WIDTH,GAME_HEIGHT };	// ������`��p�G���A
int DrawSpeedCnt = 0;					//�����̕`�摬�x�J�E���^
int DrawSpeedCntMax = STR_DRAW_SPEED;	//�����̕`�摬�x�J�E���^MAX

char Story[STR_ROW_MAX][STR_COL_MAX] =
{
	"�@���Ȃ��̂��Ƃ������Ă���邩����BB",
	"@ �Ȃ��H" ,
	"@�Ȃ��H���ċM���̂��Ƃ��C�ɓ����������AB",
	"���ꂢ��������Ȃɂ�����̂�BB",
	"�e�X�g",
	"@ ���Ȃ��̐��ʂ�?",
	"@�@���Ƃ� 2",
	"@�@����� 3",
	"@ �ǂ���ł����B�@Q",
	"2C���肪�Ƃ��@X",
	"3C���f�����Ȃ��@X",
	"X�ǂ����Ă��悧��������orz",
	"E"
	
};

//���y�֘A
MUSIC BGM;			//�Q�[����BGM

MUSIC BGM_TITLE;	//�^�C�g����BGM
MUSIC BGM_COMP;		//�R���v���[�g��BGM
MUSIC BGM_FAIL;		//�t�H�[���g��BGM

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		k,k,k,k,k,k,k,k,k,k,k,k,k,	// 0
		s,t,t,t,t,t,t,t,t,t,t,t,k,	// 1
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 2
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 3
		k,t,k,k,k,k,k,k,k,k,t,t,k,	// 4
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 5
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 6
		k,t,t,t,t,t,t,t,t,t,t,t,g,	// 7
		k,k,k,k,k,k,k,k,k,k,k,k,k,	// 8
};	//�Q�[���̃}�b�v

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

//�}�b�v�̏ꏊ���Ǘ�
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�X�^�[�g�̈ʒu
iPOINT startPt{ -1,-1 };

//�}�b�v�̓����蔻��
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//########## �v���g�^�C�v�錾 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int KEY_INPUT_);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_UP(int);				//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEYDOWN_KEEP(int, int);		//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����

VOID MY_MOUSE_UPDATE(VOID);			//�}�E�X�̓��͏����X�V����
BOOL MY_MOUSE_DOWN(int);			//�{�^���������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����
BOOL MY_MOUSE_UP(int);				//�{�^���������グ�����A�}�E�X�R�[�h�Ŕ��f����
BOOL MY_MOUSEDOWN_KEEP(int, int);	//�{�^�������������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����

BOOL MY_FONT_INSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
BOOL MY_FONT_CREATE(VOID);			//�t�H���g���쐬����
VOID MY_FONT_DELETE(VOID);			//�t�H���g���폜����

VOID MY_START(VOID);		//�X�^�[�g���
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);   //�v���C���
VOID MY_PLAY_PROC(VOID);  //�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);  //�v���C��ʂ̕`��

VOID MY_IBENTO(VOID);			//�C�x���g���
VOID MY_IBENTO_PROC(VOID);	//�C�x���g��ʂ̏���
VOID MY_IBENTO_DRAW(VOID);	//�C�x���g��ʂ̕`��

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);		//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);		//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);		//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);		//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);	//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//�̈�̓����蔻�������֐�

int Kaigyou(VOID);
VOID NovelProc(char str[][STR_COL_MAX]);	//���������񏈗��֐��i�����ŕ`�悷�镶��������炤�j
VOID NovelDraw(VOID);

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }




	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���


	//�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	//�S�[���̈ʒu�����łɌ�������
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�X�^�[�g�ʒu��T��
			if (mapData[tate][yoko] == s)
			{
				//�X�^�[�g�ʒu���v�Z
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//���SX���W���擾
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//���SY���W���擾
			}

			//�S�[���ʒu��T��
			if (mapData[tate][yoko] == g)
			{
				GoalRect.left = mapChip.width * yoko;
				GoalRect.top = mapChip.height * tate;
				GoalRect.right = mapChip.width * (yoko + 1);
				GoalRect.bottom = mapChip.height * (tate + 1);
			}
		}
	}

	//�X�^�[�g�����܂��Ă��Ȃ����
	if (startPt.x == -1 && startPt.y == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//�S�[�������܂��Ă��Ȃ����
	if (GoalRect.left == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_MOUSE_UPDATE();						//�}�E�X�̏�Ԃ��擾

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//�X�^�[�g���
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//�v���C���
			break;
		case GAME_SCENE_IBENTO:
			MY_IBENTO();
			break;
		case GAME_SCENE_END:
			MY_END();	//�G���h���
			break;
		}

		MY_FPS_DRAW();		//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	//�t�H���g�n���h����j��
	MY_FONT_DELETE();

	//�ꎞ�I�ɃC���X�g�[�������t�H���g���A���C���X�g�[��
	MY_FONT_UNINSTALL_ONCE();

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//���y�n���h����j��
	MY_DELETE_MUSIC();

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//���s�֐�
int Kaigyou(VOID)
{
	// �`�����ŏ��ɖ߂�
	DrawPointX = 0;

	DrawPointY++;	// �`��s�ʒu���������

	// ������ʂ���͂ݏo��Ȃ當������X�N���[��������
	if (rectString.top + DrawPointY * STR_DRAW_SIZE + STR_DRAW_SIZE > rectString.bottom)
	{
		//��ԏ�̍s����ɂ���
		for (int j = 0; j < STR_COL_MAX; j++) { DrawStringBuf[0][j] = '\0'; }

		//��̍s�ɏ��ԂɈړ�������
		for (int i = 1; i < STR_DRAW_ROW_MAX; i++)
		{
			strcpy_s(DrawStringBuf[i - 1], DrawStringBuf[i]);
		}

		//�Ō�̍s����ɂ���
		for (int j = 0; j < STR_COL_MAX; j++) { DrawStringBuf[STR_DRAW_ROW_MAX - 1][j] = '\0'; }

		// �ŏI�s����`����J�n����
		DrawPointY = STR_DRAW_ROW_MAX - 1;
	}

	return 0;
}


//########## FPS�l���v���A�X�V����֐� ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS�l��`�悷��֐� ##########
VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS�l���v�����A�҂֐� ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
	}
	return;
}

//########## �L�[�̓��͏�Ԃ��X�V����֐� ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{

	char TempKey[256];	//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//���O�͉����Ă���
		&& AllKeyState[KEY_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�L�[�������グ�Ă���
	}
	else
	{
		return FALSE;	//�L�[�������グ�Ă��Ȃ�
	}
}

//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
//���@���Fint�F�L�[�����������鎞��
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

//�}�E�X�̓��͏����X�V����
VOID MY_MOUSE_UPDATE(VOID)
{
	//�}�E�X�̈ȑO�̍��W���擾
	mouse.OldPoint = mouse.Point;

	//�}�E�X�̈ȑO�̃{�^�����͂��擾
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//�}�E�X�̍��W���擾
	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	//�}�E�X�̉����Ă���{�^�����擾
	mouse.InputValue = GetMouseInput();

	//���{�^���������Ă��邩�`�F�b�N(TRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }		//�����Ă���
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }		//�����Ă��Ȃ�

	//���{�^���������Ă��邩�`�F�b�N(TRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }	//�����Ă���
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }	//�����Ă��Ȃ�

	//�E�{�^���������Ă��邩�`�F�b�N(TRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }		//�����Ă���
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }	//�����Ă��Ȃ�

	//�z�C�[���̉�]�ʂ��擾
	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

//�{�^���������Ă��邩�A�}�E�X�[�R�[�h�Ŕ��f����
//���@���Fint�F�}�E�X�R�[�h�FMOUSE_INPUT_???
BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h�̃{�^���������Ă��鎞
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;	//�{�^���������Ă���
	}
	else
	{
		return FALSE;	//�{�^���������Ă��Ȃ�
	}
}

//�{�^���������グ�����A�}�E�X�R�[�h���f����
//���@���Fint�F�}�E�X�R�[�h�FMOUSE_INPUT_???
BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1	//���O�͉����Ă���
		&& mouse.Button[MOUSE_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�{�^���������グ�Ă���
	}
	else
	{
		return FALSE;	//�{�^���������グ�Ă��Ȃ�
	}
}

//�{�^�������������Ă��邩�A�}�E�X�R�[�h���f����
//���@���Fint�F�}�E�X�R�[�h�FMOUSE_INPUT_???
//���@���Fint�F�{�^�������������鎞��
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//�t�H���g��ǂݍ��ފ֐�

BOOL MY_FONT_CREATE(VOID)
{
	//���������ʂ������}�W�b�N�̃t�H���g���쐬������

	//�t�H���g�f�[�^���쐬
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);	//�p�X���R�s�[
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	//�t�H���g�����R�s�[
	FontTanu32.handle = -1;								//�n���h����������
	FontTanu32.size = 32;								//�T�C�Y��32
	FontTanu32.bold = 1;								//����1
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//�A���`�G�C���A�V���O�t���̃t�H���g

	//�t�H���g�n���h���쐬
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	//�t�H���g�n���h���쐬�ł��Ȃ��Ƃ��A�G���[
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }


	return TRUE;
}

//�t�H���g���폜����֐�
VOID MY_FONT_DELETE(VOID)
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(FontTanu32.handle);	//�t�H���g�̃n���h�����폜

	return;
}

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	//�X�y�[�X�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(FALSE);			//�}�E�X�J�[�\�����\��

		//�v���C���[�̒��S�ʒu���v�Z����
		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		//�v���C���[�̉摜�̈ʒu��ݒ肷��
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		//�X�^�[�g�ʒu���}�E�X�̈ʒu�ɂ���
		SetMousePoint(player.image.x, player.image.y);


		//�Q�[���̏I����Ԃ�����������
		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_PLAY;
	}



	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{


	//�w�i��`��
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);	//�^�C�g���w�i�̕`��


	//�_��
	if (ImageTitleSTART.IsDraw == TRUE)
	{
		//�^�C�g���X�^�[�g�̕`��
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	DrawString(0, 0, "�X�^�[�g���(�X�y�[�X�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}
//�v���C���(������)
VOID MY_PLAY_INIT(VOID)
{
	// �`��ʒu�̏����ʒu�Z�b�g
	DrawPointX = 0;
	DrawPointY = 0;

	// �Q�ƕ����ʒu���Z�b�g
	RowPos = 0;	// �P�s�ڂ�
	ColPos = 0;	// �O����

	// �I���t���O��|��
	EndFlag = FALSE;

	//�f�t�H���g�̃t�H���g�T�C�Y���擾
	DefaultFontSize = GetFontSize();

	//���������ɂ���
	OneMojiBuf[0] = '\0';
	OneMojiBuf[1] = '\0';
	OneMojiBuf[2] = '\0';

	for (int i = 0; i < STR_DRAW_ROW_MAX; i++)
	{
		for (int j = 0; j < STR_COL_MAX; j++)
		{
			DrawStringBuf[i][j] = '\0';
		}
	}

	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

}

VOID MY_PLAY_PROC(VOID)
{
	if (MY_KEY_DOWN(KEY_INPUT_1) == TRUE)
	{

		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_IBENTO;
	}

	if (EndFlag == FALSE)
	{
		//����������`��
		NovelProc(Story);
	}

}
//���������񏈗��֐�
//�����ŁA�`�悳�������������������Ă���
VOID NovelProc(char str[][STR_COL_MAX])
{
	switch (str[RowPos][ColPos])	//�������P�擾
	{
	case '@':	// ���s����

		// ���s��������юQ�ƕ����ʒu����i�߂�
		Kaigyou();
		ColPos++;	//���̕�����ǂݎ��

		break;

	case 'B':	// �{�^�������҂�����

		//�{�^���������ꂽ��A���̕��͂�
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE) { ColPos++; }

		break;

	case 'Q':	// ���╶��

		//2�{�^���������ꂽ�Ƃ�
		if (MY_KEY_DOWN(KEY_INPUT_2) == TRUE)
		{
			//�ŏ���2����n�܂镶�͂�T��
			for (int i = 0; i < STR_ROW_MAX; i++)
			{
				if (str[i][0] == '2')
				{
					RowPos = i;
					ColPos = 1;
					break;
				}
			}
		}

		//3�{�^���������ꂽ�Ƃ�
		if (MY_KEY_DOWN(KEY_INPUT_3) == TRUE)
		{
			//�ŏ���3����n�܂镶�͂�T��
			for (int i = 0; i < STR_ROW_MAX; i++)
			{
				if (str[i][0] == '3')
				{
					RowPos = i;
					ColPos = 1;
					break;
				}
			}
		}

		break;

	case 'X':	// ���₩��߂��Ă��镶��

		//�{�^���������ꂽ��A���̕��͂�
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		{
			//�ŏ���X����n�܂镶�͂�T��
			for (int i = 0; i < STR_ROW_MAX; i++)
			{
				if (str[i][0] == 'X')
				{
					RowPos = i;
					ColPos = 1;
					break;
				}
			}
		}

		break;

	case 'E':	// �I������

		// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
		EndFlag = TRUE;
		ColPos++;	//���̕�����ǂݎ��

		break;

	case 'C':	// �N���A����

		//�`�悵�Ă��镶�������ɂ���
		for (int i = 0; i < STR_DRAW_ROW_MAX; i++)
		{
			for (int j = 0; j < STR_COL_MAX; j++)
			{
				DrawStringBuf[i][j] = '\0';
			}
		}

		//�����̈ʒu��������
		DrawPointY = 0;
		DrawPointX = 0;
		ColPos++;

		break;

	default:	// ���̑��̕���

		//�`��^�C�~���O���v�Z
		if (DrawSpeedCnt < DrawSpeedCntMax)
		{
			DrawSpeedCnt++;
		}
		else
		{
			// �P�����������o��
			OneMojiBuf[0] = str[RowPos][ColPos];
			OneMojiBuf[1] = str[RowPos][ColPos + 1];
			OneMojiBuf[2] = '\0';

			// ���������������
			strcat_s(DrawStringBuf[DrawPointY], OneMojiBuf);

			// �Q�ƕ����ʒu���Q�o�C�g�i�߂�
			ColPos += 2;

			// �J�[�\�����ꕶ�����i�߂�
			DrawPointX++;

			// ��ʂ���͂ݏo������s����
			if (DrawPointX * STR_DRAW_SIZE + STR_DRAW_SIZE > rectString.right)
			{
				Kaigyou();
			}

			DrawSpeedCnt = 0;
		}

		break;
	}

	// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
	if (str[RowPos][ColPos] == '\0')
	{
		RowPos++;
		ColPos = 0;
	}

	return;
}

VOID MY_PLAY_DRAW(VOID)
{
DrawGraph(Image.x, Image.y, Image.handle, TRUE);
		DrawGraph(karikyara.x, karikyara.y, karikyara.handle, TRUE);

		//�������`��
		NovelDraw();

	return;

		
}

//�C�x���g���
VOID MY_IBENTO(VOID)
{
	MY_IBENTO_PROC();	//�v���C��ʂ̏���
	MY_IBENTO_DRAW();	//�v���C��ʂ̕`��
	return;
}

//�C�x���g��ʂ̏���
VOID MY_IBENTO_PROC(VOID)
{

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);	//50%�̉��ʂɂ���

		//BGM�𗬂�
		//DX_PLAYTYPE_NORMAL:�@�m�[�}���Đ�
		//DX_PLAYTYPE_BACK  : �o�b�N�O���E���h�Đ�
		//DX_PLAYTYPE_LOOP  : ���[�v�Đ�
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//�}�E�X���E�N���b�N����ƁA�^�C�g����ʂɖ߂�
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//�N���b�N�������W���擾���Ă���
		iPOINT R_ClickPt = mouse.Point;

		//�}�E�X��\��
		SetMouseDispFlag(TRUE);

		//�I���_�C�A���O��\��
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YES�Ȃ�A�Q�[���𒆒f����
		{
			//BGM������Ă���Ȃ�
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);	//BGM���~�߂�
			}

			SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

			//�����I�Ƀ^�C�g����ʂɔ��
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NO�Ȃ�A�Q�[���𑱍s����
		{
			//�}�E�X�̈ʒu���A�N���b�N����O�ɖ߂�
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//�}�E�X���\���ɂ���B
			SetMouseDispFlag(FALSE);
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_UP))
	{
		player.CenterY -= CHARA_RELOAD_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll))
		{
			player.CenterY += CHARA_RELOAD_MIDI;
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_DOWN))
	{
		player.CenterY += CHARA_RELOAD_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll))
		{
			player.CenterY += CHARA_RELOAD_MIDI;
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_RIGHT))
	{
		player.CenterX += CHARA_RELOAD_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll))
		{
			player.CenterY += CHARA_RELOAD_MIDI;
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_LEFT))
	{
		player.CenterX -= CHARA_RELOAD_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll))
		{
			player.CenterY += CHARA_RELOAD_MIDI;
		}
	}

	//�v���C���[�̓����蔻��̐ݒ�
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//�v���C���[�ƃ}�b�v���������Ă�����
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		IsMove = FALSE;
	}

	if (IsMove == TRUE)
	{
		//��ʓ��Ƀ}�E�X�������
		if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
			&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
		{
			//�v���C���[�̈ʒu�ɒu��������
			player.image.x = player.CenterX - player.image.width / 2;
			player.image.y = player.CenterY - player.image.height / 2;

			//�������Ă��Ȃ��Ƃ��̍��W���擾
			player.collBeforePt.x = player.CenterX;
			player.collBeforePt.y = player.CenterY;
		}
	}

	RECT PlayerRect;
	int CollRange = 5;	//�����蔻��͈̔�
	PlayerRect.left = player.image.x + player.image.width / 2 - CollRange;
	PlayerRect.top = player.image.y + player.image.height / 2 - CollRange;
	PlayerRect.right = player.image.x + player.image.width / 2 + CollRange;
	PlayerRect.bottom = player.image.y + player.image.height / 2 + CollRange;

	//�S�[���ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_COMP;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//�v���C���[����ʊO�ɏo����
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����t�H�[���g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}


	//�w�i�摜�𓮂���
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		//�摜���ړ�������
		ImageBack[num].image.x++;

		//�w�i�摜��`��ł��Ȃ��Ƃ�
		if (ImageBack[num].IsDraw == FALSE)
		{
			//�w�i�摜����ʓ��ɂ���Ƃ�
			if (ImageBack[num].image.x + ImageBack[num].image.width > 0)
			{
				ImageBack[num].IsDraw = TRUE;	//�摜��`�悷��
			}
		}

		//�w�i�摜����ʂ�ʂ�z�����Ƃ�
		if (ImageBack[num].image.x > GAME_WIDTH)
		{
			ImageBack[num].image.x = 0 - ImageBack[0].image.width* 4;	//�摜�̍����Q���A��Ɉړ�������
			ImageBack[num].IsDraw = FALSE;								//�摜��`�悵�Ȃ�
		}
	}

	return;
}

//�C�x���g�̕`��
VOID MY_IBENTO_DRAW(VOID)
{
	//�w�i��`�悷��
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		//�`��ł���Ƃ��́E�E�E
		if (ImageBack[num].IsDraw == TRUE)
		{
			//�w�i��`��
			DrawGraph(ImageBack[num].image.x, ImageBack[num].image.y, ImageBack[num].image.handle, TRUE);

			//�w�i�摜�̐������e�X�g�I�ɕ\��
			DrawFormatString(
				ImageBack[num].image.x,
				ImageBack[num].image.y,
				GetColor(255, 255, 255), "�w�i�摜�F%d", num + 1);
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v��`��
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}



	//�v���C���[�̂�`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);




	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	//�G�X�P�[�v�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);	//BGM���~�߂�
		}

		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);		//�}�E�X�J�[�\����\��

		GameScene = GAME_SCENE_START;

		return;
	}

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//�R���v���[�g�̂Ƃ�

		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(BGM_COMP.handle) == 0)
		{
			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_COMP.handle);	//50%�̉��ʂɂ���
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}

		//�R���v���[�g��_��
		if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		{
			ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		}
		else
		{
			//�`�悷��/���Ȃ������߂�
			if (ImageEndCOMP.IsDraw == FALSE)
			{
				ImageEndCOMP.IsDraw = TRUE;
			}
			else if (ImageEndCOMP.IsDraw == TRUE)
			{
				ImageEndCOMP.IsDraw = FALSE;
			}
			ImageEndCOMP.Cnt = 0;
		}
		break;

	case GAME_END_FAIL:
		//�t�H�[���g�̂Ƃ�

		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(BGM_FAIL.handle) == 0)
		{
			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_FAIL.handle);	//50%�̉��ʂɂ���
			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		//�t�H�[���g��_��
		if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		{
			ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		}
		else
		{
			//�`�悷��/���Ȃ������߂�
			if (ImageEndFAIL.IsDraw == FALSE)
			{
				ImageEndFAIL.IsDraw = TRUE;
			}
			else if (ImageEndFAIL.IsDraw == TRUE)
			{
				ImageEndFAIL.IsDraw = FALSE;
			}
			ImageEndFAIL.Cnt = 0;
		}
		break;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	
	//�Q�[���̏I����Ԃɂ��A�`���ς���
	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//�R���v���[�g�̂Ƃ�

		//�_��
		if (ImageEndCOMP.IsDraw == TRUE)
		{
			//�R���v���[�g�̕`��
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		}
		break;

	case GAME_END_FAIL:
		//�t�H�[���g�̂Ƃ�

		//�_��
		if (ImageEndFAIL.IsDraw == TRUE)
		{
			//�t�H�[���g�̕`��
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		}
		break;

	}

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�摜���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_IMAGE(VOID)
{
	//�^�C�g���w�i
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//�p�X�̐ݒ�
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//�ǂݍ���
	if (ImageTitleBK.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//�摜�̕��ƍ������擾
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//���E��������
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//�㉺��������

	//�v���C�w�i
	strcpy_s(Image.path, IMAGE_PLAY_BACK);			//�p�X�̐ݒ�
	Image.handle = LoadGraph(Image.path);			//�ǂݍ���
	if (Image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Image.handle, &Image.width, &Image.height);	//�摜�̕��ƍ������擾
	Image.x = GAME_WIDTH / 2 - Image.width / 2;		//���E��������
	Image.y = GAME_HEIGHT / 2 - Image.height / 2;		//�㉺��������

	//���L����
	strcpy_s(karikyara.path, KariKyara);			//�p�X�̐ݒ�
	karikyara.handle = LoadGraph(karikyara.path);			//�ǂݍ���
	if (karikyara.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), KariKyara, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(karikyara.handle, &karikyara.width, &karikyara.height);	//�摜�̕��ƍ������擾
	karikyara.x = GAME_WIDTH / 2 - karikyara.width / 2;		//���E��������
	karikyara.y = GAME_HEIGHT / 2 - karikyara.height / 2;		//�㉺��������

	//�G���h�R���v
	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);					//�p�X�̐ݒ�
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);			//�ǂݍ���
	if (ImageEndCOMP.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);	//�摜�̕��ƍ������擾
	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;			//���E��������
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2;			//�㉺��������
	ImageEndCOMP.Cnt = 0.0;									//�J�E���^
	ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;			//�J�E���^MAX
	ImageEndCOMP.IsDraw = FALSE;							//�`�悳���Ȃ�

	//�G���h�t�H�[��
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);				//�p�X�̐ݒ�
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);			//�ǂݍ���
	if (ImageEndFAIL.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);	//�摜�̕��ƍ������擾
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;			//���E��������
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2;			//�㉺��������
	ImageEndFAIL.Cnt = 0.0;									//�J�E���^
	ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;			//�J�E���^MAX
	ImageEndFAIL.IsDraw = FALSE;							//�`�悳���Ȃ�

	//�w�i�摜
	strcpy_s(ImageBack[0].image.path, IMAGE_BACK_PATH);			//�p�X�̐ݒ�
	strcpy_s(ImageBack[1].image.path, IMAGE_BACK_REV_PATH);		//�p�X�̐ݒ�(�w�i�摜���])
	strcpy_s(ImageBack[2].image.path, IMAGE_BACK_PATH);			//�p�X�̐ݒ�
	strcpy_s(ImageBack[3].image.path, IMAGE_BACK_REV_PATH);		//�p�X�̐ݒ�(�w�i�摜���])

	//�摜��A�����ēǂݍ���
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);	//�ǂݍ���
		if (ImageBack[num].image.handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�摜�̕��ƍ������擾
		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);
	}
	//�w�i�摜�@�̐ݒ�
	ImageBack[0].image.y = GAME_WIDTH / 2 - ImageBack[0].image.width / 2;	//���E��������
	ImageBack[0].image.x= 0 - ImageBack[0].image.height * 0;				//y�͌��_����
	ImageBack[0].IsDraw = FALSE;

	//�w�i�摜�A�̐ݒ�
	ImageBack[1].image.y = GAME_WIDTH / 2 - ImageBack[1].image.width/2 ;	//���E��������
	ImageBack[1].image.x = 0 - ImageBack[0].image.height * 1;				//�摜�̍����P���A��Ɉړ�������
	ImageBack[1].IsDraw = FALSE;

	//�w�i�摜�B�̐ݒ�
	ImageBack[2].image.y = GAME_WIDTH / 2 - ImageBack[2].image.width/2;	//���E��������
	ImageBack[2].image.x = 0 - ImageBack[0].image.height * 2;				//�摜�̍����Q���A��Ɉړ�������
	ImageBack[2].IsDraw = FALSE;

	//�w�i�摜�B�̐ݒ�
	ImageBack[3].image.y = GAME_WIDTH / 2 - ImageBack[2].image.width/2;	//���E��������
	ImageBack[3].image.x = 0 - ImageBack[0].image.height * 3;				//�摜�̍����R���A��Ɉړ�������
	ImageBack[3].IsDraw = FALSE;

	//�v���C���[�̉摜
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//�p�X�̐ݒ�
	player.image.handle = LoadGraph(player.image.path);	//�ǂݍ���
	if (player.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//�摜�̕��ƍ������擾
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//���E��������
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//�㉺��������
	player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��
	player.speed = CHARA_SPEED_LOW;									//�X�s�[�h��ݒ�



	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//�Ԓe�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//�Ԓe�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊�����̕��ƍ���
		&mapChip.handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map[tate][yoko].kind = mapData[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W��ݒ�
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[0].image.handle);
	}

	DeleteGraph(player.image.handle);
	DeleteGraph(Image.handle);
    DeleteGraph(karikyara.handle);
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleSTART.image.handle);
	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);
	


	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//���y���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_MUSIC(VOID)
{
	//�w�i���y
	strcpy_s(BGM.path, MUSIC_BGM_PATH);		//�p�X�̐ݒ�
	BGM.handle = LoadSoundMem(BGM.path);	//�ǂݍ���
	if (BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}



	//�^�C�g����BGM
	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);				//�p�X�̐ݒ�
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);			//�ǂݍ���
	if (BGM_TITLE.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�R���v���[�gBGM
	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);				//�p�X�̐ݒ�
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);				//�ǂݍ���
	if (BGM_COMP.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�t�H�[���g��BGM
	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);				//�p�X�̐ݒ�
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);				//�ǂݍ���
	if (BGM_FAIL.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
				if (map[tate][yoko].kind == k) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
}

//����������`��֐�
VOID NovelDraw(VOID)
{
	//������`�悷��Ƃ���
	if (EndFlag == FALSE)
	{
		//������`�悷��̈��`��(�������̎l�p��`��)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);	//�������ɂ���
		DrawBox(
			rectString.left,
			rectString.top,
			rectString.right,
			rectString.bottom,
			GetColor(255, 255, 255),
			TRUE
		);	//�l�p��`����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���ɖ߂�

		SetFontSize(STR_DRAW_SIZE);	//�m�x���̃t�H���g�̃T�C�Y�Z�b�g
		//�������`��
		for (int cnt = 0; cnt <= DrawPointY; cnt++)
		{
			DrawString(rectString.left, rectString.top + cnt * STR_DRAW_SIZE, DrawStringBuf[cnt], GetColor(0, 0, 0));
		}
		SetFontSize(DefaultFontSize);	//�m�x���̃t�H���g�����Ƃɖ߂�
	}
}