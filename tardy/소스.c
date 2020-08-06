#define _CRT_NONSTDC_NO_WARNINGS //비표준 함수를 사용했을시 오류방지

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <direct.h>
#include <Windows.h> 
#include <io.h> // _creat함수를 쓰기위한 헤더파일 + access함수
#include <sys/types.h>  // 다양한 데이터 유형
#include <sys/stat.h> // 파일정보
#pragma warning(disable:4996)

FILE* fp = NULL;
int ctrl = 0;
int color = 11;
char csv[99] = { ".csv" };


//구조체
typedef struct {
	int cnt;
	char YN;
	char name[99];
	char Student_ID[99];

}LIST;
//구조체

//intro
void intro(void)
{
	system("cls");
	printf("□□□□□□□□□□□□□□□□□ Late □□□□□□□□□□□□□□□□□\n");
	printf("□□□□□□□ 이 프로그램은 지각을 관리하는 프로그램입니다. □□□□□□□\n");
	printf("□□□□□□□□□□□□□□ 제작자: 최민기 □□□□□□□□□□□□□□□\n");
	printf("------------------------------------------------------------------------\n\n");
}
//intro

//exit
void exitprint(void)
{
	printf("□□□□□□□□□□□□□□□□□ Late □□□□□□□□□□□□□□□□\n");
	printf("□□□□□□□□ 이 프로그램을 사용해주셔서 갑사합니다. □□□□□□□□\n");
	printf("□□□□□□□□□□□□□□ 제작자: 최민기 □□□□□□□□□□□□□□\n");
	printf("------------------------------------------------------------------------\n\n");
}
//exit

//학생이름수정함수
void change(char oldname[99], char newname[99])
{
	strcat(oldname, csv);
	strcat(newname, csv);

	int result = rename(oldname, newname);
	fopen_s(&fp, "학생목록.csv", "a+");

	if (result == 0)
	{
		printf("이름 수정 성공! \n");
		fprintf(fp, "\n%s", newname);
		getch();
	}
	else if (result == -1)
	{
		perror("이름 수정 실패.. \n");
		getch();
	}
	return;
}
//학생이름수정함수

//추가함수
void add(int cnt)
{
	LIST ADD;


	if (cnt == 1)
	{
		int error;

		printf("추가하실 학생의 이름을 입력하세요 : ");
		scanf_s("%s", &ADD.name, 30);
		strcat(ADD.name, csv);

		printf("추가하실 학생의 학번을 입력하세요 : ");
		scanf_s("%s", &ADD.Student_ID, 30);
		strcat(ADD.Student_ID, csv);
		fopen_s(&fp, "학생목록.csv", "a+");


		error = _creat(ADD.name, _S_IWRITE); //쓰기허용
		if (error == -1)
		{
			perror("ERROR!!\n");
		}
		else
		{
			printf("'%s' 학생이 추가되었습니다.\n", ADD.name);
			printf("   아무키나 눌러주세요!\n");
			fprintf(fp, "\n%s", ADD.name);
			_close(error);
			getch();
			fclose(fp);
		}
	}

	else if (cnt == 2)
	{
		printf("지각한 학생의 이름을 입력해주세요 : ");
		scanf_s("%s", &ADD.name, 30);
		strcat(ADD.name, csv);
		int result = access(ADD.name, 0);


		if (result == -1)
		{
			perror("해당하는 학생이 없습니다!!\n");
			getch();
			return;
		}
		else if (result == 0)
		{
			fopen_s(&fp, ADD.name, "a+");
			char tardy[99] = { NULL };
			char time[99] = { NULL };
			printf("지각한 년도 날짜를 입력해주세요 ((예) 2020/2/17) : ");
			scanf_s("%s", tardy, 30);

			printf("지각한 시간을 입력해주세요 ((예) 7:12) : ");
			scanf_s("%s", time, 30);


			fprintf(fp, "\n%s %s" , tardy, time);
			printf(" '%s %s' 지각이 추가되었습니다.\n", tardy, time);
			printf("아무키나 눌러주세요!\n");

			getch();
			fclose(fp);
		}
	}

	else if (cnt == 3)
	{
		printf("메인으로 돌아갑니다.\n");
		getch();
		return;
	}
	else if (cnt < 1 || cnt>3)
	{
		printf("잘 못 고르셨습니다.\n");
		getch();
		return;
	}

}
//추가함수

