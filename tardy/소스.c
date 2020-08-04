#define _CRT_NONSTDC_NO_WARNINGS //��ǥ�� �Լ��� ��������� ��������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <direct.h>
#include <Windows.h> 
#include <io.h> // _creat�Լ��� �������� ������� + access�Լ�
#include <sys/types.h>  // �پ��� ������ ����
#include <sys/stat.h> // ��������
#pragma warning(disable:4996)

FILE* fp = NULL;
int ctrl = 0;
int color = 11;
char csv[99] = { ".csv" };


//����ü
typedef struct {
	int cnt;
	char YN;
	char name[99];
	char Student_ID[99];

}LIST;
//����ü

//intro
void intro(void)
{
	system("cls");
	printf("������������������ Late ������������������\n");
	printf("�������� �� ���α׷��� ������ �����ϴ� ���α׷��Դϴ�. ��������\n");
	printf("��������������� ������: �ֹα� ����������������\n");
	printf("------------------------------------------------------------------------\n\n");
}
//intro

//exit
void exitprint(void)
{
	printf("������������������ Late �����������������\n");
	printf("��������� �� ���α׷��� ������ּż� �����մϴ�. ���������\n");
	printf("��������������� ������: �ֹα� ���������������\n");
	printf("------------------------------------------------------------------------\n\n");
}
//exit

//�л��̸������Լ�
void change(char oldname[99], char newname[99])
{
	strcat(oldname, csv);
	strcat(newname, csv);

	int result = rename(oldname, newname);
	fopen_s(&fp, "�л����.csv", "a+");

	if (result == 0)
	{
		printf("�̸� ���� ����! \n");
		fprintf(fp, "\n%s", newname);
		getch();
	}
	else if (result == -1)
	{
		perror("�̸� ���� ����.. \n");
		getch();
	}
	return;
}
//�л��̸������Լ�

//�߰��Լ�
void add(int cnt)
{
	LIST ADD;


	if (cnt == 1)
	{
		int error;

		printf("�߰��Ͻ� �л��� �̸��� �Է��ϼ��� : ");
		scanf_s("%s", &ADD.name, 30);
		strcat(ADD.name, csv);

		printf("�߰��Ͻ� �л��� �й��� �Է��ϼ��� : ");
		scanf_s("%s", &ADD.Student_ID, 30);
		strcat(ADD.Student_ID, csv);
		fopen_s(&fp, "�л����.csv", "a+");

		error = _creat(ADD.name, _S_IWRITE); //�������
		if (error == -1)
		{
			perror("ERROR!!\n");
		}
		else
		{
			printf("'%s' �л��� �߰��Ǿ����ϴ�.\n", ADD.name);
			printf("   �ƹ�Ű�� �����ּ���!\n");
			fprintf(fp, "\n%s", ADD.name);
			_close(error);
			getch();
			fclose(fp);
		}
	}

	else if (cnt == 2)
	{
		printf("������ �л��� �̸��� �Է����ּ��� : ");
		scanf_s("%s", &ADD.name, 30);
		strcat(ADD.name, csv);
		int result = access(ADD.name, 0);

		if (result == -1)
		{
			perror("�ش��ϴ� �л��� �����ϴ�!!\n");
			getch();
			return;
		}
		else if (result == 0)
		{
			fopen_s(&fp, ADD.name, "a+");
			char tardy[99] = { NULL };
			printf("������ �⵵ ��¥ �ð��� �Է����ּ��� (��) 2020/2/17 ): ");
			scanf_s("%s", tardy, 30);

			fprintf(fp, "\n%s", tardy);
			printf(" '%s' ������ �߰��Ǿ����ϴ�.\n", tardy);
			printf("�ƹ�Ű�� �����ּ���!\n");

			getch();
			fclose(fp);
		}
	}

	else if (cnt == 3)
	{
		printf("�������� ���ư��ϴ�.\n");
		getch();
		return;
	}
	else if (cnt < 1 || cnt>3)
	{
		printf("�� �� ���̽��ϴ�.\n");
		getch();
		return;
	}

}
//�߰��Լ�

//�˻��Լ�
void search(void)
{
	LIST SCH;

	char singerlist[99] = { "�л����.csv" };

	printf("�˻��Ͻ� �л��� �Է����ּ��� : ");
	scanf_s(" %s", &SCH.name, 30);
	char* ptr = strstr(singerlist, SCH.name);
	fopen_s(&fp, singerlist, "r");

	if (fp != NULL)
	{
		printf("�ش� �л� ����� �ҷ�������.. \n");
		while ((fgets(singerlist, sizeof(singerlist), fp)) != NULL)
		{
			char* ptr = strstr(singerlist, SCH.name);

			if (ptr != NULL) {
				printf("%s", ptr);   // �˻��� ���ڿ� ���
			}
		}
		fclose(fp);
	}
	else if (fp == NULL)
	{
		printf("�ش��ϴ� �л��� �����ϴ�.\n");
		printf("�߰��Ͻðڽ��ϱ�?[Y/N]:");
		scanf_s("%c", &SCH.YN, 30);
		while (getchar() != '\n');

		if (SCH.YN == 'Y' || SCH.YN == 'y')
		{
			system("cls");
			printf("================================= �޴� =================================\n\n");
			printf("���������������  1. �л� �߰�  ���������������\n");
			printf("���������������  2. ���� �߰�  ���������������\n");
			printf("���������������   3. ��������  ���������������\n");
			printf("========================================================================\n");
			printf("��� �Ͻ� ����� �����ϼ���: ");
			scanf_s("%d", &SCH.cnt);
			while (getchar() != '\n');

			add(SCH.cnt);
		}

		else if (SCH.YN == 'N' || SCH.YN == 'n')
		{
			printf("�߰����� �ʾҽ��ϴ�.\n");
			system("pause");
			return;
		}
		else
		{
			printf("�� �� �����Ͽ����ϴ�.\n");
		}
		system("pause");
		return;
	}
	getch();
}
//�˻��Լ�

//�����Լ�
void rmv(int cnt)
{
	LIST RMV;
	char str[1000][256] = { 0, };
	int line = 0;
	int i, n;

	strcat(RMV.name, csv);
	char singerlist[99] = { "�л����.csv" };

	int result = strcmp(singerlist, RMV.name);
	fopen_s(&fp, singerlist, "a+");


	if (cnt == 1)
	{
		printf("�����ϰ���� �л��� �Է��ϼ���:");
		scanf_s("%s", &RMV.name, 30);

		strcat(RMV.name, csv);
		int result = strcmp(singerlist, RMV.name);
		fopen_s(&fp, singerlist, "a+");

		while (1)
		{
			if (fgets(str[line], 256, fp) == NULL)
				break;
			line++;
		}
		fclose(fp);

		for (i = 0; i < line; i++)
		{
			printf("%d:%s", i + 1, str[i]);
		}
		printf("\n");
		printf("������ �л��� Ȯ�����ּ���:");
		scanf_s("%d", &n);
		while (getchar() != '\n');

		fopen_s(&fp, singerlist, "w");

		for (i = 0; i < line; i++)
		{
			if (n != (i + 1))
				fprintf(fp, "%s", str[i]);
		}
		fclose(fp);

		if (result == 0)
		{
			printf("������ �� �����ϴ�.\n");
			getch();
			return;
		}
		else if (_unlink(RMV.name)) {
			switch (errno) {
			case EACCES:
				fprintf(stderr, "�������� �ź� �Ǿ����ϴ�. %s\n", RMV.name); break;
			case ENOENT:
				fprintf(stderr, "�л��� ã�� �� �����ϴ�. %s\n", RMV.name); break;
			default:
				fprintf(stderr, "�˼����� �����Դϴ�.\n"); break;
			}
			getch();
		}
		else
		{
			printf("�����Ǿ����ϴ�. \n");
			getch();
		}
	}
	else if (cnt == 2)
	{
		RMV.YN = NULL;

		printf("�����ϰ���� �й��� �ش��ϴ� �л��� �Է����ּ��� :");
		scanf_s("%s", &RMV.name, 30);
		strcat(RMV.name, csv);

		fopen_s(&fp, RMV.name, "r");

		while (1)
		{
			if (fgets(str[line], 256, fp) == NULL)
				break;
			line++;
		}
		fclose(fp);

		for (i = 0; i < line; i++)
		{
			printf("%d:%s", i + 1, str[i]);
		}

		printf("\n");
		printf("�����ϰ���� ���� :");
		scanf_s("%d", &n);
		while (getchar() != '\n');

		fopen_s(&fp, RMV.name, "w");

		for (i = 0; i < line; i++)
		{
			if (n != (i + 1))
				fprintf(fp, "%s", str[i]);
		}
		fclose(fp);

		printf("�����Ǿ����ϴ�.\n ����� Ȯ���Ͻðڽ��ϱ�?[Y/N] : ");
		scanf_s("%c", &RMV.YN, 30);
		while (getchar() != '\n');

		if (RMV.YN == 'Y' || RMV.YN == 'y')
		{
			fopen_s(&fp, RMV.name, "r");

			line = 0;

			while (1)
			{
				if (fgets(str[line], 256, fp) == NULL)
					break;
				line++;
			}

			for (i = 0; i < line; i++)
			{
				printf("%d:%s", i + 1, str[i]);
			}

			fclose(fp);

			printf("\n");
			system("pause");
		}
		else if (RMV.YN == 'N' || RMV.YN == 'n')
		{
			printf("�������� ���ư��ϴ�.\n");
			getch();
			return;
		}
		else
		{
			printf("�� �� �Է��ϼ̽��ϴ�.\n");
			getch();
			return;
		}
		return;
	}
	else if (cnt == 3)
	{
		printf("�������� ���ư��ϴ�.\n");
		getch();
		return;
	}
	else if (cnt < 1 || cnt>3)
	{
		printf("�� �� ���̽��ϴ�.\n");
		getch();
		return;
	}
}
//�����Լ�

//�ҷ������Լ�
void call(cnt)
{
	LIST CALL;

	if (cnt == 1)
	{
		system("cls");
		strcpy((char*)CALL.name, "�л����.csv");
		fopen_s(&fp, CALL.name, "r");

		if (fp != NULL)
		{
			printf("�л� ����� �ҷ�������.. \n");
			while ((fgets(CALL.name, sizeof(CALL.name), fp)) != NULL)
			{
				printf("%s", CALL.name);
			}
			printf("\n\n");
			getch();
			fclose(fp);
		}
		else if (fp == NULL)
		{
			printf("�ҷ��� ����� �������� �ʽ��ϴ�. \n");
		}
		fclose(fp);
	}
	else if (cnt == 2)//���ϴ� ���� ���
	{

		system("cls");
		CALL.YN = NULL;

		printf("���ϴ� �л��� �Է��ϼ���: ");
		scanf_s("%s", &CALL.name, 30);
		strcat(CALL.name, csv); //����������� �ҷ��������ؼ��� .txt�� ���ԵǾ���ϴµ� �л��̸��� .txt�� �������ν� ����
		int result = access(CALL.name, 0);

		if (result == 0)
		{
			fopen_s(&fp, CALL.name, "a+");
			printf("�ش� �л��� ����Ƚ���� �ҷ�������.\n");
			while ((fgets(CALL.name, sizeof(CALL.name), fp)) != NULL)
			{
				printf("%s", CALL.name);
			}
			printf("\n");
			printf("�ش� �л��� ����Ƚ���� �߰��Ͻðڽ��ϱ�?[Y/N] \n");
			scanf_s("%c", &CALL.YN, 30);
			while (getchar() != '\n');

			if (CALL.YN == 'Y' || CALL.YN == 'y')
			{
				char input[256];
				printf("����Ƚ���� �Է����ּ���:");
				gets(input);
				fprintf(fp, "\n%s", input);
				printf("�߰��Ǿ����ϴ�. \n");
				system("pause"); //�ܼ�â ����
				fclose(fp);
			}
			else if (CALL.YN == 'N' || CALL.YN == 'n')
			{
				printf("�߰����� �ʾҽ��ϴ�.\n");
				system("pause");
				fclose(fp);
			}
			else
			{
				printf("�� �� �����Ͽ����ϴ�.\n");
				system("pause");
				fclose(fp);
			}
		}
		else if (result == -1)
		{
			CALL.YN = NULL;
			printf("�ش� �л��� �����ϴ�!\n");
			printf("�߰��Ͻðڽ��ϱ�?[Y/N]:");
			scanf_s("%c", &CALL.YN, 30);
			while (getchar() != '\n');

			if (CALL.YN == 'Y' || CALL.YN == 'y')
			{
				system("cls");
				printf("================================= �޴� =================================\n\n");
				printf("���������������  1. �л� �߰�  ���������������\n");
				printf("���������������   3. ��������  ���������������\n");
				printf("========================================================================\n");
				printf("���� ���� ����� �����ϼ���: ");
				scanf("%d", &CALL.cnt);
				while (getchar() != '\n');
				add(CALL.cnt);
			}
			else if (CALL.YN == 'N' || CALL.YN == 'n')
			{
				printf("�߰����� �ʾҽ��ϴ�.\n");
				system("pause");
				return;
			}
			else
			{
				printf("�� �� �����Ͽ����ϴ�.\n");
			}
			system("pause");
			return;
		}
		fclose(fp);
	}
	else if (cnt == 3)
	{
		intro();
		printf("�������� �̵��մϴ�.\n");
		system("pause");
		return;
	}
	else if (cnt < 1 || cnt>3)
	{
		intro();
		printf("�� �� �����ϼ̽��ϴ�.\n �������� ���ư��ϴ�.\n");
		system("pause");
		return;
	}
}
//�ҷ������Լ�

