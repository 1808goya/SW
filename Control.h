#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Stages.h"

int cur_x = 10 / 2, cur_y = 1; // 캐릭터의 '발'의 좌표
int cur2_x = 30, cur2_y = 68; //캐릭터2의 '발'의 좌표
int cur2 = 0; //캐릭 통과상태일때 겹칠때 확인용
int dual = 0; //캐릭 스위치를 위한 변수, 0이면 캐릭1명, 1이면 2명인데 그중 1, 2면 2명인데 그중 2
int right = 0, left = 0; // 점프 방향
int jump_height = 0; // 점프 유무를 나타내는 동시에 점프를 뛴 후 앞으로 얼마나 더 올라가야 하는지를 나타내는 변수입니다.
int jump_and_falling = 0; //점프로 최고 높이에 도착한 후 다시 내려 올 때의 상황에서 사용할 변수
int control_gravity = 1; // 1은 아래로, 2는 왼쪽으로
int x1 = 1; // x1과 x2는 키워드 교체 인디케이터에 사용됨
int y1 = 0;
int isfalling = 0;
int isStarfalling = 0;
int clear = 0; //클리어와 게임오버 변수
int bonus = 0, c_bonus = 0; //총 보너스, 현 스테이지 에서 먹은 bonus 변수
int m[4][10], M = 0; //움직이는 블럭 관련 배열
int ispush = 0; //push키워드 0이면 작동안함 1이면 작동
int Mispush = 0; //push키워드 - Machine에 적용
int Misfalling = 0; //fall, float키워드 - Machine에 적용
int time_reset = 0;
int isdeath = 0;

int shootrate = 0;


int isCharacterThere(int x, int y) { // Stageinfo와 캐릭터와의 위치를 비교해서 '해당 칸'에 캐릭터의 판정이 있는지 확인
	// 1이면 캐릭터의 판정이 있고, 0이면 없음. 중력에 따라 판정이 바뀌는것도 계산함

	int R = 0;

	if (control_gravity == 1) { // 중력 아래
		for (int i = 0; i < 3; i++) {
			if (cur_x == x && (cur_y - 10 - i) == y) {
				R = 1;
			}
		}
	}
	else if (control_gravity == 2) { // 중력 왼쪽
		for (int i = 0; i < 3; i++) {
			if (cur_x == x + i && (cur_y - 10) == y) {
				R = 1;
			}
		}
	}
	else if (control_gravity == 3) {

	}
	else if (control_gravity == 4) {

	}

	return R;
}


void draw_character(Stage* S, int x, int y) { // x,y에 캐릭터의 '맨 밑(다리) 부분' 생성

	drawStage(*S, 0, 10);
	if (control_gravity == 1)
	{
		if (dual == 0) {
			setCursorPosition(2 * x, y - 2);
			printf("○");
			setCursorPosition(2 * x, y - 1);
			printf("▣");
			setCursorPosition(2 * x, y);
			printf("∥");
		}
		else if (dual == 1) {
			textcolor(12); // 빨간색
			setCursorPosition(2 * x, y - 2);
			printf("○");
			setCursorPosition(2 * x, y - 1);
			printf("▣");
			setCursorPosition(2 * x, y);
			printf("∥");
			textcolor(15); // 다시 하얀색으로
		}
		else {
			textcolor(9); // 파란색
			setCursorPosition(2 * x, y - 2);
			printf("○");
			setCursorPosition(2 * x, y - 1);
			printf("▣");
			setCursorPosition(2 * x, y);
			printf("∥");
			textcolor(15); // 다시 하얀색으로
		}
	}

	if (control_gravity == 2)
	{
		setCursorPosition(2 * (x + 2), y);
		printf("○");
		setCursorPosition(2 * (x + 1), y);
		printf("▣");
		setCursorPosition(2 * x, y);
		printf("〓");
	}
	// S->stageinfo[y][x].n2 = 7; // 캐릭터 위치 표시
}

void check_cur2(Stage* S) {
	if (c_stage == 2) {
		if (S->stageinfo[cur2_y - 10][cur2_x].n3 != 0 || S->stageinfo[cur2_y - 11][cur2_x].n3 != 0 || S->stageinfo[cur2_y - 12][cur2_x].n3 != 0)
			cur2 = 1;
		if (cur_x == cur2_x && cur_y >= cur2_y - 2 && cur_y <= cur2_y + 2)
			cur2 = 2;

		if (cur2 == 1 && S->stageinfo[cur2_y - 10][cur2_x].n3 == 0 && S->stageinfo[cur2_y - 11][cur2_x].n3 == 0 && S->stageinfo[cur2_y - 12][cur2_x].n3 == 0) {
			cur2 = 0;
			if (dual == 1) {
				textcolor(9); // 파란색
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("○");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("□");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("∥");
				textcolor(15); // 다시 하얀색으로
			}
			else {
				textcolor(12); // 빨간색
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("○");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("□");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("∥");
				textcolor(15); // 다시 하얀색으로
			}
		}

		if (cur2 == 2 && ((cur_x != cur2_x) || (cur_y < cur2_y - 2 && cur_y > cur2_y + 2))) {
			cur2 = 0;
			if (dual == 1) {
				textcolor(9); // 파란색
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("○");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("□");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("∥");
				textcolor(15); // 다시 하얀색으로
			}
			else {
				textcolor(12); // 빨간색
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("○");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("□");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("∥");
				textcolor(15); // 다시 하얀색으로
			}
		}
	}
}

void draw_ready_to_jump_character(Stage* S, int x, int y)// 입력받은 x, y좌표에 입력 받은 캐릭터 모양 출력
{
	drawStage(*S, 0, 10);
	if (control_gravity == 1)
	{
		setCursorPosition(2 * x, y - 2); //코드 완성되면 제거 할지 확인
		printf("  ");
		setCursorPosition(2 * x, y - 1);
		printf("○");
		setCursorPosition(2 * x, y);
		printf("▣");
	}
	if (control_gravity == 2)
	{
		setCursorPosition(2 * (x + 2), y);
		printf("  ");
		setCursorPosition(2 * (x + 1), y);
		printf("○");
		setCursorPosition(2 * x, y);
		printf("▣");
	}
	return;
}

void clear_character(Stage* S, int x, int y) {
	if (control_gravity == 1)
	{
		if (S->stageinfo[y - 10][x].n2 != 0 || S->stageinfo[y - 11][x].n2 != 0 || S->stageinfo[y - 12][x].n2 != 0) { //이거 왜 있지?
			S->stageinfo[y - 12][x].n3 = 0;
			S->stageinfo[y - 11][x].n3 = 0;
			S->stageinfo[y - 10][x].n3 = 0;
		}
		setCursorPosition(2 * x, y - 2);
		printf("  ");
		setCursorPosition(2 * x, y - 1);
		printf("  ");
		setCursorPosition(2 * x, y);
		printf("  ");
	}

	if (control_gravity == 2)
	{
		if (S->stageinfo[y - 10][x].n2 != 0 || S->stageinfo[y - 10][x + 1].n2 != 0 || S->stageinfo[y - 10][x + 2].n2 != 0) {
			S->stageinfo[y - 10][x + 2].n3 = 0;
			S->stageinfo[y - 10][x + 1].n3 = 0;
			S->stageinfo[y - 10][x].n3 = 0;
		}
		setCursorPosition(2 * (x + 2), y);
		printf("  ");
		setCursorPosition(2 * (x + 1), y);
		printf("  ");
		setCursorPosition(2 * x, y);
		printf("  ");
	}
}

void set_character(Stage* S, int x, int y) { // 캐릭터의 위치를 바꾸고, 그에 따라 (다리의) 좌표 또한 조정해줌

	// S->stageinfo[y][x].n2 = 7; // 새 위치 설정
	cur_x = x;
	cur_y = y;
	draw_character(S, cur_x, cur_y);
}

void set_Block(Stage* S, int x, int y) { // 캐릭터의 위치를 바꾸고, 그에 따라 (다리의) 좌표 또한 조정해줌

	// S->stageinfo[y][x].n2 = 7; // 새 위치 설정
	cur_x = x;
	cur_y = y;
	draw_character(S, cur_x, cur_y);
}

int isCollision(Stage* S, int x, int y) { // x,y가 충돌판정을 가지는지 return
	y = y - 10;

	if (S->stageinfo[y][x].isSolid == 1) { // 충돌판정이 있으면 1 반환, -10을 해주는 이유는 인터페이스때문에 실제 스테이지의 좌표는 10만큼 아래에 있기 때문
		if (S->stageinfo[y][x].n2 == 14 || S->stageinfo[y][x].n2 == 15 || S->stageinfo[y][x].n2 == 16) {
			clear--;
		}
		return 1;
	}

	return 0; // 아니면 0 반환

}

int isCollisionforblock(Stage* S, int x, int y) { // x,y가 충돌판정을 가지는지 return

	if (S->stageinfo[y][x].isSolid == 1) { // 충돌판정이 있으면 1 반환
		return 1;
	}

	return 0; // 아니면 0 반환

}

int isblockCollision(Stage* S, int x, int y) { // x,y가 충돌판정을 가지는지 return

	if (S->stageinfo[y][x].isSolid == 1) { // 충돌판정이 있으면 1 반환, -10을 해주는 이유는 인터페이스때문에 실제 스테이지의 좌표는 10만큼 아래에 있기 때문
		return 1;
	}

	return 0; // 아니면 0 반환
}