//검색함수
void search(void)
{
	LIST SCH;

	char singerlist[99] = { "학생목록.csv" };

	printf("검색하실 학생을 입력해주세요 : ");
	scanf_s(" %s", &SCH.name, 30);
	char* ptr = strstr(singerlist, SCH.name);
	fopen_s(&fp, singerlist, "r");

	if (fp != NULL)
	{
		printf("해당 학생 목록을 불러오는중.. \n");
		while ((fgets(singerlist, sizeof(singerlist), fp)) != NULL)
		{
			char* ptr = strstr(singerlist, SCH.name);

			if (ptr != NULL) {
				printf("%s", ptr);   // 검색된 문자열 출력
			}
		}
		fclose(fp);
	}
	else if (fp == NULL)
	{
		printf("해당하는 학생이 없습니다.\n");
		printf("추가하시겠습니까?[Y/N]:");
		scanf_s("%c", &SCH.YN, 1);
		while (getchar() != '\n');

		if (SCH.YN == 'Y' || SCH.YN == 'y')
		{
			system("cls");
			printf("================================= 메뉴 =================================\n\n");
			printf("□□□□□□□□□□□□□□  1. 학생 추가  □□□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□□  2. 지각 추가  □□□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□□   3. 메인으로  □□□□□□□□□□□□□□\n");
			printf("========================================================================\n");
			printf("사용 하실 목록을 선택하세요: ");
			scanf_s("%d", &SCH.cnt);
			while (getchar() != '\n');

			add(SCH.cnt);
		}

		else if (SCH.YN == 'N' || SCH.YN == 'n')
		{
			printf("추가하지 않았습니다.\n");
			system("pause");
			return;
		}
		else
		{
			printf("잘 못 선택하였습니다.\n");
		}
		system("pause");
		return;
	}
	getch();
}
//검색함수

//삭제함수
void rmv(int cnt)
{
	LIST RMV;

	if (cnt == 1)
	{
		char str[1000][256] = { 0, };
		int line = 0;
		int i, n;
		printf("삭제하고싶은 학생을 입력하세요:");
		scanf_s("%s", &RMV.name, 30);
		char singerlist[99] = { "학생목록.csv" };

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
		printf("삭제할 학생을 확인해주세요:");
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
			printf("삭제할 수 없습니다.\n");
			getch();
			return;
		}
		else if (_unlink(RMV.name)) {
			switch (errno) {
			case EACCES:
				fprintf(stderr, "엑세스가 거부 되었습니다. %s\n", RMV.name); break;
			case ENOENT:
				fprintf(stderr, "학생을 찾을 수 없습니다. %s\n", RMV.name); break;
			default:
				fprintf(stderr, "알수없는 오류입니다.\n"); break;
			}
			getch();
		}
		else
		{
			printf("삭제되었습니다. \n");
			getch();
		}
	}
	else if (cnt == 2)
	{
		RMV.YN = NULL;
		char str[1000][256] = { 0, };
		int line = 0;
		int i, n;

		printf("삭제하고싶은 학번에 해당하는 학생를 입력해주세요 :");
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
		printf("삭제하고싶은 지각 :");
		scanf_s("%d", &n);
		while (getchar() != '\n');

		fopen_s(&fp, RMV.name, "w");

		for (i = 0; i < line; i++)
		{
			if (n != (i + 1))
				fprintf(fp, "%s", str[i]);
		}
		fclose(fp);

		printf("삭제되었습니다.\n 목록을 확인하시겠습니까?[Y/N] : ");
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
			printf("메인으로 돌아갑니다.\n");
			getch();
			return;
		}
		else
		{
			printf("잘 못 입력하셨습니다.\n");
			getch();
			return;
		}
		return;
	}
	else if (cnt == 3)
	{
		printf("메인으로 돌아갑니다.\n");
		getch();
		return;
	}
	else if (cnt < 1 || cnt>3)
	{
		printf("잘 못 고르셨습니다.\n");
		getch();
		return;
	}
}
//삭제함수