//��ɾ��Լ�
void command(void)
{
	LIST COM;

	ctrl = getch();

	if (ctrl == 15)//CTRL+O (�ҷ�����)
	{
		COM.cnt = 0;

		intro();
		printf("================================= �޴� =================================\n\n");
		printf("���������������  1. �л� ���  ���������������\n");
		printf("������������  2. �ش� �л��� ���� ���  ������������\n");
		printf("���������������   3. ��������  ���������������\n");
		printf("========================================================================\n");
		printf("���� ���� ����� �����ϼ���: ");
		scanf("%d", &COM.cnt);
		while (getchar() != '\n');

		call(COM.cnt);
	}
	else if (ctrl == 18)//ctrl+R (�����ϱ�)
	{
		intro();
		COM.cnt = 0;
		printf("================================= �޴� =================================\n\n");
		printf("���������������  1. �л� ����  ���������������\n");
		printf("���������������  2. ���� ����  ���������������\n");
		printf("���������������   3. ��������  ���������������\n");
		printf("========================================================================\n");
		printf("��� �Ͻ� ����� �����ϼ���: ");
		scanf_s("%d", &COM.cnt);
		while (getchar() != '\n');

		rmv(COM.cnt);
	}
	else if (ctrl == 1)//ctrl+A (�߰��ϱ�)
	{
		intro();
		printf("================================= �޴� =================================\n\n");
		printf("���������������  1. �л� �߰�  ���������������\n");
		printf("���������������  2. ���� �߰�  ���������������\n");
		printf("���������������   3. ��������  ���������������\n");
		printf("========================================================================\n");
		printf("��� �Ͻ� ����� �����ϼ���: ");
		scanf_s("%d", &COM.cnt);
		while (getchar() != '\n');

		add(COM.cnt);
	}
	else if (ctrl == 6)//ctrl+F(�˻��ϱ�)
	{
		intro();
		search();
	}
	else if (ctrl == 3)//ctrl+C(�����ϱ�)
	{
		char oldname[99] = { NULL };
		char newname[99] = { NULL };
		intro();
		printf("�л��� �̸��� �Է����ּ���: ");
		scanf_s("%s", &oldname, 30);
		printf("�����Ͻ� �̸��� �Է����ּ���: ");
		scanf_s("%s", &newname, 30);
		change(oldname, newname);
	}
	else if (ctrl == 27)
	{
		char answer = NULL;

		intro();
		printf("���� �����Ͻðڽ��ϱ�?[Y/N]: ");
		scanf_s(" %c", &answer, 1);
		while (getchar() != '\n');

		if (answer == 'Y' || answer == 'y')
		{
			printf("�����Ͽ����ϴ�.\n\n");
			exitprint();
			getch();
			exit(0);
		}

		else if (answer == 'N' || answer == 'n')
		{
			printf("�������� ���ư��ϴ�.\n");
			system("pause");
			return;
		}

		else
		{
			printf("�� �� �����̽��ϴ�.\n");
			getch();
			return;
		}
	}
}

//��ɾ��Լ�

//�����Լ�
int main(void)
{
	LIST MAIN;
	system("mode con cols=75 lines=35");
	int pass = 8431;
	int answer = 0;
	intro();
	printf("���������� �̿��Ͻ÷��� �н����带 �Է����ּ���. ����������\n");
	printf("�н����带 �Է����ּ��� : ");
	scanf_s("%d", &answer);

	if (answer != pass) {

		printf("�н����尡 Ʋ�Ƚ��ϴ�.");
	}

	else if (answer == pass) {
		while (1) {
			intro();
			printf("================================= �޴� =================================\n\n");
			printf("��������������  �߰��ϱ� : CTRL+A ��������������\n");
			printf("��������������  �����ϱ� : CTRL+R ��������������\n");
			printf("��������������  �˻��ϱ� : CTRL+F ��������������\n");
			printf("��������������  �����ϱ� : CTRL+C ��������������\n");
			printf("��������������  �ҷ����� : CTRL+O ��������������\n");
			printf("��������������   �����ϱ� : ESC  ���������������\n");
			printf("========================================================================\n");
			command();
		}
	}
}
//�����Լ