void to_push(Stage* S, int pre_x, int pre_y)
{
	if (control_gravity == 1)
	{
		if (ispush == 1) {
			if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x, pre_y - 1) == 0 && isCollision(S, pre_x, pre_y - 2) == 0) { // 충돌판정이 없으면
				clear_character(S, cur_x, cur_y); //현 캐릭터 삭제
				set_character(S, pre_x, pre_y); // 캐릭터를 해당 좌표로 이동
			}

			else if (isCollision(S, pre_x, pre_y) == 1 || isCollision(S, pre_x, pre_y - 1) == 1 || isCollision(S, pre_x, pre_y - 2) == 1)
			{
				pre_y -= 10;
				int did_move = 0;


				if (S->stageinfo[pre_y][pre_x].n3 == 11 || S->stageinfo[pre_y][pre_x].n3 == 12) //캐릭터가 이동 시에 충돌 하는데 채워진 파란 블록 또는 빨간 블록을 만났을 시
				{

					if (pre_x > cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 작음 = 오른쪽으로 이동중
					{
						if (isblockCollision(S, pre_x + 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x + 1].n2 = S->stageinfo[pre_y][pre_x].n2;//오른쪽 이동 시 채워진 파란 블록or 빨간블록을 오른쪽으로
							S->stageinfo[pre_y][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 큼 = 왼쪽으로 이동중
					{
						if (isblockCollision(S, pre_x - 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x - 1].n2 = S->stageinfo[pre_y][pre_x].n2;//왼쪽 이동 시 채워진 파란 블록or 빨간블록을 왼쪽으로
							S->stageinfo[pre_y][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 1][pre_x].n3 == 11 || S->stageinfo[pre_y - 1][pre_x].n3 == 12) //캐릭터가 이동 시에 충돌 하는데 채워진 파란 블록 또는 빨간 블록을 만났을 시
				{

					if (pre_x > cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 작음 = 오른쪽으로 이동중
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x + 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//오른쪽 이동 시 채워진 파란 블록or 빨간블록을 오른쪽으로
							S->stageinfo[pre_y - 1][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 큼 = 왼쪽으로 이동중
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x - 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//왼쪽 이동 시 채워진 파란 블록or 빨간블록을 왼쪽으로
							S->stageinfo[pre_y - 1][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 2][pre_x].n3 == 11 || S->stageinfo[pre_y - 1][pre_x].n3 == 12) //캐릭터가 이동 시에 충돌 하는데 채워진 파란 블록 또는 빨간 블록을 만났을 시
				{

					if (pre_x > cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 작음 = 오른쪽으로 이동중
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x + 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//오른쪽 이동 시 채워진 파란 블록or 빨간블록을 오른쪽으로
							S->stageinfo[pre_y - 2][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 2][pre_x].n2 = 0;
							S->stageinfo[pre_y - 2][pre_x].isSolid = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 큼 = 왼쪽으로 이동중
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x - 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//왼쪽 이동 시 채워진 파란 블록or 빨간블록을 왼쪽으로
							S->stageinfo[pre_y - 2][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y - 2][pre_x].n2 = 0;
							S->stageinfo[pre_y - 2][pre_x].isSolid = 0;
							did_move += 1;
						}
					}
				}
				drawStage(*S, 0, 10);
				if (did_move > 0)
					to_push(S, pre_x, pre_y + 10);
			}
		}


		//-------------------------------------------------------------- MACHINE에 적용되는 경우

		if (Mispush == 1) {
			if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x, pre_y - 1) == 0 && isCollision(S, pre_x, pre_y - 2) == 0) { // 충돌판정이 없으면
				clear_character(S, cur_x, cur_y); //현 캐릭터 삭제
				set_character(S, pre_x, pre_y); // 캐릭터를 해당 좌표로 이동
			}

			else if (isCollision(S, pre_x, pre_y) == 1 || isCollision(S, pre_x, pre_y - 1) == 1 || isCollision(S, pre_x, pre_y - 2) == 1)
			{
				pre_y -= 10;
				int did_move = 0;


				if (S->stageinfo[pre_y][pre_x].n3 == 10) //캐릭터가 이동 시에 충돌 하는데 채워진 파란 블록 또는 빨간 블록을 만났을 시
				{

					if (pre_x > cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 작음 = 오른쪽으로 이동중
					{
						if (isblockCollision(S, pre_x + 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x + 1].n2 = S->stageinfo[pre_y][pre_x].n2;//오른쪽 이동 시 채워진 파란 블록or 빨간블록을 오른쪽으로
							S->stageinfo[pre_y][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;

							S->stageinfo[pre_y][pre_x + 1].mod = S->stageinfo[pre_y][pre_x].mod;
							S->stageinfo[pre_y][pre_x].mod = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 큼 = 왼쪽으로 이동중
					{
						if (isblockCollision(S, pre_x - 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x - 1].n2 = S->stageinfo[pre_y][pre_x].n2;//왼쪽 이동 시 채워진 파란 블록or 빨간블록을 왼쪽으로
							S->stageinfo[pre_y][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;


							S->stageinfo[pre_y][pre_x - 1].mod = S->stageinfo[pre_y][pre_x].mod;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 1][pre_x].n3 == 10) //캐릭터가 이동 시에 충돌 하는데 채워진 파란 블록 또는 빨간 블록을 만났을 시
				{

					if (pre_x > cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 작음 = 오른쪽으로 이동중
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x + 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//오른쪽 이동 시 채워진 파란 블록or 빨간블록을 오른쪽으로
							S->stageinfo[pre_y - 1][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 1][pre_x + 1].mod = S->stageinfo[pre_y - 1][pre_x].mod;
							did_move += 1;

						}
					}

					if (pre_x < cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 큼 = 왼쪽으로 이동중
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x - 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//왼쪽 이동 시 채워진 파란 블록or 빨간블록을 왼쪽으로
							S->stageinfo[pre_y - 1][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 1][pre_x - 1].mod = S->stageinfo[pre_y - 1][pre_x].mod;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 2][pre_x].n3 == 10) //캐릭터가 이동 시에 충돌 하는데 채워진 파란 블록 또는 빨간 블록을 만났을 시
				{

					if (pre_x > cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 작음 = 오른쪽으로 이동중
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x + 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//오른쪽 이동 시 채워진 파란 블록or 빨간블록을 오른쪽으로
							S->stageinfo[pre_y - 2][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 2][pre_x].n2 = 0;
							S->stageinfo[pre_y - 2][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 2][pre_x + 1].mod = S->stageinfo[pre_y - 2][pre_x].mod;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //현재 x좌표가 다음으로 이동할 x좌표보다 큼 = 왼쪽으로 이동중
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x - 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//왼쪽 이동 시 채워진 파란 블록or 빨간블록을 왼쪽으로
							S->stageinfo[pre_y - 2][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y - 2][pre_x].n2 = 0;
							S->stageinfo[pre_y - 2][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 2][pre_x - 1].mod = S->stageinfo[pre_y - 2][pre_x].mod;
							did_move += 1;
						}
					}
				}


				drawStage(*S, 0, 10);
				if (did_move > 0)
					to_push(S, pre_x, pre_y + 10);
			}
		}


	}


	//if (control_gravity == 2)
	//{
	// if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x + 1, pre_y) == 0 && isCollision(S, pre_x + 2, pre_y) == 0) { // 충돌판정이 없으면
	// clear_character(S, cur_x, cur_y); //현 캐릭터 삭제
	// set_character(S, pre_x, pre_y); // 캐릭터를 해당 좌표로 이동
	// }
	//}
	//스테이지 구상에서 필요 시 추가 작성
}

void move_character(Stage* S, int pre_x, int pre_y) {

	if (ispush == 1 || Mispush == 1)
	{
		to_push(S, pre_x, pre_y);
	}

	else if (control_gravity == 1)
	{
		if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x, pre_y - 1) == 0 && isCollision(S, pre_x, pre_y - 2) == 0) { // 충돌판정이 없으면
			clear_character(S, cur_x, cur_y); //현 캐릭터 삭제
			set_character(S, pre_x, pre_y); // 캐릭터를 해당 좌표로 이동
		}
	}

	else if (control_gravity == 2)
	{
		if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x + 1, pre_y) == 0 && isCollision(S, pre_x + 2, pre_y) == 0) { // 충돌판정이 없으면
			clear_character(S, cur_x, cur_y); //현 캐릭터 삭제
			set_character(S, pre_x, pre_y); // 캐릭터를 해당 좌표로 이동
		}
	}
}

void move_block(Stage* S, int pre_x, int pre_y) {
	if (isCollision(S, pre_x, pre_y) == 0) { // 충돌판정이 없으면
		//set_block(S, pre_x, pre_y);
	}
}

int isair(Stage* S) { // 캐릭터의 바로 아래가 충돌판정을 가지는지 확인

	if (control_gravity == 1)
	{
		if (isCollision(S, cur_x, cur_y + 1) == 1) { // 충돌판정이 있으면(캐릭터가 체공 중이 아니면)
			return 0; // 0 반환
		}
		return 1; // 체공 중이면 1 반환
	}

	if (control_gravity == 2)
	{
		if (isCollision(S, cur_x - 1, cur_y) == 1) { // 충돌판정이 있으면(캐릭터가 체공 중이 아니면)
			return 0; // 0 반환
		}
		return 1; // 체공 중이면 1 반환
	}
}


int isairforblock(Stage* S, int x, int y) { // x,y의 바로 아래가 충돌판정을 가지는지 확인
	if (isCollisionforblock(S, x, y + 1) == 1) { // 충돌판정이 있으면(바닥이 비지 않았으면)
		return 0; // 0 반환
	}
	return 1; // 체공 중이면 1 반환
}

void gravity(Stage* S) {

	if (control_gravity == 1)
	{
		if (jump_height == 0) { // 점프 중이 아니면서 체공 중이면
			if (isair(S) == 1)
				move_character(S, cur_x, cur_y + 1); // 캐릭터를 1칸 내림
			else {
				jump_and_falling = 0; //점프 높이 초기화
			}
		}
		if (S->stageinfo[cur_y - 9][cur_x].n3 == 14 || S->stageinfo[cur_y - 9][cur_x].n3 == 15 || S->stageinfo[cur_y - 9][cur_x].n3 == 16) //밑에가 가시라면
			clear--;
	}

	if (control_gravity == 2)
	{
		if (jump_height == 0) { // 점프 중이 아니면서 체공 중이면
			if (isair(S) == 1)
				move_character(S, cur_x - 1, cur_y); // 캐릭터를 1칸 내림
			else {
				jump_and_falling = 0; //점프 높이 초기화
				if (S->stageinfo[cur_y - 10][cur_x - 1].n3 == 14 || S->stageinfo[cur_y - 10][cur_x - 1].n3 == 15 || S->stageinfo[cur_y - 10][cur_x - 1].n3 == 16) //밑에가 가시라면
					clear--;
			}
		}
	}
}


void gravityPlatform(Stage* S, int n) { // 코드 'n'에 해당하는 블럭은 낙하
	if (isgravity == 1) { // isgravity가 1이여서 블럭에 중력이 작용할 경우에 작동

		for (int i = 58; i > 1; i--) { // y축 역순으로 찾기
			for (int j = 1; j < 39; j++) {
				if (isairforblock(S, j, i) == 1 && S->stageinfo[i][j].n3 == 8) { // 공중이라면 한칸 내리기, 코드 n을 대상으로
					S->stageinfo[i][j].n2 = 0; // 원래 블럭이 있던 위치는 0으로
					S->stageinfo[i + 1][j].n2 = n; // 그 바로 아래는 n으로
				}
			}
		}
	}
}

void seachmoving(Stage* S, int x, int y) { //움직이는 블럭 찾는 함수
	int t = 0, J; //덩어리 길이 확인용 변수
	M = 0; //블럭갯수 초기화
	for (int i = 0; i < S->y; i++)
		for (int j = 0; j < S->x; j++)
		{
			if (S->stageinfo[i][j].n2 == 13 && t == 0) { //움직이는 블럭 덩어리의 가장 왼쪽
				J = j;
				m[0][M] = j; //x좌표
				m[1][M] = i; //y좌표
				m[2][M] = 0; //초기 방향 오른쪽
				t = 1;
			}
			if (S->stageinfo[i][j].n2 != 13 && t == 1) { //블럭 덩어리 가장 오른쪽 한칸 옆
				m[3][M] = j - J; //길이
				t = 0;
				M++; //움직이는 블럭 갯수 증가
			}
		}
}

void movingblock(Stage* S) { // 움직이는 블럭
	int cm = 0; //캐릭터가 무빙블럭 위에 있는지 확인하는 변수
	for (int i = 0; i < M; i++) {
		if (m[2][i] == 0) { //오른쪽
			if (control_gravity == 1) {
				if (S->stageinfo[cur_y - 9][cur_x].n3 == 13 && isCollision(S, cur_x + 1, cur_y) == 0 && isCollision(S, cur_x + 1, cur_y - 1) == 0 && isCollision(S, cur_x + 1, cur_y - 2) == 0) { //옆에 충돌 판정이 있을때
					cm = 1;
				}
			}
			else if (control_gravity == 2) {
				if (S->stageinfo[cur_y - 10][cur_x - 1].n3 == 13) {
					cm = 1;
				}
			}
			S->stageinfo[m[1][i]][m[0][i]].n2 = 0;
			S->stageinfo[m[1][i]][m[0][i]].isSolid = 0;
			setCursorPosition(2 * m[0][i], m[1][i] + 10);
			printf("  ");
			S->stageinfo[m[1][i]][m[0][i] + m[3][i]].n2 = 13;
			S->stageinfo[m[1][i]][m[0][i] + m[3][i]].isSolid = 1;
			setCursorPosition(2 * (m[0][i] + m[3][i]), m[1][i] + 10);
			textcolor(10);
			printf("◆");
			textcolor(15);
			m[0][i]++;
			if (S->stageinfo[m[1][i]][m[0][i] + m[3][i] + 1].n2 > 0) //오른쪽이 통과하는 블럭이 아닐경우 방향전환
				m[2][i] = 1;
		}
		else { //왼쪽
			if (control_gravity == 1) {
				if (S->stageinfo[cur_y - 9][cur_x].n3 == 13 && isCollision(S, cur_x - 1, cur_y) == 0 && isCollision(S, cur_x - 1, cur_y - 1) == 0 && isCollision(S, cur_x - 1, cur_y - 2) == 0) { //옆에 충돌 판정이 있을때
					cm = -1;
				}
			}
			else if (control_gravity == 2) {
				if (S->stageinfo[cur_y - 10][cur_x - 1].n3 == 13) {
					cm = -1;
				}
			}
			S->stageinfo[m[1][i]][m[0][i] + m[3][i] - 1].n2 = 0;
			S->stageinfo[m[1][i]][m[0][i] + m[3][i] - 1].isSolid = 0;
			setCursorPosition(2 * (m[0][i] + m[3][i] - 1), m[1][i] + 10);
			printf("  ");
			S->stageinfo[m[1][i]][m[0][i] - 1].n2 = 13;
			S->stageinfo[m[1][i]][m[0][i] - 1].isSolid = 1;
			setCursorPosition(2 * (m[0][i] - 1), m[1][i] + 10);
			textcolor(10);
			printf("◆");
			textcolor(15);
			m[0][i]--;
			if (S->stageinfo[m[1][i]][m[0][i] - 2].n2 > 0) //왼쪽이 통과하는 블럭이 아닐경우 방향전환
				m[2][i] = 0;
		}
	}
	if (cm == 1) { //오른쪽으로 움직이고 있을때 무빙블럭 위에 있다면
		clear_character(S, cur_x, cur_y);
		cur_x++;
		cm = 0;
	}
	else if (cm == -1) { //왼쪽으로 움직이고 있을때 무빙블럭 위에 있다면
		clear_character(S, cur_x, cur_y);
		cur_x--;
		cm = 0;
	}
}

//////////////////////////////fall 구현




void to_fall(Stage* S)
{
	if (isfalling == 1 && control_gravity == 1) //중력이 아래로 맨 아래에서 위쪽으로 검사
	{
		for (int i = 59; i >= 0; i--)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j, i + 1) == 0) // 아래가 충돌이 아닌 경우
					{
						//가시가 움직여 별과 만날 경우 별파괴(중력 왼쪽일때와 float는 일단 안해둠)
						/*if((S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15) && S->stageinfo[i + 1][j].n3 == -1){
							S->stageinfo[i + 1][j].n2 = 0;
							S->stageinfo[i + 1][j].n3 = 0;
							S->stageinfo[i + 1][j].n4 = 0;
							clear++;
						}
						*/
						//if (j == cur_x && i + 1 == cur_y) //캐릭터가 깔리면 죽은걸로 하고 리셋하면 될 것같습니다
						// return;
						// 한칸 아래가 issolid는 0이지만 배열이 0(빈공간)이 아닌것, 즉 통과되는 블럭이라는 뜻이고 n4가 0, 즉 통과되고 있는중이 아닌 것 이므로 통과가 시작되는 지점인 경우라는 뜻입니다
						if (S->stageinfo[i + 1][j].n2 != 0 && S->stageinfo[i + 1][j].n4 == 0)

							S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 11) // 각 코드에 대해서
							S->stageinfo[i + 1][j].n2 = 11; // 한칸 아래의 n2를 변경

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i + 1][j].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i + 1][j].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i + 1][j].n2 = 15;

						S->stageinfo[i + 1][j].isSolid = 1; //블럭이 떨어지는 경우이므로 블럭으로 바뀐 한칸아래는 충돌판정을 넣어줍니다 따라서 통과 가능한 별에는 이 코드가 없습니다

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i - 1][j].isSolid == 0) { //통과중인 블럭이자 한칸 위의 isSolid가 0, 즉 통과가 끝나는 지점일 경우 라는 의미입니다
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (isfalling == 1 && control_gravity == 2) //중력이 위로 왼쪽 끝부터 오른쪽 끝으로 검사
	{
		for (int j = 0; j < 40; j++)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j - 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //캐릭터가 깔리면 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i][j - 1].n2 != 0 && S->stageinfo[i][j - 1].n4 == 0)

							S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 11) // 각 코드에 대해서
							S->stageinfo[i][j - 1].n2 = 11; // 한칸 아래의 n2를 변경

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i][j - 1].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i][j - 1].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i][j - 1].n2 = 15;

						S->stageinfo[i][j - 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j + 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

	if (isStarfalling == 1 && control_gravity == 1) //중력이 아래로 맨 아래에서 위쪽으로 검사
	{
		for (int i = 59; i >= 0; i--)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j, i + 1) == 0) // 아래가 충돌이 아닌 경우
					{
						//if (j == cur_x && i + 1 == cur_y) //캐릭터가 깔리면 죽은걸로 하고 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i + 1][j].n2 != 0 && S->stageinfo[i + 1][j].n4 == 0)

							S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; //일단 아래의 n4에 n2를 임시저장함


						S->stageinfo[i + 1][j].n2 = -1; // 한칸 아래의 n2를 변경

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i - 1][j].isSolid == 0) { // 원래 있던칸의 n4가 0이 아니고 원래 있던칸의 한칸 위의 n2가 0이면???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
					//움직일때 가시 닿으면 별 파괴(왼쪽 중력과 float일때는 일단 안해둠)
					/* else if(S->stageinfo[i + 1][j] == 14 || S->stageinfo[i + 1][j] == 15){
					* S->stageinfo[i][j].n2 = 0;
					* clear++;
					}
					*/
				}
			}
		}
		drawStage(*S, 0, 10);
	}


	if (isStarfalling == 1 && control_gravity == 2) //중력이 위로, 왼쪽 끝부터 오른쪽 끝으로 검사
	{
		for (int j = 0; j < 40; j++)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j - 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //캐릭터가 깔리면 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i][j - 1].n2 != 0 && S->stageinfo[i][j - 1].n4 == 0) // 아래의 n2가 0이 아니고 n4도 0이 아닐 경우?

							S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; //일단 아래의 n4에 n2를 임시저장함


						S->stageinfo[i][j - 1].n2 = -1; // 한칸 아래의 n2를 변경

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j + 1].isSolid == 0) { // 원래 있던칸의 n4가 0이 아니고 원래 있던칸의 한칸 위의 n2가 0이면???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

	if (Misfalling == 1 && control_gravity == 1) //중력이 아래로 맨 아래에서 위쪽으로 검사
	{
		for (int i = 59; i >= 0; i--)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j, i + 1) == 0) // 아래가 충돌이 아닌 경우
					{
						if (S->stageinfo[i + 1][j].n2 != 0 && S->stageinfo[i + 1][j].n4 == 0)

							S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 10) // 각 코드에 대해서
							S->stageinfo[i + 1][j].n2 = 10; // 한칸 아래의 n2를 변경
						S->stageinfo[i + 1][j].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i + 1][j].isSolid = 1; //블럭이 떨어지는 경우이므로 블럭으로 바뀐 한칸아래는 충돌판정을 넣어줍니다 따라서 통과 가능한 별에는 이 코드가 없습니다

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i - 1][j].isSolid == 0) { //통과중인 블럭이자 한칸 위의 isSolid가 0, 즉 통과가 끝나는 지점일 경우 라는 의미입니다
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (Misfalling == 1 && control_gravity == 2) //중력이 위로 왼쪽 끝부터 오른쪽 끝으로 검사
	{
		for (int j = 0; j < 40; j++)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j - 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //캐릭터가 깔리면 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i][j - 1].n2 != 0 && S->stageinfo[i][j - 1].n4 == 0)

							S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 10) // 각 코드에 대해서
							S->stageinfo[i][j - 1].n2 = 10; // 한칸 아래의 n2를 변경
						S->stageinfo[i][j - 1].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i][j - 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j + 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

}

