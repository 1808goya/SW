#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Stages.h"

int cur_x = 10 / 2, cur_y = 1; // ĳ������ '��'�� ��ǥ
int cur2_x = 30, cur2_y = 68; //ĳ����2�� '��'�� ��ǥ
int cur2 = 0; //ĳ�� ��������϶� ��ĥ�� Ȯ�ο�
int dual = 0; //ĳ�� ����ġ�� ���� ����, 0�̸� ĳ��1��, 1�̸� 2���ε� ���� 1, 2�� 2���ε� ���� 2
int right = 0, left = 0; // ���� ����
int jump_height = 0; // ���� ������ ��Ÿ���� ���ÿ� ������ �� �� ������ �󸶳� �� �ö󰡾� �ϴ����� ��Ÿ���� �����Դϴ�.
int jump_and_falling = 0; //������ �ְ� ���̿� ������ �� �ٽ� ���� �� ���� ��Ȳ���� ����� ����
int control_gravity = 1; // 1�� �Ʒ���, 2�� ��������
int x1 = 1; // x1�� x2�� Ű���� ��ü �ε������Ϳ� ����
int y1 = 0;
int isfalling = 0;
int isStarfalling = 0;
int clear = 0; //Ŭ����� ���ӿ��� ����
int bonus = 0, c_bonus = 0; //�� ���ʽ�, �� �������� ���� ���� bonus ����
int m[4][10], M = 0; //�����̴� �� ���� �迭
int ispush = 0; //pushŰ���� 0�̸� �۵����� 1�̸� �۵�
int Mispush = 0; //pushŰ���� - Machine�� ����
int Misfalling = 0; //fall, floatŰ���� - Machine�� ����
int time_reset = 0;
int isdeath = 0;

int shootrate = 0;


int isCharacterThere(int x, int y) { // Stageinfo�� ĳ���Ϳ��� ��ġ�� ���ؼ� '�ش� ĭ'�� ĳ������ ������ �ִ��� Ȯ��
	// 1�̸� ĳ������ ������ �ְ�, 0�̸� ����. �߷¿� ���� ������ �ٲ�°͵� �����

	int R = 0;

	if (control_gravity == 1) { // �߷� �Ʒ�
		for (int i = 0; i < 3; i++) {
			if (cur_x == x && (cur_y - 10 - i) == y) {
				R = 1;
			}
		}
	}
	else if (control_gravity == 2) { // �߷� ����
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


void draw_character(Stage* S, int x, int y) { // x,y�� ĳ������ '�� ��(�ٸ�) �κ�' ����

	drawStage(*S, 0, 10);
	if (control_gravity == 1)
	{
		if (dual == 0) {
			setCursorPosition(2 * x, y - 2);
			printf("��");
			setCursorPosition(2 * x, y - 1);
			printf("��");
			setCursorPosition(2 * x, y);
			printf("��");
		}
		else if (dual == 1) {
			textcolor(12); // ������
			setCursorPosition(2 * x, y - 2);
			printf("��");
			setCursorPosition(2 * x, y - 1);
			printf("��");
			setCursorPosition(2 * x, y);
			printf("��");
			textcolor(15); // �ٽ� �Ͼ������
		}
		else {
			textcolor(9); // �Ķ���
			setCursorPosition(2 * x, y - 2);
			printf("��");
			setCursorPosition(2 * x, y - 1);
			printf("��");
			setCursorPosition(2 * x, y);
			printf("��");
			textcolor(15); // �ٽ� �Ͼ������
		}
	}

	if (control_gravity == 2)
	{
		setCursorPosition(2 * (x + 2), y);
		printf("��");
		setCursorPosition(2 * (x + 1), y);
		printf("��");
		setCursorPosition(2 * x, y);
		printf("��");
	}
	// S->stageinfo[y][x].n2 = 7; // ĳ���� ��ġ ǥ��
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
				textcolor(9); // �Ķ���
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("��");
				textcolor(15); // �ٽ� �Ͼ������
			}
			else {
				textcolor(12); // ������
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("��");
				textcolor(15); // �ٽ� �Ͼ������
			}
		}

		if (cur2 == 2 && ((cur_x != cur2_x) || (cur_y < cur2_y - 2 && cur_y > cur2_y + 2))) {
			cur2 = 0;
			if (dual == 1) {
				textcolor(9); // �Ķ���
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("��");
				textcolor(15); // �ٽ� �Ͼ������
			}
			else {
				textcolor(12); // ������
				setCursorPosition(2 * cur2_x, cur2_y - 2);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y - 1);
				printf("��");
				setCursorPosition(2 * cur2_x, cur2_y);
				printf("��");
				textcolor(15); // �ٽ� �Ͼ������
			}
		}
	}
}

void draw_ready_to_jump_character(Stage* S, int x, int y)// �Է¹��� x, y��ǥ�� �Է� ���� ĳ���� ��� ���
{
	drawStage(*S, 0, 10);
	if (control_gravity == 1)
	{
		setCursorPosition(2 * x, y - 2); //�ڵ� �ϼ��Ǹ� ���� ���� Ȯ��
		printf("  ");
		setCursorPosition(2 * x, y - 1);
		printf("��");
		setCursorPosition(2 * x, y);
		printf("��");
	}
	if (control_gravity == 2)
	{
		setCursorPosition(2 * (x + 2), y);
		printf("  ");
		setCursorPosition(2 * (x + 1), y);
		printf("��");
		setCursorPosition(2 * x, y);
		printf("��");
	}
	return;
}