//불러오기함수
void call(cnt)
{
	LIST CALL;

	if (cnt == 1)
	{
		system("cls");
		strcpy((char*)CALL.name, "학생목록.csv");
		fopen_s(&fp, CALL.name, "r");

		if (fp != NULL)
		{
			printf("학생 목록을 불러오는중.. \n");
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
			printf("불러올 목록이 존재하지 않습니다. \n");
		}
		fclose(fp);
	}
	else if (cnt == 2)//원하는 지각 목록
	{

		system("cls");

		CALL.YN = NULL;

		printf("원하는 학생를 입력하세요: ");
		scanf_s("%s", &CALL.name, 30);
		strcat(CALL.name, csv); //파일입출력을 불러오기위해서는 .csv가 포함되어야하는데 학생이름과 .csv를 붙임으로써 생략
		int result = access(CALL.name, 0);

		if (result == 0)
		{
			fopen_s(&fp, CALL.name, "a+");
			printf("해당 학생의 지각횟수를 불러오는중.");
			while ((fgets(CALL.name, sizeof(CALL.name), fp)) != NULL)
			{
				printf("%s", CALL.name);
			}
			printf("\n");
			printf("해당 학생의 지각횟수을 추가하시겠습니까?[Y/N] \n");
			scanf_s(" %c", &CALL.YN, 30);
			while (getchar() != '\n');

			if (CALL.YN == 'Y' || CALL.YN == 'y')
			{
				char input[256];
				char input2[256];
				printf("지각한 날짜를 입력해주세요 : ");
				scanf_s("%s", input, 30);
				printf("지각한 시간을 입력해주세요 : ");
				scanf_s("%s", input2, 30);

				fprintf(fp, "\n%s %s", input, input2);
				printf("추가되었습니다. \n");
				system("pause"); //콘솔창 멈춤
				fclose(fp);
			}
			else if (CALL.YN == 'N' || CALL.YN == 'n')
			{
				printf("추가하지 않았습니다.\n");
				system("pause");
				fclose(fp);
			}
			else
			{
				printf("잘 못 선택하였습니다.\n");
				system("pause");
				fclose(fp);
			}
		}
		else if (result == -1)
		{
			CALL.YN = NULL;
			printf("해당 학생이 없습니다!\n");
			printf("추가하시겠습니까?[Y/N]:");
			scanf_s(" %c", &CALL.YN, 1);
			while (getchar() != '\n');

			if (CALL.YN == 'Y' || CALL.YN == 'y')
			{
				system("cls");
				printf("================================= 메뉴 =================================\n\n");
				printf("□□□□□□□□□□□□□□  1. 학생 추가  □□□□□□□□□□□□□□\n");
				printf("□□□□□□□□□□□□□□  2. 지각 추가  □□□□□□□□□□□□□□\n");
				printf("□□□□□□□□□□□□□□   3. 메인으로  □□□□□□□□□□□□□□\n");
				printf("========================================================================\n");
				printf("보고 싶은 목록을 선택하세요: ");
				scanf("%d", &CALL.cnt);
				while (getchar() != '\n');
				add(CALL.cnt);
			}
			else if (CALL.YN == 'N' || CALL.YN == 'n')
			{
				printf("추가하지 않았습니다.\n");
				system("pause");
				return;
			}
			else
			{
				printf("잘 못 선택하였습니다.\n");
			}
			system("pause");
			return;
		}
		fclose(fp);
	}



	/*@#@#!@#@!#추가 중!@#!@#@!#!@# -> 몆분 늦었는지 비교 후 늦은 시간마다 벌칙 출력 
	else if (cnt == 3)
	{
		system("cls");

		CALL.YN = NULL;
		printf("지각한 학생을 입력하세요 : ");
		scanf_s("%s", &CALL.name, 30);
		strcat(CALL.name, csv); //파일입출력을 불러오기위해서는 .csv가 포함되어야하는데 학생이름과 .csv를 붙임으로써 생략
		int result = access(CALL.name, 0);
		int num1;

		if (result == 0) {

			int i = 0;
			fopen_s(&fp, CALL.name, "a+");
			printf("해당 학생의 지각횟수를 불러오는중.");
			while ((fgets(CALL.name, sizeof(CALL.name), fp)) != NULL)
			{
				printf("%d%s" ,i , CALL.name, 30);
			}
			printf("\n");
			printf("다음 중 확인하려는 벌칙의 날짜에 해당하는 번호를 입력해주세요 : \n");
			scanf_s(" %d", ? 30);
			while (getchar() != '\n');


		}
	}
	*/

			else if (cnt == 4)
			{
				intro();
				printf("메인으로 이동합니다.\n");
				system("pause");
				return;
			}
			else if (cnt < 1 || cnt>3)
			{
				intro();
				printf("잘 못 선택하셨습니다.\n 메인으로 돌아갑니다.\n");
				system("pause");
				return;
			}
	}
//불러오기함수