void to_float(Stage* S)
{
	if (isfalling == -1 && control_gravity == 1) //중력이 아래로 맨 아래에서 위쪽으로 검사
	{
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j, i - 1) == 0) // 아래가 충돌이 아닌 경우
					{
						//if (j == cur_x && i + 1 == cur_y) //캐릭터가 깔리면 죽은걸로 하고 리셋하면 될 것같습니다
						// return;
						// 한칸 아래가 issolid는 0이지만 배열이 0(빈공간)이 아닌것, 즉 통과되는 블럭이라는 뜻이고 n4가 0, 즉 통과되고 있는중이 아닌 것 이므로 통과가 시작되는 지점인 경우라는 뜻입니다
						if (S->stageinfo[i - 1][j].n2 != 0 && S->stageinfo[i - 1][j].n4 == 0)

							S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 11) // 각 코드에 대해서
							S->stageinfo[i - 1][j].n2 = 11; // 한칸 아래의 n2를 변경

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i - 1][j].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i - 1][j].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i - 1][j].n2 = 15;

						S->stageinfo[i - 1][j].isSolid = 1; //블럭이 떨어지는 경우이므로 블럭으로 바뀐 한칸아래는 충돌판정을 넣어줍니다 따라서 통과 가능한 별에는 이 코드가 없습니다

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i + 1][j].isSolid == 0) { //통과중인 블럭이자 한칸 위의 isSolid가 0, 즉 통과가 끝나는 지점일 경우 라는 의미입니다
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}

						if (isCharacterThere(j, i - 1) == 1) { // 캐릭터가 위에있으면
							move_character(S, j, i + 8);
							if (S->stageinfo[i-2][j].isSolid == 1) {
								isdeath = 1;
							}
						}

					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (isfalling == -1 && control_gravity == 2) //중력이 위로 왼쪽 끝부터 오른쪽 끝으로 검사
	{
		for (int j = 39; j >= 0; j--)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j + 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //캐릭터가 깔리면 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i][j + 1].n2 != 0 && S->stageinfo[i][j + 1].n4 == 0)

							S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 11) // 각 코드에 대해서
							S->stageinfo[i][j + 1].n2 = 11; // 한칸 아래의 n2를 변경

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i][j + 1].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i][j + 1].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i][j + 1].n2 = 15;

						S->stageinfo[i][j + 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j - 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

	if (isStarfalling == -1 && control_gravity == 1) //중력이 아래로 맨 아래에서 위쪽으로 검사
	{
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j, i - 1) == 0) // 아래가 충돌이 아닌 경우
					{
						//if (j == cur_x && i + 1 == cur_y) //캐릭터가 깔리면 죽은걸로 하고 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i - 1][j].n2 != 0 && S->stageinfo[i - 1][j].n4 == 0)

							S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; //일단 아래의 n4에 n2를 임시저장함


						S->stageinfo[i - 1][j].n2 = -1; // 한칸 아래의 n2를 변경

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i + 1][j].isSolid == 0) { // 원래 있던칸의 n4가 0이 아니고 원래 있던칸의 한칸 위의 n2가 0이면???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}


	if (isStarfalling == -1 && control_gravity == 2) //중력이 위로, 왼쪽 끝부터 오른쪽 끝으로 검사
	{
		for (int j = 39; j >= 0; j--)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j + 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //캐릭터가 깔리면 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i][j + 1].n2 != 0 && S->stageinfo[i][j + 1].n4 == 0) // 아래의 n2가 0이 아니고 n4도 0이 아닐 경우?

							S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; //일단 아래의 n4에 n2를 임시저장함


						S->stageinfo[i][j + 1].n2 = -1; // 한칸 아래의 n2를 변경

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j - 1].isSolid == 0) { // 원래 있던칸의 n4가 0이 아니고 원래 있던칸의 한칸 위의 n2가 0이면???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}
	//Machine의 경우
	if (Misfalling == -1 && control_gravity == 1) //중력이 아래로 맨 아래에서 위쪽으로 검사
	{
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j, i - 1) == 0) // 아래가 충돌이 아닌 경우
					{
						//if (j == cur_x && i + 1 == cur_y) //캐릭터가 깔리면 죽은걸로 하고 리셋하면 될 것같습니다
						// return;
						// 한칸 아래가 issolid는 0이지만 배열이 0(빈공간)이 아닌것, 즉 통과되는 블럭이라는 뜻이고 n4가 0, 즉 통과되고 있는중이 아닌 것 이므로 통과가 시작되는 지점인 경우라는 뜻입니다
						if (S->stageinfo[i - 1][j].n2 != 0 && S->stageinfo[i - 1][j].n4 == 0)

							S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 10) // 각 코드에 대해서
							S->stageinfo[i - 1][j].n2 = 10; // 한칸 아래의 n2를 변경
						S->stageinfo[i - 1][j].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i - 1][j].isSolid = 1; //블럭이 떨어지는 경우이므로 블럭으로 바뀐 한칸아래는 충돌판정을 넣어줍니다 따라서 통과 가능한 별에는 이 코드가 없습니다

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i + 1][j].isSolid == 0) { //통과중인 블럭이자 한칸 위의 isSolid가 0, 즉 통과가 끝나는 지점일 경우 라는 의미입니다
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}

						if (isCharacterThere(j, i - 1) == 1) { // 캐릭터가 위에있으면
							move_character(S, j, i + 8);
						}

					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (Misfalling == -1 && control_gravity == 2) //중력이 위로 왼쪽 끝부터 오른쪽 끝으로 검사
	{
		for (int j = 39; j >= 0; j--)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j + 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //캐릭터가 깔리면 리셋하면 될 것같습니다
						// return;
						if (S->stageinfo[i][j + 1].n2 != 0 && S->stageinfo[i][j + 1].n4 == 0)

							S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; //일단 아래의 n4에 n2를 임시저장함


						if (S->stageinfo[i][j].n3 == 10) // 각 코드에 대해서
							S->stageinfo[i][j + 1].n2 = 10; // 한칸 아래의 n2를 변경
						S->stageinfo[i][j + 1].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i][j + 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // 원래 있던칸의 n2는 빈칸으로

						S->stageinfo[i][j].isSolid = 0; // 원래 있던칸은 충돌판정 없애줌

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j - 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 원래 있던칸의 n2는 n4를 통해 다시 불러옴
							S->stageinfo[i][j].n4 = 0; // n4는 0으로
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

}