void clear_character(Stage* S, int x, int y) {
	if (control_gravity == 1)
	{
		if (S->stageinfo[y - 10][x].n2 != 0 || S->stageinfo[y - 11][x].n2 != 0 || S->stageinfo[y - 12][x].n2 != 0) { //�̰� �� ����?
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

void set_character(Stage* S, int x, int y) { // ĳ������ ��ġ�� �ٲٰ�, �׿� ���� (�ٸ���) ��ǥ ���� ��������

	// S->stageinfo[y][x].n2 = 7; // �� ��ġ ����
	cur_x = x;
	cur_y = y;
	draw_character(S, cur_x, cur_y);
}

void set_Block(Stage* S, int x, int y) { // ĳ������ ��ġ�� �ٲٰ�, �׿� ���� (�ٸ���) ��ǥ ���� ��������

	// S->stageinfo[y][x].n2 = 7; // �� ��ġ ����
	cur_x = x;
	cur_y = y;
	draw_character(S, cur_x, cur_y);
}

int isCollision(Stage* S, int x, int y) { // x,y�� �浹������ �������� return
	y = y - 10;

	if (S->stageinfo[y][x].isSolid == 1) { // �浹������ ������ 1 ��ȯ, -10�� ���ִ� ������ �������̽������� ���� ���������� ��ǥ�� 10��ŭ �Ʒ��� �ֱ� ����
		if (S->stageinfo[y][x].n2 == 14 || S->stageinfo[y][x].n2 == 15 || S->stageinfo[y][x].n2 == 16) {
			clear--;
		}
		return 1;
	}

	return 0; // �ƴϸ� 0 ��ȯ

}

int isCollisionforblock(Stage* S, int x, int y) { // x,y�� �浹������ �������� return

	if (S->stageinfo[y][x].isSolid == 1) { // �浹������ ������ 1 ��ȯ
		return 1;
	}

	return 0; // �ƴϸ� 0 ��ȯ

}

int isblockCollision(Stage* S, int x, int y) { // x,y�� �浹������ �������� return

	if (S->stageinfo[y][x].isSolid == 1) { // �浹������ ������ 1 ��ȯ, -10�� ���ִ� ������ �������̽������� ���� ���������� ��ǥ�� 10��ŭ �Ʒ��� �ֱ� ����
		return 1;
	}

	return 0; // �ƴϸ� 0 ��ȯ
}

void to_push(Stage* S, int pre_x, int pre_y)
{
	if (control_gravity == 1)
	{
		if (ispush == 1) {
			if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x, pre_y - 1) == 0 && isCollision(S, pre_x, pre_y - 2) == 0) { // �浹������ ������
				clear_character(S, cur_x, cur_y); //�� ĳ���� ����
				set_character(S, pre_x, pre_y); // ĳ���͸� �ش� ��ǥ�� �̵�
			}

			else if (isCollision(S, pre_x, pre_y) == 1 || isCollision(S, pre_x, pre_y - 1) == 1 || isCollision(S, pre_x, pre_y - 2) == 1)
			{
				pre_y -= 10;
				int did_move = 0;


				if (S->stageinfo[pre_y][pre_x].n3 == 11 || S->stageinfo[pre_y][pre_x].n3 == 12) //ĳ���Ͱ� �̵� �ÿ� �浹 �ϴµ� ä���� �Ķ� ��� �Ǵ� ���� ����� ������ ��
				{

					if (pre_x > cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ���� = ���������� �̵���
					{
						if (isblockCollision(S, pre_x + 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x + 1].n2 = S->stageinfo[pre_y][pre_x].n2;//������ �̵� �� ä���� �Ķ� ���or ��������� ����������
							S->stageinfo[pre_y][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ŭ = �������� �̵���
					{
						if (isblockCollision(S, pre_x - 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x - 1].n2 = S->stageinfo[pre_y][pre_x].n2;//���� �̵� �� ä���� �Ķ� ���or ��������� ��������
							S->stageinfo[pre_y][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 1][pre_x].n3 == 11 || S->stageinfo[pre_y - 1][pre_x].n3 == 12) //ĳ���Ͱ� �̵� �ÿ� �浹 �ϴµ� ä���� �Ķ� ��� �Ǵ� ���� ����� ������ ��
				{

					if (pre_x > cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ���� = ���������� �̵���
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x + 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//������ �̵� �� ä���� �Ķ� ���or ��������� ����������
							S->stageinfo[pre_y - 1][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ŭ = �������� �̵���
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x - 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//���� �̵� �� ä���� �Ķ� ���or ��������� ��������
							S->stageinfo[pre_y - 1][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 2][pre_x].n3 == 11 || S->stageinfo[pre_y - 1][pre_x].n3 == 12) //ĳ���Ͱ� �̵� �ÿ� �浹 �ϴµ� ä���� �Ķ� ��� �Ǵ� ���� ����� ������ ��
				{

					if (pre_x > cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ���� = ���������� �̵���
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x + 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//������ �̵� �� ä���� �Ķ� ���or ��������� ����������
							S->stageinfo[pre_y - 2][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 2][pre_x].n2 = 0;
							S->stageinfo[pre_y - 2][pre_x].isSolid = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ŭ = �������� �̵���
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x - 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//���� �̵� �� ä���� �Ķ� ���or ��������� ��������
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


		//-------------------------------------------------------------- MACHINE�� ����Ǵ� ���

		if (Mispush == 1) {
			if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x, pre_y - 1) == 0 && isCollision(S, pre_x, pre_y - 2) == 0) { // �浹������ ������
				clear_character(S, cur_x, cur_y); //�� ĳ���� ����
				set_character(S, pre_x, pre_y); // ĳ���͸� �ش� ��ǥ�� �̵�
			}

			else if (isCollision(S, pre_x, pre_y) == 1 || isCollision(S, pre_x, pre_y - 1) == 1 || isCollision(S, pre_x, pre_y - 2) == 1)
			{
				pre_y -= 10;
				int did_move = 0;


				if (S->stageinfo[pre_y][pre_x].n3 == 10) //ĳ���Ͱ� �̵� �ÿ� �浹 �ϴµ� ä���� �Ķ� ��� �Ǵ� ���� ����� ������ ��
				{

					if (pre_x > cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ���� = ���������� �̵���
					{
						if (isblockCollision(S, pre_x + 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x + 1].n2 = S->stageinfo[pre_y][pre_x].n2;//������ �̵� �� ä���� �Ķ� ���or ��������� ����������
							S->stageinfo[pre_y][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;

							S->stageinfo[pre_y][pre_x + 1].mod = S->stageinfo[pre_y][pre_x].mod;
							S->stageinfo[pre_y][pre_x].mod = 0;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ŭ = �������� �̵���
					{
						if (isblockCollision(S, pre_x - 1, pre_y) != 1)
						{
							S->stageinfo[pre_y][pre_x - 1].n2 = S->stageinfo[pre_y][pre_x].n2;//���� �̵� �� ä���� �Ķ� ���or ��������� ��������
							S->stageinfo[pre_y][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y][pre_x].n2 = 0;
							S->stageinfo[pre_y][pre_x].isSolid = 0;


							S->stageinfo[pre_y][pre_x - 1].mod = S->stageinfo[pre_y][pre_x].mod;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 1][pre_x].n3 == 10) //ĳ���Ͱ� �̵� �ÿ� �浹 �ϴµ� ä���� �Ķ� ��� �Ǵ� ���� ����� ������ ��
				{

					if (pre_x > cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ���� = ���������� �̵���
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x + 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//������ �̵� �� ä���� �Ķ� ���or ��������� ����������
							S->stageinfo[pre_y - 1][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 1][pre_x + 1].mod = S->stageinfo[pre_y - 1][pre_x].mod;
							did_move += 1;

						}
					}

					if (pre_x < cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ŭ = �������� �̵���
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 1) != 1)
						{
							S->stageinfo[pre_y - 1][pre_x - 1].n2 = S->stageinfo[pre_y - 1][pre_x].n2;//���� �̵� �� ä���� �Ķ� ���or ��������� ��������
							S->stageinfo[pre_y - 1][pre_x - 1].isSolid = 1;
							S->stageinfo[pre_y - 1][pre_x].n2 = 0;
							S->stageinfo[pre_y - 1][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 1][pre_x - 1].mod = S->stageinfo[pre_y - 1][pre_x].mod;
							did_move += 1;
						}
					}
				}

				if (S->stageinfo[pre_y - 2][pre_x].n3 == 10) //ĳ���Ͱ� �̵� �ÿ� �浹 �ϴµ� ä���� �Ķ� ��� �Ǵ� ���� ����� ������ ��
				{

					if (pre_x > cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ���� = ���������� �̵���
					{
						if (isblockCollision(S, pre_x + 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x + 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//������ �̵� �� ä���� �Ķ� ���or ��������� ����������
							S->stageinfo[pre_y - 2][pre_x + 1].isSolid = 1;
							S->stageinfo[pre_y - 2][pre_x].n2 = 0;
							S->stageinfo[pre_y - 2][pre_x].isSolid = 0;

							S->stageinfo[pre_y - 2][pre_x + 1].mod = S->stageinfo[pre_y - 2][pre_x].mod;
							did_move += 1;
						}
					}

					if (pre_x < cur_x) //���� x��ǥ�� �������� �̵��� x��ǥ���� ŭ = �������� �̵���
					{
						if (isblockCollision(S, pre_x - 1, pre_y - 2) != 1)
						{
							S->stageinfo[pre_y - 2][pre_x - 1].n2 = S->stageinfo[pre_y - 2][pre_x].n2;//���� �̵� �� ä���� �Ķ� ���or ��������� ��������
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
	// if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x + 1, pre_y) == 0 && isCollision(S, pre_x + 2, pre_y) == 0) { // �浹������ ������
	// clear_character(S, cur_x, cur_y); //�� ĳ���� ����
	// set_character(S, pre_x, pre_y); // ĳ���͸� �ش� ��ǥ�� �̵�
	// }
	//}
	//�������� ���󿡼� �ʿ� �� �߰� �ۼ�
}

void move_character(Stage* S, int pre_x, int pre_y) {

	if (ispush == 1 || Mispush == 1)
	{
		to_push(S, pre_x, pre_y);
	}

	else if (control_gravity == 1)
	{
		if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x, pre_y - 1) == 0 && isCollision(S, pre_x, pre_y - 2) == 0) { // �浹������ ������
			clear_character(S, cur_x, cur_y); //�� ĳ���� ����
			set_character(S, pre_x, pre_y); // ĳ���͸� �ش� ��ǥ�� �̵�
		}
	}

	else if (control_gravity == 2)
	{
		if (isCollision(S, pre_x, pre_y) == 0 && isCollision(S, pre_x + 1, pre_y) == 0 && isCollision(S, pre_x + 2, pre_y) == 0) { // �浹������ ������
			clear_character(S, cur_x, cur_y); //�� ĳ���� ����
			set_character(S, pre_x, pre_y); // ĳ���͸� �ش� ��ǥ�� �̵�
		}
	}
}

void move_block(Stage* S, int pre_x, int pre_y) {
	if (isCollision(S, pre_x, pre_y) == 0) { // �浹������ ������
		//set_block(S, pre_x, pre_y);
	}
}

int isair(Stage* S) { // ĳ������ �ٷ� �Ʒ��� �浹������ �������� Ȯ��

	if (control_gravity == 1)
	{
		if (isCollision(S, cur_x, cur_y + 1) == 1) { // �浹������ ������(ĳ���Ͱ� ü�� ���� �ƴϸ�)
			return 0; // 0 ��ȯ
		}
		return 1; // ü�� ���̸� 1 ��ȯ
	}

	if (control_gravity == 2)
	{
		if (isCollision(S, cur_x - 1, cur_y) == 1) { // �浹������ ������(ĳ���Ͱ� ü�� ���� �ƴϸ�)
			return 0; // 0 ��ȯ
		}
		return 1; // ü�� ���̸� 1 ��ȯ
	}
}


int isairforblock(Stage* S, int x, int y) { // x,y�� �ٷ� �Ʒ��� �浹������ �������� Ȯ��
	if (isCollisionforblock(S, x, y + 1) == 1) { // �浹������ ������(�ٴ��� ���� �ʾ�����)
		return 0; // 0 ��ȯ
	}
	return 1; // ü�� ���̸� 1 ��ȯ
}

void gravity(Stage* S) {

	if (control_gravity == 1)
	{
		if (jump_height == 0) { // ���� ���� �ƴϸ鼭 ü�� ���̸�
			if (isair(S) == 1)
				move_character(S, cur_x, cur_y + 1); // ĳ���͸� 1ĭ ����
			else {
				jump_and_falling = 0; //���� ���� �ʱ�ȭ
			}
		}
		if (S->stageinfo[cur_y - 9][cur_x].n3 == 14 || S->stageinfo[cur_y - 9][cur_x].n3 == 15 || S->stageinfo[cur_y - 9][cur_x].n3 == 16) //�ؿ��� ���ö��
			clear--;
	}

	if (control_gravity == 2)
	{
		if (jump_height == 0) { // ���� ���� �ƴϸ鼭 ü�� ���̸�
			if (isair(S) == 1)
				move_character(S, cur_x - 1, cur_y); // ĳ���͸� 1ĭ ����
			else {
				jump_and_falling = 0; //���� ���� �ʱ�ȭ
				if (S->stageinfo[cur_y - 10][cur_x - 1].n3 == 14 || S->stageinfo[cur_y - 10][cur_x - 1].n3 == 15 || S->stageinfo[cur_y - 10][cur_x - 1].n3 == 16) //�ؿ��� ���ö��
					clear--;
			}
		}
	}
}


void gravityPlatform(Stage* S, int n) { // �ڵ� 'n'�� �ش��ϴ� ���� ����
	if (isgravity == 1) { // isgravity�� 1�̿��� ���� �߷��� �ۿ��� ��쿡 �۵�

		for (int i = 58; i > 1; i--) { // y�� �������� ã��
			for (int j = 1; j < 39; j++) {
				if (isairforblock(S, j, i) == 1 && S->stageinfo[i][j].n3 == 8) { // �����̶�� ��ĭ ������, �ڵ� n�� �������
					S->stageinfo[i][j].n2 = 0; // ���� ���� �ִ� ��ġ�� 0����
					S->stageinfo[i + 1][j].n2 = n; // �� �ٷ� �Ʒ��� n����
				}
			}
		}
	}
}

void seachmoving(Stage* S, int x, int y) { //�����̴� �� ã�� �Լ�
	int t = 0, J; //��� ���� Ȯ�ο� ����
	M = 0; //������ �ʱ�ȭ
	for (int i = 0; i < S->y; i++)
		for (int j = 0; j < S->x; j++)
		{
			if (S->stageinfo[i][j].n2 == 13 && t == 0) { //�����̴� �� ����� ���� ����
				J = j;
				m[0][M] = j; //x��ǥ
				m[1][M] = i; //y��ǥ
				m[2][M] = 0; //�ʱ� ���� ������
				t = 1;
			}
			if (S->stageinfo[i][j].n2 != 13 && t == 1) { //�� ��� ���� ������ ��ĭ ��
				m[3][M] = j - J; //����
				t = 0;
				M++; //�����̴� �� ���� ����
			}
		}
}

void movingblock(Stage* S) { // �����̴� ��
	int cm = 0; //ĳ���Ͱ� ������ ���� �ִ��� Ȯ���ϴ� ����
	for (int i = 0; i < M; i++) {
		if (m[2][i] == 0) { //������
			if (control_gravity == 1) {
				if (S->stageinfo[cur_y - 9][cur_x].n3 == 13 && isCollision(S, cur_x + 1, cur_y) == 0 && isCollision(S, cur_x + 1, cur_y - 1) == 0 && isCollision(S, cur_x + 1, cur_y - 2) == 0) { //���� �浹 ������ ������
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
			printf("��");
			textcolor(15);
			m[0][i]++;
			if (S->stageinfo[m[1][i]][m[0][i] + m[3][i] + 1].n2 > 0) //�������� ����ϴ� ���� �ƴҰ�� ������ȯ
				m[2][i] = 1;
		}
		else { //����
			if (control_gravity == 1) {
				if (S->stageinfo[cur_y - 9][cur_x].n3 == 13 && isCollision(S, cur_x - 1, cur_y) == 0 && isCollision(S, cur_x - 1, cur_y - 1) == 0 && isCollision(S, cur_x - 1, cur_y - 2) == 0) { //���� �浹 ������ ������
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
			printf("��");
			textcolor(15);
			m[0][i]--;
			if (S->stageinfo[m[1][i]][m[0][i] - 2].n2 > 0) //������ ����ϴ� ���� �ƴҰ�� ������ȯ
				m[2][i] = 0;
		}
	}
	if (cm == 1) { //���������� �����̰� ������ ������ ���� �ִٸ�
		clear_character(S, cur_x, cur_y);
		cur_x++;
		cm = 0;
	}
	else if (cm == -1) { //�������� �����̰� ������ ������ ���� �ִٸ�
		clear_character(S, cur_x, cur_y);
		cur_x--;
		cm = 0;
	}
}

//////////////////////////////fall ����




void to_fall(Stage* S)
{
	if (isfalling == 1 && control_gravity == 1) //�߷��� �Ʒ��� �� �Ʒ����� �������� �˻�
	{
		for (int i = 59; i >= 0; i--)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j, i + 1) == 0) // �Ʒ��� �浹�� �ƴ� ���
					{
						//���ð� ������ ���� ���� ��� ���ı�(�߷� �����϶��� float�� �ϴ� ���ص�)
						/*if((S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15) && S->stageinfo[i + 1][j].n3 == -1){
							S->stageinfo[i + 1][j].n2 = 0;
							S->stageinfo[i + 1][j].n3 = 0;
							S->stageinfo[i + 1][j].n4 = 0;
							clear++;
						}
						*/
						//if (j == cur_x && i + 1 == cur_y) //ĳ���Ͱ� �򸮸� �����ɷ� �ϰ� �����ϸ� �� �Ͱ����ϴ�
						// return;
						// ��ĭ �Ʒ��� issolid�� 0������ �迭�� 0(�����)�� �ƴѰ�, �� ����Ǵ� ���̶�� ���̰� n4�� 0, �� ����ǰ� �ִ����� �ƴ� �� �̹Ƿ� ����� ���۵Ǵ� ������ ����� ���Դϴ�
						if (S->stageinfo[i + 1][j].n2 != 0 && S->stageinfo[i + 1][j].n4 == 0)

							S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 11) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i + 1][j].n2 = 11; // ��ĭ �Ʒ��� n2�� ����

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i + 1][j].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i + 1][j].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i + 1][j].n2 = 15;

						S->stageinfo[i + 1][j].isSolid = 1; //���� �������� ����̹Ƿ� ������ �ٲ� ��ĭ�Ʒ��� �浹������ �־��ݴϴ� ���� ��� ������ ������ �� �ڵ尡 �����ϴ�

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i - 1][j].isSolid == 0) { //������� ������ ��ĭ ���� isSolid�� 0, �� ����� ������ ������ ��� ��� �ǹ��Դϴ�
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (isfalling == 1 && control_gravity == 2) //�߷��� ���� ���� ������ ������ ������ �˻�
	{
		for (int j = 0; j < 40; j++)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j - 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //ĳ���Ͱ� �򸮸� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i][j - 1].n2 != 0 && S->stageinfo[i][j - 1].n4 == 0)

							S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 11) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i][j - 1].n2 = 11; // ��ĭ �Ʒ��� n2�� ����

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i][j - 1].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i][j - 1].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i][j - 1].n2 = 15;

						S->stageinfo[i][j - 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j + 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

	if (isStarfalling == 1 && control_gravity == 1) //�߷��� �Ʒ��� �� �Ʒ����� �������� �˻�
	{
		for (int i = 59; i >= 0; i--)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j, i + 1) == 0) // �Ʒ��� �浹�� �ƴ� ���
					{
						//if (j == cur_x && i + 1 == cur_y) //ĳ���Ͱ� �򸮸� �����ɷ� �ϰ� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i + 1][j].n2 != 0 && S->stageinfo[i + 1][j].n4 == 0)

							S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						S->stageinfo[i + 1][j].n2 = -1; // ��ĭ �Ʒ��� n2�� ����

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i - 1][j].isSolid == 0) { // ���� �ִ�ĭ�� n4�� 0�� �ƴϰ� ���� �ִ�ĭ�� ��ĭ ���� n2�� 0�̸�???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
					//�����϶� ���� ������ �� �ı�(���� �߷°� float�϶��� �ϴ� ���ص�)
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


	if (isStarfalling == 1 && control_gravity == 2) //�߷��� ����, ���� ������ ������ ������ �˻�
	{
		for (int j = 0; j < 40; j++)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j - 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //ĳ���Ͱ� �򸮸� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i][j - 1].n2 != 0 && S->stageinfo[i][j - 1].n4 == 0) // �Ʒ��� n2�� 0�� �ƴϰ� n4�� 0�� �ƴ� ���?

							S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						S->stageinfo[i][j - 1].n2 = -1; // ��ĭ �Ʒ��� n2�� ����

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j + 1].isSolid == 0) { // ���� �ִ�ĭ�� n4�� 0�� �ƴϰ� ���� �ִ�ĭ�� ��ĭ ���� n2�� 0�̸�???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

	if (Misfalling == 1 && control_gravity == 1) //�߷��� �Ʒ��� �� �Ʒ����� �������� �˻�
	{
		for (int i = 59; i >= 0; i--)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j, i + 1) == 0) // �Ʒ��� �浹�� �ƴ� ���
					{
						if (S->stageinfo[i + 1][j].n2 != 0 && S->stageinfo[i + 1][j].n4 == 0)

							S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 10) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i + 1][j].n2 = 10; // ��ĭ �Ʒ��� n2�� ����
						S->stageinfo[i + 1][j].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i + 1][j].isSolid = 1; //���� �������� ����̹Ƿ� ������ �ٲ� ��ĭ�Ʒ��� �浹������ �־��ݴϴ� ���� ��� ������ ������ �� �ڵ尡 �����ϴ�

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i - 1][j].isSolid == 0) { //������� ������ ��ĭ ���� isSolid�� 0, �� ����� ������ ������ ��� ��� �ǹ��Դϴ�
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (Misfalling == 1 && control_gravity == 2) //�߷��� ���� ���� ������ ������ ������ �˻�
	{
		for (int j = 0; j < 40; j++)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j - 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //ĳ���Ͱ� �򸮸� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i][j - 1].n2 != 0 && S->stageinfo[i][j - 1].n4 == 0)

							S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 10) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i][j - 1].n2 = 10; // ��ĭ �Ʒ��� n2�� ����
						S->stageinfo[i][j - 1].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i][j - 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j + 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
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
	if (isfalling == -1 && control_gravity == 1) //�߷��� �Ʒ��� �� �Ʒ����� �������� �˻�
	{
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j, i - 1) == 0) // �Ʒ��� �浹�� �ƴ� ���
					{
						//if (j == cur_x && i + 1 == cur_y) //ĳ���Ͱ� �򸮸� �����ɷ� �ϰ� �����ϸ� �� �Ͱ����ϴ�
						// return;
						// ��ĭ �Ʒ��� issolid�� 0������ �迭�� 0(�����)�� �ƴѰ�, �� ����Ǵ� ���̶�� ���̰� n4�� 0, �� ����ǰ� �ִ����� �ƴ� �� �̹Ƿ� ����� ���۵Ǵ� ������ ����� ���Դϴ�
						if (S->stageinfo[i - 1][j].n2 != 0 && S->stageinfo[i - 1][j].n4 == 0)

							S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 11) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i - 1][j].n2 = 11; // ��ĭ �Ʒ��� n2�� ����

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i - 1][j].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i - 1][j].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i - 1][j].n2 = 15;

						S->stageinfo[i - 1][j].isSolid = 1; //���� �������� ����̹Ƿ� ������ �ٲ� ��ĭ�Ʒ��� �浹������ �־��ݴϴ� ���� ��� ������ ������ �� �ڵ尡 �����ϴ�

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i + 1][j].isSolid == 0) { //������� ������ ��ĭ ���� isSolid�� 0, �� ����� ������ ������ ��� ��� �ǹ��Դϴ�
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}

						if (isCharacterThere(j, i - 1) == 1) { // ĳ���Ͱ� ����������
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

	if (isfalling == -1 && control_gravity == 2) //�߷��� ���� ���� ������ ������ ������ �˻�
	{
		for (int j = 39; j >= 0; j--)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 11 || S->stageinfo[i][j].n3 == 12 || S->stageinfo[i][j].n3 == 14 || S->stageinfo[i][j].n3 == 15)
				{
					if (isblockCollision(S, j + 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //ĳ���Ͱ� �򸮸� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i][j + 1].n2 != 0 && S->stageinfo[i][j + 1].n4 == 0)

							S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 11) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i][j + 1].n2 = 11; // ��ĭ �Ʒ��� n2�� ����

						if (S->stageinfo[i][j].n3 == 12)
							S->stageinfo[i][j + 1].n2 = 12;

						if (S->stageinfo[i][j].n3 == 14)
							S->stageinfo[i][j + 1].n2 = 14;

						if (S->stageinfo[i][j].n3 == 15)
							S->stageinfo[i][j + 1].n2 = 15;

						S->stageinfo[i][j + 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j - 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

	if (isStarfalling == -1 && control_gravity == 1) //�߷��� �Ʒ��� �� �Ʒ����� �������� �˻�
	{
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j, i - 1) == 0) // �Ʒ��� �浹�� �ƴ� ���
					{
						//if (j == cur_x && i + 1 == cur_y) //ĳ���Ͱ� �򸮸� �����ɷ� �ϰ� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i - 1][j].n2 != 0 && S->stageinfo[i - 1][j].n4 == 0)

							S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						S->stageinfo[i - 1][j].n2 = -1; // ��ĭ �Ʒ��� n2�� ����

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i + 1][j].isSolid == 0) { // ���� �ִ�ĭ�� n4�� 0�� �ƴϰ� ���� �ִ�ĭ�� ��ĭ ���� n2�� 0�̸�???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}


	if (isStarfalling == -1 && control_gravity == 2) //�߷��� ����, ���� ������ ������ ������ �˻�
	{
		for (int j = 39; j >= 0; j--)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == -1)
				{
					if (isblockCollision(S, j + 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //ĳ���Ͱ� �򸮸� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i][j + 1].n2 != 0 && S->stageinfo[i][j + 1].n4 == 0) // �Ʒ��� n2�� 0�� �ƴϰ� n4�� 0�� �ƴ� ���?

							S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						S->stageinfo[i][j + 1].n2 = -1; // ��ĭ �Ʒ��� n2�� ����

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j - 1].isSolid == 0) { // ���� �ִ�ĭ�� n4�� 0�� �ƴϰ� ���� �ִ�ĭ�� ��ĭ ���� n2�� 0�̸�???
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}
	//Machine�� ���
	if (Misfalling == -1 && control_gravity == 1) //�߷��� �Ʒ��� �� �Ʒ����� �������� �˻�
	{
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j, i - 1) == 0) // �Ʒ��� �浹�� �ƴ� ���
					{
						//if (j == cur_x && i + 1 == cur_y) //ĳ���Ͱ� �򸮸� �����ɷ� �ϰ� �����ϸ� �� �Ͱ����ϴ�
						// return;
						// ��ĭ �Ʒ��� issolid�� 0������ �迭�� 0(�����)�� �ƴѰ�, �� ����Ǵ� ���̶�� ���̰� n4�� 0, �� ����ǰ� �ִ����� �ƴ� �� �̹Ƿ� ����� ���۵Ǵ� ������ ����� ���Դϴ�
						if (S->stageinfo[i - 1][j].n2 != 0 && S->stageinfo[i - 1][j].n4 == 0)

							S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 10) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i - 1][j].n2 = 10; // ��ĭ �Ʒ��� n2�� ����
						S->stageinfo[i - 1][j].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i - 1][j].isSolid = 1; //���� �������� ����̹Ƿ� ������ �ٲ� ��ĭ�Ʒ��� �浹������ �־��ݴϴ� ���� ��� ������ ������ �� �ڵ尡 �����ϴ�

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i + 1][j].isSolid == 0) { //������� ������ ��ĭ ���� isSolid�� 0, �� ����� ������ ������ ��� ��� �ǹ��Դϴ�
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}

						if (isCharacterThere(j, i - 1) == 1) { // ĳ���Ͱ� ����������
							move_character(S, j, i + 8);
						}

					}
				}
			}
		}
		drawStage(*S, 0, 10);
	}

	if (Misfalling == -1 && control_gravity == 2) //�߷��� ���� ���� ������ ������ ������ �˻�
	{
		for (int j = 39; j >= 0; j--)
		{
			for (int i = 0; i < 60; i++)
			{
				if (S->stageinfo[i][j].n3 == 10)
				{
					if (isblockCollision(S, j + 1, i) == 0) // && isColision
					{
						//if (j - 1 == cur_x && i == cur_y) //ĳ���Ͱ� �򸮸� �����ϸ� �� �Ͱ����ϴ�
						// return;
						if (S->stageinfo[i][j + 1].n2 != 0 && S->stageinfo[i][j + 1].n4 == 0)

							S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; //�ϴ� �Ʒ��� n4�� n2�� �ӽ�������


						if (S->stageinfo[i][j].n3 == 10) // �� �ڵ忡 ���ؼ�
							S->stageinfo[i][j + 1].n2 = 10; // ��ĭ �Ʒ��� n2�� ����
						S->stageinfo[i][j + 1].mod = S->stageinfo[i][j].mod;
						S->stageinfo[i][j].mod = 0;

						S->stageinfo[i][j + 1].isSolid = 1;

						S->stageinfo[i][j].n2 = 0; // ���� �ִ�ĭ�� n2�� ��ĭ����

						S->stageinfo[i][j].isSolid = 0; // ���� �ִ�ĭ�� �浹���� ������

						if (S->stageinfo[i][j].n4 != 0 && S->stageinfo[i][j - 1].isSolid == 0) {
							S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ���� �ִ�ĭ�� n2�� n4�� ���� �ٽ� �ҷ���
							S->stageinfo[i][j].n4 = 0; // n4�� 0����
						}
					}
				}

			}
		}
		drawStage(*S, 0, 10);
	}

}



