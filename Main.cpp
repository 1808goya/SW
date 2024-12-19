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

	//인터페이스 구조체 선언 및 초기화 해주기
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

	set_character(&MAP[c_stage].S, start_arr[c_stage][0], start_arr[c_stage][1]); // 캐릭터 위치 설정

	indicateTextline(MAP[c_stage].S, TextMatrix);

	seachmoving(&MAP[c_stage].S, 0, 10);

	int time = 0;

	initItems();


	/// ---------------------------------- 함정 mod 세팅(임시)

// MAP[c_stage].S.stageinfo[58][1].mod = 0; // 함정 mod용

	MAP[1].S.stageinfo[12][38].mod = 2; // 함정 mod용
	MAP[1].S.stageinfo[16][38].mod = 2; // 함정 mod용
	MAP[1].S.stageinfo[23][35].mod = 2; // 함정 mod용
	MAP[1].S.stageinfo[31][17].mod = 1; // 함정 mod용
	MAP[1].S.stageinfo[38][35].mod = 2; // 함정 mod용
	MAP[1].S.stageinfo[45][17].mod = 1; // 함정 mod용


	MAP[2].S.stageinfo[5][5].mod = 2; // 함정 mod용

	MAP[2].S.stageinfo[46][1].mod = 1; // 함정 mod용
	MAP[2].S.stageinfo[45][2].mod = 1; // 함정 mod용
	MAP[2].S.stageinfo[44][3].mod = 1; // 함정 mod용

	MAP[2].S.stageinfo[43][4].mod = 1; // 함정 mod용
	MAP[2].S.stageinfo[42][5].mod = 1; // 함정 mod용
	MAP[2].S.stageinfo[41][6].mod = 1; // 함정 mod용

	



	MAP[2].S.NumofLines = 3;
	/// ------------------------------------

	indicateItems();

	keyWordindicator();


	while (1)
	{

		if (GetAsyncKeyState(0x50) & 0x8000) // 디버그용 치트. P를 누르면 스테이지 클리어
		{
			if (c_stage != 2 && c_stage != 3) {
				c_stage++; //스테이지 변수 증가
			}

			if (c_stage == 2) {
				// 최종클리어
			}

			if (c_stage == 3) {
				c_stage = 0;
			}
			seachmoving(&MAP[c_stage].S, 0, 10); //다음 스테이지 움직이는 블록 탐지
			stageclear(MAP);
		}


		if (dual == 0 && c_stage == 2) { //3스테 초기 캐릭 생성
			dual = 1;
			textcolor(9); // 파란색
			setCursorPosition(2 * cur2_x, cur2_y - 2);
			printf("○");
			setCursorPosition(2 * cur2_x, cur2_y - 1);
			printf("□");
			setCursorPosition(2 * cur2_x, cur2_y);
			printf("∥");
			textcolor(15);
		}

		keybord_input(MAP, &MAP[c_stage].S);
		check_cur2(&MAP[c_stage].S);



		CONSOLE_CURSOR_INFO curCursorInfo;
		GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
		curCursorInfo.bVisible = 0;
		SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);




		if (clear == MAP[c_stage].S.clearstar) { //별을 먹어 클리어스타의 갯수와 같아지면
			if (c_stage != 2 && c_stage != 3) {
				c_stage++; //스테이지 변수 증가
			}

			if (c_stage == 2) {
				// 최종클리어
			}

			if (c_stage == 3) {
				c_stage = 0;
			}

			seachmoving(&MAP[c_stage].S, 0, 10); //다음 스테이지 움직이는 블록 탐지
			stageclear(MAP); //다음 스테이지로 넘어가는 함수
			keyWordindicator();
			time_reset = 1;
		}
		else if (clear < 0) { // 죽을 시
			gameover(&MAP[c_stage], &MAP[c_stage].S); //다시 시작하는 함수
			time_reset = 1;
		}

		if (isdeath == 1){
			gameover(&MAP[c_stage], &MAP[c_stage].S); //다시 시작하는 함수
			time_reset = 1;
		}
		Sleep(100);

		time++;
		shootrate = shootrate + 10;
		printshootrate();

		if (time % 1 == 0) { // 투사체 업데이트
			projectileUpdate(MAP, &MAP[c_stage].S);
		}

		if (time % 5 == 0) { // 약 0.5~1초 후

			movingblock(&MAP[c_stage].S); //움직이는 블럭 이동
			check_cur2(&MAP[c_stage].S);

		}

		if (shootrate % 200 == 0) { // 2초마다 발사
			shootrate = 0;
			shooting(&MAP[c_stage].S);
			check_cur2(&MAP[c_stage].S);
		}

		if (shootrate >= 201) { // 2초마다 발사
			shootrate = 0;
			shooting(&MAP[c_stage].S);
			check_cur2(&MAP[c_stage].S);
		}

		itemAcquire(&MAP[c_stage].S, cur_x, cur_y);
		to_jump(&MAP[c_stage].S);//만약 캐릭터가 점프 중이였다면 점프를 반영하여 위치 변경
		gravity(&MAP[c_stage].S);//캐릭터가 점프중이 아니면서 공중에 있으면 중력에 의해 1칸씩 내려옴
		to_fall(&MAP[c_stage].S);
		to_float(&MAP[c_stage].S);
		gravityPlatform(&MAP[c_stage].S, 8);

		draw_character(&MAP[c_stage].S, cur_x, cur_y);
		check_cur2(&MAP[c_stage].S);


		time_check();

	}

	return 0;
}