//------------------------------- PUSH



// --------------------------- 발사체 함정 구현



void printshootrate() {
	setCursorPosition(88, 50);
	if (shootrate >= 200) {
		setCursorPosition(88, 50);
		// printf("Shootrate :    ");
		shootrate = 0;
	}
	//printf("Shootrate : %d", shootrate);
}


void projectileUpdate(inter* M, Stage* S) { // 투사체 이동시키기
	for (int i = 0; i < 60; i++) {
		for (int j = 39; j > 0; j--) {
			if (S->stageinfo[i][j].n2 == -301) { // 오른쪽 투사체일 경우
				if (S->stageinfo[i][j + 1].isSolid != 1) { // 충돌판정이 없다면

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 지나간 칸을 원래대로 되돌리고
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; // n2를 임시저장
					S->stageinfo[i][j + 1].n2 = -301; // 오른쪽 칸은 투사체로
					if (isCharacterThere(j + 1, i) == 1) { // 만약 이동했을 시 플레이어가 거기에 있으면)
						clear--;
					}
					if (S->stageinfo[i][j + 1].n4 == -1) { // 만약 이동했을 시 별이 거기에 있으면)
						S->stageinfo[i][j + 1].n4 = 0; // 별 없애고 별 얻은것과 같은효과
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // 충돌판정이 있으면
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 소멸
				}

			}
		}

		for (int j = 0; j < 39; j++) {

			if (S->stageinfo[i][j].n2 == -302) { // 왼쪽 투사체일 경우
				if (S->stageinfo[i][j - 1].isSolid != 1) { // 충돌판정이 없다면

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 지나간 칸을 원래대로 되돌리고
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; // n2를 임시저장
					S->stageinfo[i][j - 1].n2 = -302; // 오른쪽 칸은 투사체로
					if (isCharacterThere(j - 1, i) == 1) { // 만약 이동했을 시 플레이어가 거기에 있으면)
						clear--;
					}
					if (S->stageinfo[i][j - 1].n4 == -1) { // 만약 이동했을 시 별이 거기에 있으면)
						S->stageinfo[i][j - 1].n4 = 0; // 별 없애고 별 얻은것과 같은효과
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // 충돌판정이 있으면
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 소멸
					S->stageinfo[i][j].n4 = 0;;
				}

			}

		}

	}

	for (int j = 0; j < 40; j++) {
		for (int i = 0; i < 60; i++) {
			if (S->stageinfo[i][j].n2 == -303) { // 위쪽 투사체일 경우
				if (S->stageinfo[i - 1][j].isSolid != 1) { // 충돌판정이 없다면

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 지나간 칸을 원래대로 되돌리고
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; // n2를 임시저장
					S->stageinfo[i - 1][j].n2 = -303; // 위쪽 칸은 투사체로
					if (isCharacterThere(j, i - 1) == 1) { // 만약 이동했을 시 플레이어가 거기에 있으면)
						clear--;
					}
					if (S->stageinfo[i - 1][j].n4 == -1) { // 만약 이동했을 시 별이 거기에 있으면)
						S->stageinfo[i - 1][j].n4 = 0; // 별 없애고 별 얻은것과 같은효과
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // 충돌판정이 있으면
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 소멸
					S->stageinfo[i][j].n4 = 0;
				}

			}
		}

		for (int i = 59; i > 0; i--) {

			if (S->stageinfo[i][j].n2 == -304) { // 아래쪽 투사체일 경우
				if (S->stageinfo[i + 1][j].isSolid != 1) { // 충돌판정이 없다면

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 지나간 칸을 원래대로 되돌리고
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; // n2를 임시저장
					S->stageinfo[i + 1][j].n2 = -304; // 아래쪽 칸은 투사체로
					if (isCharacterThere(j, i + 1) == 1) { // 만약 이동했을 시 플레이어가 거기에 있으면)
						clear--;
					}
					if (S->stageinfo[i + 1][j].n4 == -1) { // 만약 이동했을 시 플레이어가 거기에 있으면)
						S->stageinfo[i + 1][j].n4 = 0; // 별 없애고 별 얻은것과 같은효과
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // 충돌판정이 있으면
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // 소멸
					S->stageinfo[i][j].n4 = 0;
				}

			}

		}

	}
}


void shooting(Stage* S) { // 'stageinfo[y][x].n3 좌표에 발사체 함정이 있는 것으로 가정하고' 



	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 40; j++) {
			if (S->stageinfo[i][j].n2 == 10 || S->stageinfo[i][j].n2 == 17) { // 함정이면

				if (S->stageinfo[i][j].mod == 1 && S->stageinfo[i][j + 1].isSolid == 0) { // 오른쪽으로 통과 가능할때
					S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; // n2를 임시저장
					S->stageinfo[i][j + 1].n2 = -301; // 오른쪽에 투사체 생성
				}
				if (S->stageinfo[i][j].mod == 2 && S->stageinfo[i][j - 1].isSolid == 0) { // 왼쪽으로 통과 가능할때
					S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; // n2를 임시저장
					S->stageinfo[i][j - 1].n2 = -302; // 왼쪽에 투사체 생성
				}
				if (S->stageinfo[i][j].mod == 3 && S->stageinfo[i - 1][j].isSolid == 0) { // 위쪽으로 통과 가능할때
					S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; // n2를 임시저장
					S->stageinfo[i - 1][j].n2 = -303; // 위쪽에 투사체 생성
				}
				if (S->stageinfo[i][j].mod == 4 && S->stageinfo[i + 1][j].isSolid == 0) { // 아래쪽으로 통과 가능할때
					S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; // n2를 임시저장
					S->stageinfo[i + 1][j].n2 = -304; // 아래쪽에 투사체 생성
				}

			}
		}
	}
}



//---------------------------------------------------------------------- 점프
void to_jump(Stage* S) {

	if (control_gravity == 1)
	{
		if (jump_height > 0) { // 올라가야 할 높이가 남아있는 경우 ( 점프 중 )
			move_character(S, cur_x, cur_y - 1); // 캐릭터를 1칸 올려주고

			if (right == 1 && jump_height % 2 == 0) move_character(S, cur_x + 1, cur_y); // 오른쪽 점프일경우 오른쪽으로도 1칸
			if (left == 1 && jump_height % 2 == 0) move_character(S, cur_x - 1, cur_y); // 왼쪽 점프일경우 왼쪽으로도 1칸

			jump_height--; // 1칸 올라갔으니 올라가야 할 높이 1칸 감소시키기
			jump_and_falling++;

		}
		else if (jump_and_falling > 0 && isair(S)) { // 점프 최고 높이 도달 후에도 여전히 공중이라면(추락하는 상황이라면)
			// 처음 점프 방향에 맞춰서 왼쪽/오른쪽으로 이동
			if (right == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x + 1, cur_y);
			if (left == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x - 1, cur_y);
			jump_and_falling--;
		}
	}

	if (control_gravity == 2)
	{
		if (jump_height > 0) { // 올라가야 할 높이가 남아있는 경우 ( 점프 중 )
			move_character(S, cur_x + 1, cur_y); // 캐릭터를 1칸 올려주고

			if (right == 1 && jump_height % 2 == 0) move_character(S, cur_x, cur_y - 1); // 오른쪽 점프일경우 오른쪽으로도 1칸
			if (left == 1 && jump_height % 2 == 0) move_character(S, cur_x, cur_y + 1); // 왼쪽 점프일경우 왼쪽으로도 1칸

			jump_height--; // 1칸 올라갔으니 올라가야 할 높이 1칸 감소시키기
			jump_and_falling++;

		}
		else if (jump_and_falling > 0 && isair(S)) { // 점프 최고 높이 도달 후에도 여전히 공중이라면(추락하는 상황이라면)
			// 처음 점프 방향에 맞춰서 왼쪽/오른쪽으로 이동
			if (right == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x, cur_y - 1);
			if (left == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x, cur_y + 1);
			jump_and_falling--;
		}
	}

}

void print_jump_gauge()
{
	int pos_x_to_print_jump_gauge = 25; // 점프게이지 위치 수정
	int pos_y_to_print_jump_gauge = 4;
	for (int i = 0; i < 10; i += 2)//게이지를 새롭게 그리기 전 게이지 바에 있던 걸 다 지움
	{
		setCursorPosition(2 * pos_x_to_print_jump_gauge + i, pos_y_to_print_jump_gauge);
		printf("  ");
	}
	for (int i = 0; i < jump_height; i += 2)
	{
		// 색상 설정 (1~5칸에 다른 색 지정)
		int colorNum;
		if (i < 2)
			colorNum = 7; // 흰색
		else if (i < 4)
			colorNum = 14; // 옅은 노랑
		else if (i < 6)
			colorNum = 6; // 진한 노랑
		else if (i < 8)
			colorNum = 12; // 옅은 빨강
		else
			colorNum = 4; // 진한 빨강

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);

		setCursorPosition(2 * pos_x_to_print_jump_gauge + i, pos_y_to_print_jump_gauge);
		printf("■");
	}

	// 기본 색상 복원 (흰색)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void print_jump_direction() //방향을 화면에 출력
{
	if (control_gravity == 1)
	{
		if (right == 1)
		{
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("→");
		}
		if (left == 1)
		{
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("←");
		}

		if (left == 0 && right == 0)
		{
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("↑");
		}
	}

	if (control_gravity == 2)
	{
		if (right == 1)
		{
			setCursorPosition(2 * (cur_x + 2), cur_y);
			printf("↑");
		}
		if (left == 1)
		{
			setCursorPosition(2 * (cur_x + 2), cur_y);
			printf("↓");
		}

		if (left == 0 && right == 0)
		{
			setCursorPosition(2 * (cur_x + 2), cur_y);
			printf("→");
		}
	}
}

void set_jump_gauge(inter* M, Stage S)//스페이스바를 계속 누르는 동안 플레이어가 게이지와 점프 방향을 설정할 수 있게 해주는 함수
{
	int add_gauge = 2; //게이지는 총 5칸으로 이루어져 있습니다. 게이지 한 칸 당 두 칸씩 추가로 올라갑니다
	int update_print_jump_gauge_timing = 0;//방향키를 입력 받았을 때 점프 방향으로 바로바로 반영하기 위해서는 키보드 입력을 상시로 받아야합니다.
	// 하지만 화면에 출력 될 점프 게이지와 실제 점프 게이지 정보는 바로 바로 갱신하면 조작이 불가능 할 정도로 빠르게 갱신되기 때문에 시간 텀을 두고서 갱신이 필요합니다.  
	// 그러므로 방향키를 상시로 입력 받는 상황에서 게이지 갱신을 진행할 특정 타이밍을 정할 때 사용할 변수입니다.

	jump_height = 0;  // 점프 높이
	jump_and_falling = 0; // 점프에서 최고 높이까지 뛴 후 다시 떨어지는 상황에 사용할 변수

	draw_ready_to_jump_character(&S, cur_x, cur_y);
	while (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		update_print_jump_gauge_timing += 1;
		shootrate++;
		printshootrate();

		if (control_gravity == 1)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)// 오른쪽방향키를 누르면 right를 1로 갱신
			{
				right = 1; left = 0;
				print_jump_direction();//플레이어가 점프할 방향을 화면에 출력해줌(점프 게이지 밑에 출력)
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)// 왼쪽방향키 누르면 left를 1로 갱신
			{
				right = 0; left = 1;
				print_jump_direction();//플레이어가 점프할 방향을 화면에 출력해줌(점프 게이지 밑에 출력)
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000)// 위쪽 방향키일 경우 둘다 0으로
			{
				right = 0; left = 0;
				print_jump_direction();//플레이어가 점프할 방향을 화면에 출력해줌(점프 게이지 밑에 출력)
			}
		}

		if (control_gravity == 2)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)// 위쪽방향키를 누르면 right를 1로 갱신
			{
				right = 1; left = 0;
				print_jump_direction();//플레이어가 점프할 방향을 화면에 출력해줌(점프 게이지 밑에 출력)
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)// 아래방향키 누르면 left를 1로 갱신
			{
				right = 0; left = 1;
				print_jump_direction();//플레이어가 점프할 방향을 화면에 출력해줌(점프 게이지 밑에 출력)
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)// 오른쪽 방향키일 경우 둘다 0으로
			{
				right = 0; left = 0;
				print_jump_direction();//플레이어가 점프할 방향을 화면에 출력해줌(점프 게이지 밑에 출력)
			}
		}

		if (update_print_jump_gauge_timing % 13 == 0)//0.3초마다 게이지를 갱신  
		{
			if (jump_height >= 10) add_gauge = -2;//게이지가 다 찬 상황에서도 스페이스바를 누르면 다시 줄어들게 하기 위해 jump_height에 더하는 값을 -로 변경
			if (jump_height <= 0) add_gauge = 2;// 다시 게이지가 0으로 떨어지면 게이지를 올리기 위해 jump_height 더하는 값을 +로 변경
			jump_height += add_gauge;
			print_jump_gauge();//게이지 현 상황을 화면에 출력
		}

		if (update_print_jump_gauge_timing % 8 == 0) {
			to_fall(&S);
			to_float(&S);
		}
		Sleep(10);
		
		if (update_print_jump_gauge_timing % 8 == 0) {
			projectileUpdate(M, &S);
			drawStage(S, 0, 10);

		}

		if (shootrate % 200 == 0) {
			shooting(&S);
			shootrate = 0;
		}

		if (update_print_jump_gauge_timing % 40 == 0) {
			movingblock(&S);
			draw_ready_to_jump_character(&S, cur_x, cur_y); //움직인 칸에 점프중 캐릭 모션 다시 그리기
			print_jump_direction();
		}
		check_cur2(&S);
		if (isair(&S) == 1) {
			gravity(&S);
			jump_height = 0;
			jump_and_falling = 0;
			break;
		}
		time_check();
	}

	play_effect_sound("C:\\sounds\\jump_complete.wav");
}
//---------------------------------------------------------------------- 키 입력

