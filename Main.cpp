#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include "Stages.h"
#include "Control.h"



int main() {

	//�������̽� ����ü ���� �� �ʱ�ȭ ���ֱ�
	inter MAP[4];
	for (int i = 0; i < 4; i++)
		initStage(&MAP[i], i);

	for (int i = 0; i < 8; i++) {
		currentKeywords[i] = keywords[0][i];
	}

	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);


	drawStage(MAP[c_stage].TextInterface, 0, 0);
	drawStage(MAP[c_stage].ShopInterface, 40, 10);
	drawStage(MAP[c_stage].TextStored, 40, 0);
	drawStage(MAP[c_stage].S, 0, 10);

	set_character(&MAP[c_stage].S, start_arr[c_stage][0], start_arr[c_stage][1]); // ĳ���� ��ġ ����

	indicateTextline(MAP[c_stage].S, TextMatrix);

	seachmoving(&MAP[c_stage].S, 0, 10);

	int time = 0;

	initItems();


	/// ---------------------------------- ���� mod ����(�ӽ�)

// MAP[c_stage].S.stageinfo[58][1].mod = 0; // ���� mod��

	MAP[1].S.stageinfo[12][38].mod = 2; // ���� mod��
	MAP[1].S.stageinfo[16][38].mod = 2; // ���� mod��
	MAP[1].S.stageinfo[23][35].mod = 2; // ���� mod��
	MAP[1].S.stageinfo[31][17].mod = 1; // ���� mod��
	MAP[1].S.stageinfo[38][35].mod = 2; // ���� mod��
	MAP[1].S.stageinfo[45][17].mod = 1; // ���� mod��


	MAP[2].S.stageinfo[5][5].mod = 2; // ���� mod��

	MAP[2].S.stageinfo[46][1].mod = 1; // ���� mod��
	MAP[2].S.stageinfo[45][2].mod = 1; // ���� mod��
	MAP[2].S.stageinfo[44][3].mod = 1; // ���� mod��

	MAP[2].S.stageinfo[43][4].mod = 1; // ���� mod��
	MAP[2].S.stageinfo[42][5].mod = 1; // ���� mod��
	MAP[2].S.stageinfo[41][6].mod = 1; // ���� mod��

	



	MAP[2].S.NumofLines = 3;
	/// ------------------------------------

	indicateItems();

	keyWordindicator();


	while (1)
	{

		if (GetAsyncKeyState(0x50) & 0x8000) // ����׿� ġƮ. P�� ������ �������� Ŭ����
		{
			if (c_stage != 2 && c_stage != 3) {
				c_stage++; //�������� ���� ����
			}

			if (c_stage == 2) {
				// ����Ŭ����
			}

			if (c_stage == 3) {
				c_stage = 0;
			}
			seachmoving(&MAP[c_stage].S, 0, 10); //���� �������� �����̴� ��� Ž��
			stageclear(MAP);
		}


		if (dual == 0 && c_stage == 2) { //3���� �ʱ� ĳ�� ����
			dual = 1;
			textcolor(9); // �Ķ���
			setCursorPosition(2 * cur2_x, cur2_y - 2);
			printf("��");
			setCursorPosition(2 * cur2_x, cur2_y - 1);
			printf("��");
			setCursorPosition(2 * cur2_x, cur2_y);
			printf("��");
			textcolor(15);
		}

		keybord_input(MAP, &MAP[c_stage].S);
		check_cur2(&MAP[c_stage].S);



		CONSOLE_CURSOR_INFO curCursorInfo;
		GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
		curCursorInfo.bVisible = 0;
		SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);




		if (clear == MAP[c_stage].S.clearstar) { //���� �Ծ� Ŭ���Ÿ�� ������ ��������
			if (c_stage != 2 && c_stage != 3) {
				c_stage++; //�������� ���� ����
			}

			if (c_stage == 2) {
				// ����Ŭ����
			}

			if (c_stage == 3) {
				c_stage = 0;
			}

			seachmoving(&MAP[c_stage].S, 0, 10); //���� �������� �����̴� ��� Ž��
			stageclear(MAP); //���� ���������� �Ѿ�� �Լ�
			keyWordindicator();
			time_reset = 1;
		}
		else if (clear < 0) { // ���� ��
			gameover(&MAP[c_stage], &MAP[c_stage].S); //�ٽ� �����ϴ� �Լ�
			time_reset = 1;
		}

		if (isdeath == 1){
			gameover(&MAP[c_stage], &MAP[c_stage].S); //�ٽ� �����ϴ� �Լ�
			time_reset = 1;
		}
		Sleep(100);

		time++;
		shootrate = shootrate + 10;
		printshootrate();

		if (time % 1 == 0) { // ����ü ������Ʈ
			projectileUpdate(MAP, &MAP[c_stage].S);
		}

		if (time % 5 == 0) { // �� 0.5~1�� ��

			movingblock(&MAP[c_stage].S); //�����̴� �� �̵�
			check_cur2(&MAP[c_stage].S);

		}

		if (shootrate % 200 == 0) { // 2�ʸ��� �߻�
			shootrate = 0;
			shooting(&MAP[c_stage].S);
			check_cur2(&MAP[c_stage].S);
		}

		if (shootrate >= 201) { // 2�ʸ��� �߻�
			shootrate = 0;
			shooting(&MAP[c_stage].S);
			check_cur2(&MAP[c_stage].S);
		}

		itemAcquire(&MAP[c_stage].S, cur_x, cur_y);
		to_jump(&MAP[c_stage].S);//���� ĳ���Ͱ� ���� ���̿��ٸ� ������ �ݿ��Ͽ� ��ġ ����
		gravity(&MAP[c_stage].S);//ĳ���Ͱ� �������� �ƴϸ鼭 ���߿� ������ �߷¿� ���� 1ĭ�� ������
		to_fall(&MAP[c_stage].S);
		to_float(&MAP[c_stage].S);
		gravityPlatform(&MAP[c_stage].S, 8);

		draw_character(&MAP[c_stage].S, cur_x, cur_y);
		check_cur2(&MAP[c_stage].S);


		time_check();

	}

	return 0;
}