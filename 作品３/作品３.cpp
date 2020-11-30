/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�V�[���̒ǉ�

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "��i�R.h"

//########## �}�N����` ##########
#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS			60	//FPS�̐��l	

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129		//0x0000�`0x0080�܂�

//�t�H���g�̃p�X�̒���
#define FONT_PATH_MAX			255	//255�����܂�

//�t�H���g
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")


enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��


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
	char path[FONT_PATH_MAX];	//�p�X
	char name[FONT_PATH_MAX];	//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v

}FONT;

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


//########## �v���g�^�C�v�錾 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
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

VOID MY_PLAY(VOID);			//�v���C���
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��


//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	

	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��	

	int DrawX = 0;	//�\���ʒuX
	int DrawY = 0;	//�\���ʒuY

	iPOINT InputFirst = { 0,0 };	//�n�_
	iPOINT InputEnd = { 0,0 };		//�I�_
	BOOL IsMouseDownLeft = FALSE;	//�}�E�X�̍��{�^������������


	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���


	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

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

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

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
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
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


//���@���Fint�F�{�^�������������鎞��
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
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
	//�G���^�[�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{

	DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	//�X�y�[�X�L�[����������A�G���h�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		GameScene = GAME_SCENE_END;
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{

	DrawString(0, 0, "�v���C���(�X�y�[�X�L�[�������ĉ�����)", GetColor(255, 255, 255));
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
		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