void keybord_input(inter* M, Stage* S) {

	// ----------------------------------------------- 캐릭터 조작(방향키, 스페이스바)

	// 스페이스바가 눌렸는지 확인
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (isair(S) != 1) {
			set_jump_gauge(M, *S); // 점프 높이 설정
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && isair(S) != 1) {

		move_character(S, cur_x - 1, cur_y); // 왼쪽으로 이동
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && isair(S) != 1) {

		move_character(S, cur_x + 1, cur_y); // 오른쪽으로 이동
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		move_character(S, cur_x, cur_y - 1); // 위쪽으로 이동
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		move_character(S, cur_x, cur_y + 1); // 아래쪽으로 이동
	}


	// ----------------------------------------------- 인터페이스 조작

	// 방향키 입력 확인 (키워드 인터페이스 조작)


	if (GetAsyncKeyState(0x57) & 0x8000) // W, 위로 이동
	{
		findTextlineSelection(*S, TextMatrix, &x1, &y1);

		if (y1 > 0) { // 음수가 되기 전까지는 y좌표 감소
			y1--;
			TextMatrix[y1 + 1][x1] = 0; // 원래 좌표는 0으로
			TextMatrix[y1][x1] = 1; // 새 좌표는 1로
		}
		indicateTextline(*S, TextMatrix);
		Sleep(40);

	}
	if (GetAsyncKeyState(0x53) & 0x8000) // S, 아래로 이동
	{
		findTextlineSelection(*S, TextMatrix, &x1, &y1);


		if (y1 < S->NumofLines - 1) { // 개수 초과 전까지는 y좌표 증가
			y1++;
			TextMatrix[y1 - 1][x1] = 0; // 원래 좌표는 0으로
			TextMatrix[y1][x1] = 1; // 새 좌표는 1로
		}
		indicateTextline(*S, TextMatrix);
		Sleep(40);
	}

	if (GetAsyncKeyState(0x52) & 0x8000) // R, 스테이지 재시작
	{
		getinfo(S, stageinfos[c_stage], 40, 60);
		S->NumofLines = 2;
		if (c_stage == 2) {
			S->NumofLines = 3;
			S->stageinfo[4][4].mod = 1;
			S->stageinfo[55][38].mod = 3;
			S->stageinfo[58][2].mod = 3;
		}
		S->Textlines[0].element = text_arr[c_stage][0][0];
		S->Textlines[0].keyword = text_arr[c_stage][0][1];
		S->Textlines[1].element = text_arr[c_stage][1][0];
		S->Textlines[1].keyword = text_arr[c_stage][1][1];
		S->Textlines[2].element = text_arr[c_stage][2][0];
		S->Textlines[2].keyword = text_arr[c_stage][2][1];


		clear = 0;
		c_bonus = 0;
		right = 0;
		left = 0;
		jump_height = 0;
		jump_and_falling = 0;
		isfalling = 0;
		ispush = 0;
		Mispush = 0;
		Misfalling = 0;
		isStarfalling = 0;
		clear_character(S, cur_x, cur_y);
		control_gravity = 1;
		set_character(S, start_arr[c_stage][0], start_arr[c_stage][1]); // 캐릭터 위치 설정


		if (c_stage == 2) { // 3스테이지 전용


			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("  ");
			setCursorPosition(2 * cur_x, cur_y - 1);
			printf("  ");
			setCursorPosition(2 * cur_x, cur_y);
			printf("  ");

			setCursorPosition(2 * cur2_x, cur2_y - 2);
			printf("  ");
			setCursorPosition(2 * cur2_x, cur2_y - 1);
			printf("  ");
			setCursorPosition(2 * cur2_x, cur2_y);
			printf("  ");


			dual = 1;
			cur_x = 1, cur_y = 68;
			cur2_x = 30, cur2_y = 68; //캐릭터2의 '발'의 좌표
			textcolor(12); // 빨간색
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("○");
			setCursorPosition(2 * cur_x, cur_y - 1);
			printf("▣");
			setCursorPosition(2 * cur_x, cur_y);
			printf("∥");
			textcolor(15); // 다시 하얀색으로

			textcolor(9); // 파란색
			setCursorPosition(2 * cur2_x, cur2_y - 2);
			printf("○");
			setCursorPosition(2 * cur2_x, cur2_y - 1);
			printf("□");
			setCursorPosition(2 * cur2_x, cur2_y);
			printf("∥");
			textcolor(15);
		}

		for (int i = 0; i < 8; i++) {
			currentKeywords[i] = keywords[0][i];
		}

		drawStage(*S, 0, 10);
		indicateTextline(*S, TextMatrix);
		seachmoving(S, 0, 10);
		indicateItems();

		keyWordindicator();
	}

	if (GetAsyncKeyState(0x31) & 0x8000) // 1번 키워드로 교체 - STOP
	{

		if (currentKeywords[0] != 0) { // 키워드가 비어있으면 작동하지 않음

			play_effect_sound("C:\\sounds\\keyword_change.wav");

			if (S->Textlines[y1].element == 8) { // Platform이면

				for (int i = 0; i < 60; i++) { // PASS 해제
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 11) { // 파란색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // 빨간색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}

				isfalling = 0; // FALL 해제
				ispush = 0; // push 해제
			}
			if (S->Textlines[y1].element == -1) { // Star면
				isStarfalling = 0; // FALL 해제
			}

			// MACHINE용
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = 0;
			}

			S->Textlines[y1].keyword = currentKeywords[0]; // 현재 스테이지의 키워드 교체
			Sleep(40);
		}


		indicateTextline(*S, TextMatrix);

	}
	if (GetAsyncKeyState(0x32) & 0x8000) // 2번 키워드로 교체 - PASS
	{

		if (currentKeywords[1] != 0) {

			play_effect_sound("C:\\sounds\\keyword_change.wav");
			if (S->Textlines[y1].element == 8) { // Platform이면
				isfalling = 0; // FALL 해제
				ispush = 0; // PUSH 해제
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {
						// isSolid를 0으로 만들어 충돌 없앰
						if (S->stageinfo[i][j].n3 == 11) { // 파란색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // 빨간색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 0;
						}
					}
				}
			}
			if (S->Textlines[y1].element == -1) { // Star면
				isStarfalling = 0; // FALL 해제
			}

			// MACHINE용
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = 0;
			}

			S->Textlines[y1].keyword = currentKeywords[1];
			Sleep(40);
		}
		indicateTextline(*S, TextMatrix);
	}
	if (GetAsyncKeyState(0x33) & 0x8000) // 3번 키워드(FALL)로 교체
	{

		// 블럭용

		if (currentKeywords[2] != 0) {

			play_effect_sound("C:\\sounds\\keyword_change.wav");

			// 블럭용
			if (S->Textlines[y1].element == 8) { // Platform이면

				ispush = 0; // PUSH 해제
				isfalling = 1;
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {
						// isSolid를 0으로 만들어 충돌 없앰
						if (S->stageinfo[i][j].n3 == 11) {
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) {
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}
			}

			// STAR용
			if (S->Textlines[y1].element == -1) { // Star이면
				isStarfalling = 1; //FALL
			}

			// MACHINE용
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = 1;
			}


			S->Textlines[y1].keyword = currentKeywords[2];
			Sleep(40);
		}

		indicateTextline(*S, TextMatrix);

	}
	if (GetAsyncKeyState(0x34) & 0x8000) // 4번 키워드(SWITCH)로 교체
	{
		if (currentKeywords[3] != 0) {

			play_effect_sound("C:\\sounds\\keyword_change.wav");

			// 블럭용

			if (S->Textlines[y1].element == 8) { // Platform이면
				isfalling = 0; // FALL 해제
				ispush = 0; // PUSH 해제
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 11) { // 파란색 블록을 빈 블록으로
							S->stageinfo[i][j].n2 = -11;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -11) { // 파란색 빈 블록을....
							S->stageinfo[i][j].n2 = 11;
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // 빨간색 블록을 빈 블록으로
							S->stageinfo[i][j].n2 = -12;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -12) { // 빨간색 빈 블록을....
							S->stageinfo[i][j].n2 = 12;
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}
			}

			// 함정용

			if (S->Textlines[y1].element == 8) { // 함정(가시)일 경우
				isfalling = 0; // FALL 해제
				ispush = 0; // PUSH 해제
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 14) { // 파란색 가시를 파란색 빈 가시로
							S->stageinfo[i][j].n2 = -14;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -14) { // 파란색 빈 가시를....
							S->stageinfo[i][j].n2 = 14;
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 15) { // 빨간색 가시를 빨간색 빈 가시로
							S->stageinfo[i][j].n2 = -15;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -15) { // 빨간색 빈 가시를....
							S->stageinfo[i][j].n2 = 15;
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}
			}

			// STAR

			if (S->Textlines[y1].element == -1) { // STAR이면
				isStarfalling = 0; // FALL 해제
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == -1) { // ★ -> ☆
							S->stageinfo[i][j].n2 = -2;
						}
						else if (S->stageinfo[i][j].n3 == -2) { // ☆ -> ★
							S->stageinfo[i][j].n2 = -1;
						}
					}
				}
			}

			//CHARACTER

			if (S->Textlines[y1].element == 7) { // 캐릭터인 경우

				jump_height = 0;
				left = 0;
				right = 0;
				int t = cur_x;
				cur_x = cur2_x;
				cur2_x = t;
				t = cur_y;
				cur_y = cur2_y;
				cur2_y = t;

				if (dual == 1) {
					textcolor(9); // 파란색
					setCursorPosition(2 * cur_x, cur_y - 2);
					printf("○");
					setCursorPosition(2 * cur_x, cur_y - 1);
					printf("▣");
					setCursorPosition(2 * cur_x, cur_y);
					printf("∥");
					textcolor(15); // 다시 하얀색으로

					textcolor(12); // 빨간색
					setCursorPosition(2 * cur2_x, cur2_y - 2);
					printf("○");
					setCursorPosition(2 * cur2_x, cur2_y - 1);
					printf("□");
					setCursorPosition(2 * cur2_x, cur2_y);
					printf("∥");
					textcolor(15); // 다시 하얀색으로

					dual = 2;
				}
				else {
					textcolor(12); // 빨간색
					setCursorPosition(2 * cur_x, cur_y - 2);
					printf("○");
					setCursorPosition(2 * cur_x, cur_y - 1);
					printf("▣");
					setCursorPosition(2 * cur_x, cur_y);
					printf("∥");
					textcolor(15); // 다시 하얀색으로

					textcolor(9); // 파란색
					setCursorPosition(2 * cur2_x, cur2_y - 2);
					printf("○");
					setCursorPosition(2 * cur2_x, cur2_y - 1);
					printf("□");
					setCursorPosition(2 * cur2_x, cur2_y);
					printf("∥");
					textcolor(15); // 다시 하얀색으로

					dual = 1;
				}
			}

			//MACHINE

			if (S->Textlines[y1].element == 10) { // machine이면
				Misfalling = 0;
				Mispush = 0;
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 10) { // 머신이 있으면
							if (S->stageinfo[i][j].mod == 1) { // 오른쪽
								S->stageinfo[i][j].mod = 4;
							}
							else if (S->stageinfo[i][j].mod == 2) { // 왼쪽
								S->stageinfo[i][j].mod = 3;
							}
							else if (S->stageinfo[i][j].mod == 3) { // 위쪽
								S->stageinfo[i][j].mod = 1;
							}
							else if (S->stageinfo[i][j].mod == 4) { // 아래쪽
								S->stageinfo[i][j].mod = 2;
							}

						}
					}
				}
			}

			drawStage(*S, 0, 10);

			S->Textlines[y1].keyword = currentKeywords[3]; // SWITCH로 변경
			indicateTextline(*S, TextMatrix);


			Sleep(40);
		}
	}
	if (GetAsyncKeyState(0x35) & 0x8000) // 5번 키워드(FLOAT)로 교체
	{

		// 블럭용

		if (currentKeywords[4] != 0) {
			play_effect_sound("C:\\sounds\\keyword_change.wav");
			// 블럭용
			if (S->Textlines[y1].element == 8) { // Platform이면
				isfalling = -1;
				ispush = 0;
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {
						// isSolid를 0으로 만들어 충돌 없앰
						if (S->stageinfo[i][j].n3 == 11) { // 파란색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // 빨간색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 0;
						}
					}
				}
			}

			// STAR용
			if (S->Textlines[y1].element == -1) { // Star이면
				isStarfalling = -1; //FALL
			}

			// MACHINE용
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = -1;
			}


			S->Textlines[y1].keyword = currentKeywords[4];
			Sleep(40);
		}

		indicateTextline(*S, TextMatrix);

	}
	if (GetAsyncKeyState(0x36) & 0x8000) // 6번 키워드(PUSH)로 교체
	{



		if (currentKeywords[5] != 0) {
			play_effect_sound("C:\\sounds\\keyword_change.wav");
			// 블럭용
			if (S->Textlines[y1].element == 8) { // Platform이면
				for (int i = 0; i < 60; i++) { // PASS 해제
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 11) { // 파란색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // 빨간색 블록을 빈 블록으로
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}

				ispush = 1;

				isfalling = 0; // FALL 해제
			}

			// STAR용
			if (S->Textlines[y1].element == -1) { // Star이면
				isStarfalling = 0;
			}

			// MACHINE용
			if (S->Textlines[y1].element == 10) {
				Misfalling = 0;
				Mispush = 1;
			}




			S->Textlines[y1].keyword = currentKeywords[5];
			Sleep(40);
		}

		indicateTextline(*S, TextMatrix);

	}


	/*
	if (GetAsyncKeyState(0x41) & 0x8000) // A, 왼쪽으로 이동
	{
	findTextlineSelection(*S, TextMatrix, &x1, &y1);

	if (x1 == 1) { // x좌표 바꿈
	x1 = 0;
	TextMatrix[y1][x1 + 1] = 0; // 원래 좌표는 0으로
	TextMatrix[y1][x1] = 1; // 새 좌표는 1로
	}


	}
	if (GetAsyncKeyState(0x44) & 0x8000) // D, 오른쪽으로 이동
	{

	findTextlineSelection(*S, TextMatrix, &x1, &y1);

	if (x1 == 0) { // x좌표 바꿈
	x1 = 1;
	TextMatrix[y1][x1 - 1] = 0; // 원래 좌표는 0으로
	TextMatrix[y1][x1] = 1; // 새 좌표는 1로
	}
	else {

	}
	}



	if (GetAsyncKeyState(0x45) & 0x8000) // E, 키워드 교체
	{

	if (x1 == 0) {
	}
	else {
	magic(S);
	}
	}

	if (GetAsyncKeyState(0x51) & 0x8000) // Q, 키워드 교체
	{

	if (x1 == 0) {
	}
	else {
	magic2(S);
	}

	}
	return;

	*/

}