//------------------------------- PUSH



// --------------------------- �߻�ü ���� ����



void printshootrate() {
	setCursorPosition(88, 50);
	if (shootrate >= 200) {
		setCursorPosition(88, 50);
		// printf("Shootrate :    ");
		shootrate = 0;
	}
	//printf("Shootrate : %d", shootrate);
}


void projectileUpdate(inter* M, Stage* S) { // ����ü �̵���Ű��
	for (int i = 0; i < 60; i++) {
		for (int j = 39; j > 0; j--) {
			if (S->stageinfo[i][j].n2 == -301) { // ������ ����ü�� ���
				if (S->stageinfo[i][j + 1].isSolid != 1) { // �浹������ ���ٸ�

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ������ ĭ�� ������� �ǵ�����
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; // n2�� �ӽ�����
					S->stageinfo[i][j + 1].n2 = -301; // ������ ĭ�� ����ü��
					if (isCharacterThere(j + 1, i) == 1) { // ���� �̵����� �� �÷��̾ �ű⿡ ������)
						clear--;
					}
					if (S->stageinfo[i][j + 1].n4 == -1) { // ���� �̵����� �� ���� �ű⿡ ������)
						S->stageinfo[i][j + 1].n4 = 0; // �� ���ְ� �� �����Ͱ� ����ȿ��
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // �浹������ ������
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // �Ҹ�
				}

			}
		}

		for (int j = 0; j < 39; j++) {

			if (S->stageinfo[i][j].n2 == -302) { // ���� ����ü�� ���
				if (S->stageinfo[i][j - 1].isSolid != 1) { // �浹������ ���ٸ�

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ������ ĭ�� ������� �ǵ�����
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; // n2�� �ӽ�����
					S->stageinfo[i][j - 1].n2 = -302; // ������ ĭ�� ����ü��
					if (isCharacterThere(j - 1, i) == 1) { // ���� �̵����� �� �÷��̾ �ű⿡ ������)
						clear--;
					}
					if (S->stageinfo[i][j - 1].n4 == -1) { // ���� �̵����� �� ���� �ű⿡ ������)
						S->stageinfo[i][j - 1].n4 = 0; // �� ���ְ� �� �����Ͱ� ����ȿ��
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // �浹������ ������
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // �Ҹ�
					S->stageinfo[i][j].n4 = 0;;
				}

			}

		}

	}

	for (int j = 0; j < 40; j++) {
		for (int i = 0; i < 60; i++) {
			if (S->stageinfo[i][j].n2 == -303) { // ���� ����ü�� ���
				if (S->stageinfo[i - 1][j].isSolid != 1) { // �浹������ ���ٸ�

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ������ ĭ�� ������� �ǵ�����
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; // n2�� �ӽ�����
					S->stageinfo[i - 1][j].n2 = -303; // ���� ĭ�� ����ü��
					if (isCharacterThere(j, i - 1) == 1) { // ���� �̵����� �� �÷��̾ �ű⿡ ������)
						clear--;
					}
					if (S->stageinfo[i - 1][j].n4 == -1) { // ���� �̵����� �� ���� �ű⿡ ������)
						S->stageinfo[i - 1][j].n4 = 0; // �� ���ְ� �� �����Ͱ� ����ȿ��
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // �浹������ ������
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // �Ҹ�
					S->stageinfo[i][j].n4 = 0;
				}

			}
		}

		for (int i = 59; i > 0; i--) {

			if (S->stageinfo[i][j].n2 == -304) { // �Ʒ��� ����ü�� ���
				if (S->stageinfo[i + 1][j].isSolid != 1) { // �浹������ ���ٸ�

					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // ������ ĭ�� ������� �ǵ�����
					S->stageinfo[i][j].n4 = 0;

					S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; // n2�� �ӽ�����
					S->stageinfo[i + 1][j].n2 = -304; // �Ʒ��� ĭ�� ����ü��
					if (isCharacterThere(j, i + 1) == 1) { // ���� �̵����� �� �÷��̾ �ű⿡ ������)
						clear--;
					}
					if (S->stageinfo[i + 1][j].n4 == -1) { // ���� �̵����� �� �÷��̾ �ű⿡ ������)
						S->stageinfo[i + 1][j].n4 = 0; // �� ���ְ� �� �����Ͱ� ����ȿ��
						play_effect_sound("C:\\sounds\\star.wav");
						clear++;
					}
				}
				else { // �浹������ ������
					S->stageinfo[i][j].n2 = S->stageinfo[i][j].n4; // �Ҹ�
					S->stageinfo[i][j].n4 = 0;
				}

			}

		}

	}
}


void shooting(Stage* S) { // 'stageinfo[y][x].n3 ��ǥ�� �߻�ü ������ �ִ� ������ �����ϰ�' 



	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 40; j++) {
			if (S->stageinfo[i][j].n2 == 10 || S->stageinfo[i][j].n2 == 17) { // �����̸�

				if (S->stageinfo[i][j].mod == 1 && S->stageinfo[i][j + 1].isSolid == 0) { // ���������� ��� �����Ҷ�
					S->stageinfo[i][j + 1].n4 = S->stageinfo[i][j + 1].n2; // n2�� �ӽ�����
					S->stageinfo[i][j + 1].n2 = -301; // �����ʿ� ����ü ����
				}
				if (S->stageinfo[i][j].mod == 2 && S->stageinfo[i][j - 1].isSolid == 0) { // �������� ��� �����Ҷ�
					S->stageinfo[i][j - 1].n4 = S->stageinfo[i][j - 1].n2; // n2�� �ӽ�����
					S->stageinfo[i][j - 1].n2 = -302; // ���ʿ� ����ü ����
				}
				if (S->stageinfo[i][j].mod == 3 && S->stageinfo[i - 1][j].isSolid == 0) { // �������� ��� �����Ҷ�
					S->stageinfo[i - 1][j].n4 = S->stageinfo[i - 1][j].n2; // n2�� �ӽ�����
					S->stageinfo[i - 1][j].n2 = -303; // ���ʿ� ����ü ����
				}
				if (S->stageinfo[i][j].mod == 4 && S->stageinfo[i + 1][j].isSolid == 0) { // �Ʒ������� ��� �����Ҷ�
					S->stageinfo[i + 1][j].n4 = S->stageinfo[i + 1][j].n2; // n2�� �ӽ�����
					S->stageinfo[i + 1][j].n2 = -304; // �Ʒ��ʿ� ����ü ����
				}

			}
		}
	}
}



//---------------------------------------------------------------------- ����
void to_jump(Stage* S) {

	if (control_gravity == 1)
	{
		if (jump_height > 0) { // �ö󰡾� �� ���̰� �����ִ� ��� ( ���� �� )
			move_character(S, cur_x, cur_y - 1); // ĳ���͸� 1ĭ �÷��ְ�

			if (right == 1 && jump_height % 2 == 0) move_character(S, cur_x + 1, cur_y); // ������ �����ϰ�� ���������ε� 1ĭ
			if (left == 1 && jump_height % 2 == 0) move_character(S, cur_x - 1, cur_y); // ���� �����ϰ�� �������ε� 1ĭ

			jump_height--; // 1ĭ �ö����� �ö󰡾� �� ���� 1ĭ ���ҽ�Ű��
			jump_and_falling++;

		}
		else if (jump_and_falling > 0 && isair(S)) { // ���� �ְ� ���� ���� �Ŀ��� ������ �����̶��(�߶��ϴ� ��Ȳ�̶��)
			// ó�� ���� ���⿡ ���缭 ����/���������� �̵�
			if (right == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x + 1, cur_y);
			if (left == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x - 1, cur_y);
			jump_and_falling--;
		}
	}

	if (control_gravity == 2)
	{
		if (jump_height > 0) { // �ö󰡾� �� ���̰� �����ִ� ��� ( ���� �� )
			move_character(S, cur_x + 1, cur_y); // ĳ���͸� 1ĭ �÷��ְ�

			if (right == 1 && jump_height % 2 == 0) move_character(S, cur_x, cur_y - 1); // ������ �����ϰ�� ���������ε� 1ĭ
			if (left == 1 && jump_height % 2 == 0) move_character(S, cur_x, cur_y + 1); // ���� �����ϰ�� �������ε� 1ĭ

			jump_height--; // 1ĭ �ö����� �ö󰡾� �� ���� 1ĭ ���ҽ�Ű��
			jump_and_falling++;

		}
		else if (jump_and_falling > 0 && isair(S)) { // ���� �ְ� ���� ���� �Ŀ��� ������ �����̶��(�߶��ϴ� ��Ȳ�̶��)
			// ó�� ���� ���⿡ ���缭 ����/���������� �̵�
			if (right == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x, cur_y - 1);
			if (left == 1 && jump_and_falling % 2 == 0) move_character(S, cur_x, cur_y + 1);
			jump_and_falling--;
		}
	}

}

void print_jump_gauge()
{
	int pos_x_to_print_jump_gauge = 25; // ���������� ��ġ ����
	int pos_y_to_print_jump_gauge = 4;
	for (int i = 0; i < 10; i += 2)//�������� ���Ӱ� �׸��� �� ������ �ٿ� �ִ� �� �� ����
	{
		setCursorPosition(2 * pos_x_to_print_jump_gauge + i, pos_y_to_print_jump_gauge);
		printf("  ");
	}
	for (int i = 0; i < jump_height; i += 2)
	{
		// ���� ���� (1~5ĭ�� �ٸ� �� ����)
		int colorNum;
		if (i < 2)
			colorNum = 7; // ���
		else if (i < 4)
			colorNum = 14; // ���� ���
		else if (i < 6)
			colorNum = 6; // ���� ���
		else if (i < 8)
			colorNum = 12; // ���� ����
		else
			colorNum = 4; // ���� ����

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);

		setCursorPosition(2 * pos_x_to_print_jump_gauge + i, pos_y_to_print_jump_gauge);
		printf("��");
	}

	// �⺻ ���� ���� (���)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void print_jump_direction() //������ ȭ�鿡 ���
{
	if (control_gravity == 1)
	{
		if (right == 1)
		{
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("��");
		}
		if (left == 1)
		{
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("��");
		}

		if (left == 0 && right == 0)
		{
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("��");
		}
	}

	if (control_gravity == 2)
	{
		if (right == 1)
		{
			setCursorPosition(2 * (cur_x + 2), cur_y);
			printf("��");
		}
		if (left == 1)
		{
			setCursorPosition(2 * (cur_x + 2), cur_y);
			printf("��");
		}

		if (left == 0 && right == 0)
		{
			setCursorPosition(2 * (cur_x + 2), cur_y);
			printf("��");
		}
	}
}

void set_jump_gauge(inter* M, Stage S)//�����̽��ٸ� ��� ������ ���� �÷��̾ �������� ���� ������ ������ �� �ְ� ���ִ� �Լ�
{
	int add_gauge = 2; //�������� �� 5ĭ���� �̷���� �ֽ��ϴ�. ������ �� ĭ �� �� ĭ�� �߰��� �ö󰩴ϴ�
	int update_print_jump_gauge_timing = 0;//����Ű�� �Է� �޾��� �� ���� �������� �ٷιٷ� �ݿ��ϱ� ���ؼ��� Ű���� �Է��� ��÷� �޾ƾ��մϴ�.
	// ������ ȭ�鿡 ��� �� ���� �������� ���� ���� ������ ������ �ٷ� �ٷ� �����ϸ� ������ �Ұ��� �� ������ ������ ���ŵǱ� ������ �ð� ���� �ΰ� ������ �ʿ��մϴ�.  
	// �׷��Ƿ� ����Ű�� ��÷� �Է� �޴� ��Ȳ���� ������ ������ ������ Ư�� Ÿ�̹��� ���� �� ����� �����Դϴ�.

	jump_height = 0;  // ���� ����
	jump_and_falling = 0; // �������� �ְ� ���̱��� �� �� �ٽ� �������� ��Ȳ�� ����� ����

	draw_ready_to_jump_character(&S, cur_x, cur_y);
	while (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		update_print_jump_gauge_timing += 1;
		shootrate++;
		printshootrate();

		if (control_gravity == 1)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)// �����ʹ���Ű�� ������ right�� 1�� ����
			{
				right = 1; left = 0;
				print_jump_direction();//�÷��̾ ������ ������ ȭ�鿡 �������(���� ������ �ؿ� ���)
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)// ���ʹ���Ű ������ left�� 1�� ����
			{
				right = 0; left = 1;
				print_jump_direction();//�÷��̾ ������ ������ ȭ�鿡 �������(���� ������ �ؿ� ���)
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000)// ���� ����Ű�� ��� �Ѵ� 0����
			{
				right = 0; left = 0;
				print_jump_direction();//�÷��̾ ������ ������ ȭ�鿡 �������(���� ������ �ؿ� ���)
			}
		}

		if (control_gravity == 2)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)// ���ʹ���Ű�� ������ right�� 1�� ����
			{
				right = 1; left = 0;
				print_jump_direction();//�÷��̾ ������ ������ ȭ�鿡 �������(���� ������ �ؿ� ���)
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)// �Ʒ�����Ű ������ left�� 1�� ����
			{
				right = 0; left = 1;
				print_jump_direction();//�÷��̾ ������ ������ ȭ�鿡 �������(���� ������ �ؿ� ���)
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)// ������ ����Ű�� ��� �Ѵ� 0����
			{
				right = 0; left = 0;
				print_jump_direction();//�÷��̾ ������ ������ ȭ�鿡 �������(���� ������ �ؿ� ���)
			}
		}

		if (update_print_jump_gauge_timing % 13 == 0)//0.3�ʸ��� �������� ����  
		{
			if (jump_height >= 10) add_gauge = -2;//�������� �� �� ��Ȳ������ �����̽��ٸ� ������ �ٽ� �پ��� �ϱ� ���� jump_height�� ���ϴ� ���� -�� ����
			if (jump_height <= 0) add_gauge = 2;// �ٽ� �������� 0���� �������� �������� �ø��� ���� jump_height ���ϴ� ���� +�� ����
			jump_height += add_gauge;
			print_jump_gauge();//������ �� ��Ȳ�� ȭ�鿡 ���
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
			draw_ready_to_jump_character(&S, cur_x, cur_y); //������ ĭ�� ������ ĳ�� ��� �ٽ� �׸���
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
//---------------------------------------------------------------------- Ű �Է�

void keybord_input(inter* M, Stage* S) {

	// ----------------------------------------------- ĳ���� ����(����Ű, �����̽���)

	// �����̽��ٰ� ���ȴ��� Ȯ��
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (isair(S) != 1) {
			set_jump_gauge(M, *S); // ���� ���� ����
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && isair(S) != 1) {

		move_character(S, cur_x - 1, cur_y); // �������� �̵�
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && isair(S) != 1) {

		move_character(S, cur_x + 1, cur_y); // ���������� �̵�
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		move_character(S, cur_x, cur_y - 1); // �������� �̵�
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		move_character(S, cur_x, cur_y + 1); // �Ʒ������� �̵�
	}


	// ----------------------------------------------- �������̽� ����

	// ����Ű �Է� Ȯ�� (Ű���� �������̽� ����)


	if (GetAsyncKeyState(0x57) & 0x8000) // W, ���� �̵�
	{
		findTextlineSelection(*S, TextMatrix, &x1, &y1);

		if (y1 > 0) { // ������ �Ǳ� �������� y��ǥ ����
			y1--;
			TextMatrix[y1 + 1][x1] = 0; // ���� ��ǥ�� 0����
			TextMatrix[y1][x1] = 1; // �� ��ǥ�� 1��
		}
		indicateTextline(*S, TextMatrix);
		Sleep(40);

	}
	if (GetAsyncKeyState(0x53) & 0x8000) // S, �Ʒ��� �̵�
	{
		findTextlineSelection(*S, TextMatrix, &x1, &y1);


		if (y1 < S->NumofLines - 1) { // ���� �ʰ� �������� y��ǥ ����
			y1++;
			TextMatrix[y1 - 1][x1] = 0; // ���� ��ǥ�� 0����
			TextMatrix[y1][x1] = 1; // �� ��ǥ�� 1��
		}
		indicateTextline(*S, TextMatrix);
		Sleep(40);
	}

	if (GetAsyncKeyState(0x52) & 0x8000) // R, �������� �����
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
		set_character(S, start_arr[c_stage][0], start_arr[c_stage][1]); // ĳ���� ��ġ ����


		if (c_stage == 2) { // 3�������� ����


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
			cur2_x = 30, cur2_y = 68; //ĳ����2�� '��'�� ��ǥ
			textcolor(12); // ������
			setCursorPosition(2 * cur_x, cur_y - 2);
			printf("��");
			setCursorPosition(2 * cur_x, cur_y - 1);
			printf("��");
			setCursorPosition(2 * cur_x, cur_y);
			printf("��");
			textcolor(15); // �ٽ� �Ͼ������

			textcolor(9); // �Ķ���
			setCursorPosition(2 * cur2_x, cur2_y - 2);
			printf("��");
			setCursorPosition(2 * cur2_x, cur2_y - 1);
			printf("��");
			setCursorPosition(2 * cur2_x, cur2_y);
			printf("��");
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

	if (GetAsyncKeyState(0x31) & 0x8000) // 1�� Ű����� ��ü - STOP
	{

		if (currentKeywords[0] != 0) { // Ű���尡 ��������� �۵����� ����

			play_effect_sound("C:\\sounds\\keyword_change.wav");

			if (S->Textlines[y1].element == 8) { // Platform�̸�

				for (int i = 0; i < 60; i++) { // PASS ����
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 11) { // �Ķ��� ����� �� �������
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // ������ ����� �� �������
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}

				isfalling = 0; // FALL ����
				ispush = 0; // push ����
			}
			if (S->Textlines[y1].element == -1) { // Star��
				isStarfalling = 0; // FALL ����
			}

			// MACHINE��
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = 0;
			}

			S->Textlines[y1].keyword = currentKeywords[0]; // ���� ���������� Ű���� ��ü
			Sleep(40);
		}


		indicateTextline(*S, TextMatrix);

	}
	if (GetAsyncKeyState(0x32) & 0x8000) // 2�� Ű����� ��ü - PASS
	{

		if (currentKeywords[1] != 0) {

			play_effect_sound("C:\\sounds\\keyword_change.wav");
			if (S->Textlines[y1].element == 8) { // Platform�̸�
				isfalling = 0; // FALL ����
				ispush = 0; // PUSH ����
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {
						// isSolid�� 0���� ����� �浹 ����
						if (S->stageinfo[i][j].n3 == 11) { // �Ķ��� ����� �� �������
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // ������ ����� �� �������
							S->stageinfo[i][j].isSolid = 0;
						}
					}
				}
			}
			if (S->Textlines[y1].element == -1) { // Star��
				isStarfalling = 0; // FALL ����
			}

			// MACHINE��
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = 0;
			}

			S->Textlines[y1].keyword = currentKeywords[1];
			Sleep(40);
		}
		indicateTextline(*S, TextMatrix);
	}
	if (GetAsyncKeyState(0x33) & 0x8000) // 3�� Ű����(FALL)�� ��ü
	{

		// ����

		if (currentKeywords[2] != 0) {

			play_effect_sound("C:\\sounds\\keyword_change.wav");

			// ����
			if (S->Textlines[y1].element == 8) { // Platform�̸�

				ispush = 0; // PUSH ����
				isfalling = 1;
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {
						// isSolid�� 0���� ����� �浹 ����
						if (S->stageinfo[i][j].n3 == 11) {
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) {
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}
			}

			// STAR��
			if (S->Textlines[y1].element == -1) { // Star�̸�
				isStarfalling = 1; //FALL
			}

			// MACHINE��
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = 1;
			}


			S->Textlines[y1].keyword = currentKeywords[2];
			Sleep(40);
		}

		indicateTextline(*S, TextMatrix);

	}
	if (GetAsyncKeyState(0x34) & 0x8000) // 4�� Ű����(SWITCH)�� ��ü
	{
		if (currentKeywords[3] != 0) {

			play_effect_sound("C:\\sounds\\keyword_change.wav");

			// ����

			if (S->Textlines[y1].element == 8) { // Platform�̸�
				isfalling = 0; // FALL ����
				ispush = 0; // PUSH ����
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 11) { // �Ķ��� ����� �� �������
							S->stageinfo[i][j].n2 = -11;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -11) { // �Ķ��� �� �����....
							S->stageinfo[i][j].n2 = 11;
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // ������ ����� �� �������
							S->stageinfo[i][j].n2 = -12;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -12) { // ������ �� �����....
							S->stageinfo[i][j].n2 = 12;
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}
			}

			// ������

			if (S->Textlines[y1].element == 8) { // ����(����)�� ���
				isfalling = 0; // FALL ����
				ispush = 0; // PUSH ����
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 14) { // �Ķ��� ���ø� �Ķ��� �� ���÷�
							S->stageinfo[i][j].n2 = -14;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -14) { // �Ķ��� �� ���ø�....
							S->stageinfo[i][j].n2 = 14;
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 15) { // ������ ���ø� ������ �� ���÷�
							S->stageinfo[i][j].n2 = -15;
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == -15) { // ������ �� ���ø�....
							S->stageinfo[i][j].n2 = 15;
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}
			}

			// STAR

			if (S->Textlines[y1].element == -1) { // STAR�̸�
				isStarfalling = 0; // FALL ����
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == -1) { // �� -> ��
							S->stageinfo[i][j].n2 = -2;
						}
						else if (S->stageinfo[i][j].n3 == -2) { // �� -> ��
							S->stageinfo[i][j].n2 = -1;
						}
					}
				}
			}

			//CHARACTER

			if (S->Textlines[y1].element == 7) { // ĳ������ ���

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
					textcolor(9); // �Ķ���
					setCursorPosition(2 * cur_x, cur_y - 2);
					printf("��");
					setCursorPosition(2 * cur_x, cur_y - 1);
					printf("��");
					setCursorPosition(2 * cur_x, cur_y);
					printf("��");
					textcolor(15); // �ٽ� �Ͼ������

					textcolor(12); // ������
					setCursorPosition(2 * cur2_x, cur2_y - 2);
					printf("��");
					setCursorPosition(2 * cur2_x, cur2_y - 1);
					printf("��");
					setCursorPosition(2 * cur2_x, cur2_y);
					printf("��");
					textcolor(15); // �ٽ� �Ͼ������

					dual = 2;
				}
				else {
					textcolor(12); // ������
					setCursorPosition(2 * cur_x, cur_y - 2);
					printf("��");
					setCursorPosition(2 * cur_x, cur_y - 1);
					printf("��");
					setCursorPosition(2 * cur_x, cur_y);
					printf("��");
					textcolor(15); // �ٽ� �Ͼ������

					textcolor(9); // �Ķ���
					setCursorPosition(2 * cur2_x, cur2_y - 2);
					printf("��");
					setCursorPosition(2 * cur2_x, cur2_y - 1);
					printf("��");
					setCursorPosition(2 * cur2_x, cur2_y);
					printf("��");
					textcolor(15); // �ٽ� �Ͼ������

					dual = 1;
				}
			}

			//MACHINE

			if (S->Textlines[y1].element == 10) { // machine�̸�
				Misfalling = 0;
				Mispush = 0;
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 10) { // �ӽ��� ������
							if (S->stageinfo[i][j].mod == 1) { // ������
								S->stageinfo[i][j].mod = 4;
							}
							else if (S->stageinfo[i][j].mod == 2) { // ����
								S->stageinfo[i][j].mod = 3;
							}
							else if (S->stageinfo[i][j].mod == 3) { // ����
								S->stageinfo[i][j].mod = 1;
							}
							else if (S->stageinfo[i][j].mod == 4) { // �Ʒ���
								S->stageinfo[i][j].mod = 2;
							}

						}
					}
				}
			}

			drawStage(*S, 0, 10);

			S->Textlines[y1].keyword = currentKeywords[3]; // SWITCH�� ����
			indicateTextline(*S, TextMatrix);


			Sleep(40);
		}
	}
	if (GetAsyncKeyState(0x35) & 0x8000) // 5�� Ű����(FLOAT)�� ��ü
	{

		// ����

		if (currentKeywords[4] != 0) {
			play_effect_sound("C:\\sounds\\keyword_change.wav");
			// ����
			if (S->Textlines[y1].element == 8) { // Platform�̸�
				isfalling = -1;
				ispush = 0;
				for (int i = 0; i < 60; i++) {
					for (int j = 0; j < 40; j++) {
						// isSolid�� 0���� ����� �浹 ����
						if (S->stageinfo[i][j].n3 == 11) { // �Ķ��� ����� �� �������
							S->stageinfo[i][j].isSolid = 0;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // ������ ����� �� �������
							S->stageinfo[i][j].isSolid = 0;
						}
					}
				}
			}

			// STAR��
			if (S->Textlines[y1].element == -1) { // Star�̸�
				isStarfalling = -1; //FALL
			}

			// MACHINE��
			if (S->Textlines[y1].element == 10) {
				Mispush = 0;
				Misfalling = -1;
			}


			S->Textlines[y1].keyword = currentKeywords[4];
			Sleep(40);
		}

		indicateTextline(*S, TextMatrix);

	}
	if (GetAsyncKeyState(0x36) & 0x8000) // 6�� Ű����(PUSH)�� ��ü
	{



		if (currentKeywords[5] != 0) {
			play_effect_sound("C:\\sounds\\keyword_change.wav");
			// ����
			if (S->Textlines[y1].element == 8) { // Platform�̸�
				for (int i = 0; i < 60; i++) { // PASS ����
					for (int j = 0; j < 40; j++) {

						if (S->stageinfo[i][j].n3 == 11) { // �Ķ��� ����� �� �������
							S->stageinfo[i][j].isSolid = 1;
						}
						else if (S->stageinfo[i][j].n3 == 12) { // ������ ����� �� �������
							S->stageinfo[i][j].isSolid = 1;
						}
					}
				}

				ispush = 1;

				isfalling = 0; // FALL ����
			}

			// STAR��
			if (S->Textlines[y1].element == -1) { // Star�̸�
				isStarfalling = 0;
			}

			// MACHINE��
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
	if (GetAsyncKeyState(0x41) & 0x8000) // A, �������� �̵�
	{
	findTextlineSelection(*S, TextMatrix, &x1, &y1);

	if (x1 == 1) { // x��ǥ �ٲ�
	x1 = 0;
	TextMatrix[y1][x1 + 1] = 0; // ���� ��ǥ�� 0����
	TextMatrix[y1][x1] = 1; // �� ��ǥ�� 1��
	}


	}
	if (GetAsyncKeyState(0x44) & 0x8000) // D, ���������� �̵�
	{

	findTextlineSelection(*S, TextMatrix, &x1, &y1);

	if (x1 == 0) { // x��ǥ �ٲ�
	x1 = 1;
	TextMatrix[y1][x1 - 1] = 0; // ���� ��ǥ�� 0����
	TextMatrix[y1][x1] = 1; // �� ��ǥ�� 1��
	}
	else {

	}
	}



	if (GetAsyncKeyState(0x45) & 0x8000) // E, Ű���� ��ü
	{

	if (x1 == 0) {
	}
	else {
	magic(S);
	}
	}

	if (GetAsyncKeyState(0x51) & 0x8000) // Q, Ű���� ��ü
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


//---------------------------------------------------------------------- �ý���

void itemAcquire(Stage* S, int x, int y) { // Ű����, ������ �� ȹ��
	y = y - 10; // �÷��̾� ��ġ�� ��ǥ�� ��ġ��Ű��
	if (control_gravity == 1) { // �߷��� �Ʒ����� ��
		for (int i = 0; i <= 2; i++) { // ��,����,�Ӹ� �� ���� üũ
			if (S->stageinfo[y - i][x].n2 == -101) { // PASS
				addkeyword(1, -101);
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -102) { // FALL
				addkeyword(2, -102);
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -103) { // SWITCH
				addkeyword(3, -103);
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -104) { // FLOAT
				addkeyword(4, -104);
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -105) { // PUSH
				addkeyword(5, -105);
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -1) { // Star
				clear++;
				S->stageinfo[y - i][x].n2 = 0; // �������� ������
				play_effect_sound("C:\\sounds\\star.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -201) { // �߷��� ��������
				clear_character(S, cur_x, cur_y);
				control_gravity = 2;
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y - i][x].n2 == -3) { // bonus
				c_bonus += 1;
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}

		}
	}
	else if (control_gravity == 2) { // �߷��� ������ ��
		for (int i = 0; i <= 2; i++) { // ��,����,�Ӹ� �� ���� üũ
			if (S->stageinfo[y][x + i].n2 == -103) { // SWITCH
				addkeyword(3, -103);
				S->stageinfo[y][x + i].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y][x + i].n2 == -102) { // FALL
				addkeyword(2, -102);
				S->stageinfo[y][x + i].n2 = 0; // �������� �����ְ�
				indicateTextline(*S, TextMatrix); // �ؽ�Ʈ �ʱ�ȭ
				play_effect_sound("C:\\sounds\\item_aquired.wav");
			}
			if (S->stageinfo[y][x + i].n2 == -1) { // Star
				play_effect_sound("C:\\sounds\\star.wav");
				clear++;
				S->stageinfo[y][x + i].n2 = 0; // �������� ������
			}
			if (S->stageinfo[y][x + i].n2 == -201) { // �߷��� ��������
				play_effect_sound("C:\\sounds\\item_aquired.wav");
				control_gravity = 2;
				S->stageinfo[y][x + i].n2 = 0; // �������� �����ְ�
			}
			if (S->stageinfo[y][x + i].n2 == -3) { // bonus
				play_effect_sound("C:\\sounds\\item_aquired.wav");
				c_bonus += 1;
				S->stageinfo[y - i][x].n2 = 0; // �������� �����ְ�
			}

		}
	}

	
	keyWordindicator();
	indicateItems();

}

void stageclear(inter* M) { //Ŭ���� �� ���� �Ѿ�� �Լ�
	
	
	setCursorPosition(25, 30);
	textcolor(3);
	printf("������������������������������������������������������������");
	for (int i = 1; i < 15; i++) {
		Sleep(30);
		setCursorPosition(25, 30 + i);
		printf("��                            ��");
		setCursorPosition(25, 31 + i);
		printf("������������������������������������������������������������");
	}
	/*
	setCursorPosition(25, 45);
	printf("������������������������������������������������������������");
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
	printf("��");
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


	//���� �������� �׸���
	drawStage(M[c_stage].TextInterface, 0, 0);
	drawStage(M[c_stage].ShopInterface, 40, 10);
	drawStage(M[c_stage].TextStored, 40, 0);
	drawStage(M[c_stage].S, 0, 10);
	set_character(&M[c_stage].S, start_arr[c_stage][0], start_arr[c_stage][1]); //�������� 2 ���۽� ���� ��ǥ
	indicateItems();
	indicateTextline(M[c_stage].S, TextMatrix);
	seachmoving(&M[c_stage].S, 0, 10);
	//������ �ʱ�ȭ
	for (int i = 0; i < 8; i++) {
		currentKeywords[i] = keywords[1][i];
	}
	c_score = 0;
	c_time = 0;
	
}

void death_effect(Stage* S) {
	// cur_x, cur_y ����� ���

	clear_character(S, cur_x, cur_y);


	const char* explosion_frames[] = {
		" * ",
		"* *",
		" * ",
	};
	int num_frames = 3;

	for (int i = 0; i < num_frames; i++) {
		// ���� ������ ��� (���η� �� �ٸ� ǥ��)
		setCursorPosition(2 * cur_x, cur_y - 1); // cur_y�� �������� �߾� ���
		printf("%s", explosion_frames[i]);
		fflush(stdout); // ���� �÷���

		Sleep(200);

		// ���� ������ �����
		setCursorPosition(2 * cur_x, cur_y - 1);
		printf("   "); // �� �� ����
		fflush(stdout);
	}

}



void gameover(inter* M, Stage* S) { //���� �� �ٽý��� �Լ�
	play_effect_sound("C:\\sounds\\deth.wav");
	textcolor(12);
	death_effect(S);
	textcolor(15);
	Sleep(100);
	setCursorPosition(25, 30);
	printf("������������������������������������������������������������");
	for (int i = 1; i < 15; i++) {
		setCursorPosition(25, 30 + i);
		printf("��                            ��");
	}
	setCursorPosition(25, 45);
	printf("������������������������������������������������������������");
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
	set_character(&M->S, start_arr[c_stage][0], start_arr[c_stage][1]); // ĳ���� ��ġ ����

	if (c_stage == 2) { // 3�������� ����


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
		cur2_x = 30, cur2_y = 68; //ĳ����2�� '��'�� ��ǥ
		textcolor(12); // ������
		setCursorPosition(2 * cur_x, cur_y - 2);
		printf("��");
		setCursorPosition(2 * cur_x, cur_y - 1);
		printf("��");
		setCursorPosition(2 * cur_x, cur_y);
		printf("��");
		textcolor(15); // �ٽ� �Ͼ������

		textcolor(9); // �Ķ���
		setCursorPosition(2 * cur2_x, cur2_y - 2);
		printf("��");
		setCursorPosition(2 * cur2_x, cur2_y - 1);
		printf("��");
		setCursorPosition(2 * cur2_x, cur2_y);
		printf("��");
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

	//�ӽ÷� pass ������
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 40; j++) {
			// isSolid�� 0���� ����� �浹 ����
			if (M->S.stageinfo[i][j].n3 == 11) { // �Ķ��� ����� �� �������
				M->S.stageinfo[i][j].isSolid = 1;
			}
			else if (M->S.stageinfo[i][j].n3 == 12) { // ������ ����� �� �������
				M->S.stageinfo[i][j].isSolid = 1;
			}
		}
	}


}