//명령어함수
void command(void)
{
	LIST COM;

	ctrl = getch();

	if (ctrl == 15)//CTRL+O (불러오기)
	{
		COM.cnt = 0;

		intro();
		printf("================================= 메뉴 =================================\n\n");
		printf("□□□□□□□□□□□□□□  1. 학생 목록  □□□□□□□□□□□□□□\n");
		printf("□□□□□□□□□□□  2. 해당 학생의 지각 목록  □□□□□□□□□□□\n");
		printf("□□□□□□□□□□□□□□   3. 메인으로  □□□□□□□□□□□□□□\n");
		printf("========================================================================\n");
		printf("보고 싶은 목록을 선택하세요: ");
		scanf("%d", &COM.cnt);
		while (getchar() != '\n');

		call(COM.cnt);
	}
	else if (ctrl == 18)//ctrl+R (삭제하기)
	{
		intro();
		COM.cnt = 0;
		printf("================================= 메뉴 =================================\n\n");
		printf("□□□□□□□□□□□□□□  1. 학생 삭제  □□□□□□□□□□□□□□\n");
		printf("□□□□□□□□□□□□□□  2. 지각 삭제  □□□□□□□□□□□□□□\n");
		printf("□□□□□□□□□□□□□□   3. 메인으로  □□□□□□□□□□□□□□\n");
		printf("========================================================================\n");
		printf("사용 하실 목록을 선택하세요: ");
		scanf_s("%d", &COM.cnt);
		while (getchar() != '\n');
		rmv(COM.cnt);
	}
	else if (ctrl == 1)//ctrl+A (추가하기)
	{
		intro();
		printf("================================= 메뉴 =================================\n\n");
		printf("□□□□□□□□□□□□□□  1. 학생 추가  □□□□□□□□□□□□□□\n");
		printf("□□□□□□□□□□□□□□  2. 지각 추가  □□□□□□□□□□□□□□\n");
		printf("□□□□□□□□□□□□□□   3. 메인으로  □□□□□□□□□□□□□□\n");
		printf("========================================================================\n");
		printf("사용 하실 목록을 선택하세요: ");
		scanf_s("%d", &COM.cnt);
		while (getchar() != '\n');

		add(COM.cnt);
	}
	else if (ctrl == 6)//ctrl+F(검색하기)
	{
		intro();
		search();
	}
	else if (ctrl == 3)//ctrl+C(수정하기)
	{
		char oldname[99] = { NULL };
		char newname[99] = { NULL };
		intro();
		printf("학생의 이름을 입력해주세요: ");
		scanf_s("%s", &oldname, 30);
		printf("수정하실 이름을 입력해주세요: ");
		scanf_s("%s", &newname, 30);
		change(oldname, newname);
	}
	else if (ctrl == 27)
	{
		char answer = NULL;

		intro();
		printf("정말 종료하시겠습니까?[Y/N]: ");
		scanf_s(" %c", &answer, 1);
		while (getchar() != '\n');

		if (answer == 'Y' || answer == 'y')
		{
			printf("종료하였습니다.\n\n");
			exitprint();
			getch();
			exit(0);
		}

		else if (answer == 'N' || answer == 'n')
		{
			printf("메인으로 돌아갑니다.\n");
			system("pause");
			return;
		}

		else
		{
			printf("잘 못 누르셨습니다.\n");
			getch();
			return;
		}
	}
}
//명령어함수

//메인함수
int main(void)
{
	LIST MAIN;
	system("mode con cols=75 lines=35");
	int pass = 8431;
	int answer = 0;
	intro();
	printf("□□□□□□□□□ 이용하시려면 패스워드를 입력해주세요. □□□□□□□□□\n");
	printf("패스워드를 입력해주세요 : ");
	scanf_s("%d", &answer);

	if (answer != pass) {

		printf("패스워드가 틀렸습니다.");
	}

	else if (answer == pass) {
		while (1) {
			intro();
			printf("================================= 메뉴 =================================\n\n");
			printf("□□□□□□□□□□□□□  추가하기 : CTRL+A □□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□  삭제하기 : CTRL+R □□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□  검색하기 : CTRL+F □□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□  수정하기 : CTRL+C □□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□  불러오기 : CTRL+O □□□□□□□□□□□□□\n");
			printf("□□□□□□□□□□□□□   종료하기 : ESC  □□□□□□□□□□□□□□\n");
			printf("========================================================================\n");
			command();
		}
	}
}
//메인함수