//---------------------------------------------------------------------- 시스템

void itemAcquire(Stage* S, int x, int y) { // 키워드, 아이템 등 획득
	y = y - 10; // 플레이어 위치와 좌표계 일치시키기
	if (control_gravity == 1) { // 중력이 아래쪽일 때
		for (int i = 0; i <= 2; i++) { // 발,몸통,머리 셋 전부 체크
			if (S->stageinfo[y - i][x].n2 == -101) { // PASS
				addkeyword(1, -101);
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -102) { // FALL
				addkeyword(2, -102);
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -103) { // SWITCH
				addkeyword(3, -103);
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -104) { // FLOAT
				addkeyword(4, -104);
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -105) { // PUSH
				addkeyword(5, -105);
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -1) { // Star
				clear++;
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애줌
				play_effect_sound("C:\\sounds\\star.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -201) { // 중력을 왼쪽으로
				clear_character(S, cur_x, cur_y);
				control_gravity = 2;
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -3) { // bonus
				c_bonus += 1;
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}

		}
	}
	else if (control_gravity == 2) { // 중력이 왼쪽일 때
		for (int i = 0; i <= 2; i++) { // 발,몸통,머리 셋 전부 체크
			if (S->stageinfo[y][x + i].n2 == -103) { // SWITCH
				addkeyword(3, -103);
				S->stageinfo[y][x + i].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y][x + i].n2 == -102) { // FALL
				addkeyword(2, -102);
				S->stageinfo[y][x + i].n2 = 0; // 아이템은 없애주고
				indicateTextline(*S, TextMatrix); // 텍스트 초기화
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y][x + i].n2 == -1) { // Star
				play_effect_sound("C:\\sounds\\star.wav");
				clear++;
				S->stageinfo[y][x + i].n2 = 0; // 아이템은 없애줌
			}
			if (S->stageinfo[y][x + i].n2 == -201) { // 중력을 왼쪽으로
				play_effect_sound("C:\\sounds\\item_aquired.wav");
				control_gravity = 2;
				S->stageinfo[y][x + i].n2 = 0; // 아이템은 없애주고
			}
			if (S->stageinfo[y][x + i].n2 == -3) { // bonus
				play_effect_sound("C:\\sounds\\item_aquired.wav");
				c_bonus += 1;
				S->stageinfo[y - i][x].n2 = 0; // 아이템은 없애주고
			}

		}
	}

	
	keyWordindicator();
	indicateItems();

}

void stageclear(inter* M) { //클리어 시 다음 넘어가는 함수
	
	
	setCursorPosition(25, 30);
	textcolor(3);
	printf("┌────────────────────────────┐");
	for (int i = 1; i < 15; i++) {
		Sleep(30);
		setCursorPosition(25, 30 + i);
		printf("│                            │");
		setCursorPosition(25, 31 + i);
		printf("└────────────────────────────┘");
	}
	/*
	setCursorPosition(25, 45);
	printf("└────────────────────────────┘");
	*/
	
	Sleep(300);
	setCursorPosition(34, 32);
	textcolor(14);
	printf(" STAGE CLEAR");
	Sleep(500);
	setCursorPosition(30, 34);
	textcolor(15);
	play_effect_sound("C:\\sounds\\keyword_change.wav");
	printf("CLEAR TIME : %d", c_time);
	Sleep(500);
	setCursorPosition(30, 36);
	play_effect_sound("C:\\sounds\\keyword_change.wav");
	printf("Bonus");
	Sleep(500);
	setCursorPosition(30, 37);
	play_effect_sound("C:\\sounds\\keyword_change.wav");
	textcolor(6);
	printf("⊙");
	textcolor(15);
	printf(" x %d", c_bonus);
	Sleep(500);
	setCursorPosition(30, 39);
	play_effect_sound("C:\\sounds\\keyword_change.wav");
	c_score = 30000 / (1+c_time) + 100 * c_bonus;
	printf("SCORE : ");
	textcolor(12);
	printf("%d", c_score);
	textcolor(15);
	Sleep(500);
	setCursorPosition(27, 42);
	printf(" Press");
	textcolor(11);
	printf(" Enter ");
	textcolor(15);
	printf("To Next Level");

	play_effect_sound("C:\\sounds\\stage_clear.wav");


	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 13) {
				break;
			}
		}
	}
	All_erase();

	clear = 0;
	bonus += c_bonus;
	c_bonus = 0;
	right = 0;
	left = 0;
	jump_height = 0;
	jump_and_falling = 0;
	control_gravity = 1;
	isfalling = 0;
	isStarfalling = 0;
	Misfalling = 0;


	//다음 스테이지 그리기
	drawStage(M[c_stage].TextInterface, 0, 0);
	drawStage(M[c_stage].ShopInterface, 40, 10);
	drawStage(M[c_stage].TextStored, 40, 0);
	drawStage(M[c_stage].S, 0, 10);
	set_character(&M[c_stage].S, start_arr[c_stage][0], start_arr[c_stage][1]); //스테이지 2 시작시 시작 좌표
	indicateItems();
	indicateTextline(M[c_stage].S, TextMatrix);
	seachmoving(&M[c_stage].S, 0, 10);
	//변수들 초기화
	for (int i = 0; i < 8; i++) {
		currentKeywords[i] = keywords[1][i];
	}
	c_score = 0;
	c_time = 0;
	
}

void death_effect(Stage* S) {
	// cur_x, cur_y 디버깅 출력

	clear_character(S, cur_x, cur_y);


	const char* explosion_frames[] = {
		" * ",
		"* *",
		" * ",
	};
	int num_frames = 3;

	for (int i = 0; i < num_frames; i++) {
		// 폭발 프레임 출력 (세로로 한 줄만 표시)
		setCursorPosition(2 * cur_x, cur_y - 1); // cur_y를 기준으로 중앙 출력
		printf("%s", explosion_frames[i]);
		fflush(stdout); // 버퍼 플러시

		Sleep(200);

		// 이전 프레임 지우기
		setCursorPosition(2 * cur_x, cur_y - 1);
		printf("   "); // 한 줄 삭제
		fflush(stdout);
	}

}



void gameover(inter* M, Stage* S) { //죽을 시 다시시작 함수
	play_effect_sound("C:\\sounds\\deth.wav");
	textcolor(12);
	death_effect(S);
	textcolor(15);
	Sleep(100);
	setCursorPosition(25, 30);
	printf("┌────────────────────────────┐");
	for (int i = 1; i < 15; i++) {
		setCursorPosition(25, 30 + i);
		printf("│                            │");
	}
	setCursorPosition(25, 45);
	printf("└────────────────────────────┘");
	Sleep(100);
	setCursorPosition(35, 32);
	printf("STAGE Fail");
	Sleep(100);
	setCursorPosition(37, 34);
	printf("RESULT");
	Sleep(100);
	setCursorPosition(30, 42);
	printf("Press ESC To Restart");
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 27) {
				break;
			}
		}
	}

	for (int i = 0; i < 16; i++) {
		setCursorPosition(25, 30 + i);
		printf("                              ");
	}

	getinfo(&M->S, stageinfos[c_stage], 40, 60);
	M->S.NumofLines = 2;
	if (c_stage == 2) {
		S->NumofLines = 3;
		S->stageinfo[4][4].mod = 1;
		S->stageinfo[55][38].mod = 3;
		S->stageinfo[58][2].mod = 3;
	}
	M->S.Textlines[0].element = text_arr[c_stage][0][0];
	M->S.Textlines[0].keyword = text_arr[c_stage][0][1];
	M->S.Textlines[1].element = text_arr[c_stage][1][0];
	M->S.Textlines[1].keyword = text_arr[c_stage][1][1];
	M->S.Textlines[2].element = text_arr[c_stage][2][0];
	M->S.Textlines[2].keyword = text_arr[c_stage][2][1];



	clear = 0;
	c_bonus = 0;
	right = 0;
	left = 0;
	jump_height = 0;
	jump_and_falling = 0;
	clear_character(&M->S, cur_x, cur_y);
	control_gravity = 1;
	isfalling = 0;
	ispush = 0;
	Mispush = 0;
	isStarfalling = 0;
	Misfalling = 0;
	isdeath = 0;
	set_character(&M->S, start_arr[c_stage][0], start_arr[c_stage][1]); // 캐릭터 위치 설정

	if (c_stage == 2) { // 3스테이지 전용


		setCursorPosition(2 * cur_x, cur_y - 2);
		printf("  ");
		setCursorPosition(2 * cur_x, cur_y - 1);
		printf("  ");
		setCursorPosition(2 * cur_x, cur_y);
		printf("  ");

		setCursorPosition(2 * cur2_x, cur2_y - 2);
		printf("  ");
		setCursorPosition(2 * cur2_x, cur2_y - 1);
		printf("  ");
		setCursorPosition(2 * cur2_x, cur2_y);
		printf("  ");


		dual = 1;
		cur_x = 1, cur_y = 68;
		cur2_x = 30, cur2_y = 68; //캐릭터2의 '발'의 좌표
		textcolor(12); // 빨간색
		setCursorPosition(2 * cur_x, cur_y - 2);
		printf("○");
		setCursorPosition(2 * cur_x, cur_y - 1);
		printf("▣");
		setCursorPosition(2 * cur_x, cur_y);
		printf("∥");
		textcolor(15); // 다시 하얀색으로

		textcolor(9); // 파란색
		setCursorPosition(2 * cur2_x, cur2_y - 2);
		printf("○");
		setCursorPosition(2 * cur2_x, cur2_y - 1);
		printf("□");
		setCursorPosition(2 * cur2_x, cur2_y);
		printf("∥");
		textcolor(15);
	}

	for (int i = 0; i < 8; i++) {
		currentKeywords[i] = keywords[0][i];
	}

	ALL_drawStage(M->S, 0, 10);
	indicateTextline(M->S, TextMatrix);
	indicateItems();
	seachmoving(&M[c_stage].S, 0, 10);

	keyWordindicator();

	//임시로 pass 해제용
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 40; j++) {
			// isSolid를 0으로 만들어 충돌 없앰
			if (M->S.stageinfo[i][j].n3 == 11) { // 파란색 블록을 빈 블록으로
				M->S.stageinfo[i][j].isSolid = 1;
			}
			else if (M->S.stageinfo[i][j].n3 == 12) { // 빨간색 블록을 빈 블록으로
				M->S.stageinfo[i][j].isSolid = 1;
			}
		}
	}


}





