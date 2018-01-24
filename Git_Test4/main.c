#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void select_usercard(int *shape1, int *shape2, int *num1, int *num2);
void select_comcard(int *shape1, int *shape2, int *num1, int *num2, int *usershape1, int *usershape2, int *usernum1, int *usernum2);
char change_shape(int shape);
char* cal_rank(int shape1, int shape2, int num1, int num2, int *rank_val);
void referee(int user_num1, int user_num2, int com_num1, int com_num2, int user_rank, int com_rank, int* win_lose);

int main(void) {

	int user_shape1, user_shape2, user_num1, user_num2, user_rank_val;
	int com_shape1, com_shape2, com_num1, com_num2, com_rank_val;
	int win_lose, games = 1;
	int betting, cap_user = 100;
	srand(time(NULL));

	printf("?¬ì»¤ ê²Œì„???œì‘?©ë‹ˆ??\n\n");

	while (1) {

		while (1) {
			printf(":::%d??ê²Œì„:::\n", games);
			printf("ë² íŒ…ê¸ˆì•¡???…ë ¥?˜ì„¸??(?„ì¬ ?Œì?ê¸?%dë§Œì›, ì¢…ë£Œ ??-1 ?…ë ¥) : ", cap_user);
			scanf("%d", &betting);

			if (betting == -1)
				break;

			cap_user -= betting;

			if (cap_user < 0) {
				printf("?ˆì´ ë¶€ì¡±í•©?ˆë‹¤. ?¤ì‹œ ?…ë ¥?´ì£¼?¸ìš”.\n");
				cap_user += betting;
			}
			else
				break;
		};

		if (betting == -1)
			break;

		select_usercard(&user_shape1, &user_shape2, &user_num1, &user_num2);
		select_comcard(&com_shape1, &com_shape2, &com_num1, &com_num2, &user_shape1, &user_shape2, &user_num1, &user_num2);

		printf("?¬ìš©??ì¹´ë“œ : %c%d %c%d - %s\n", change_shape(user_shape1), user_num1, change_shape(user_shape2), user_num2, cal_rank(user_shape1, user_shape2, user_num1, user_num2, &user_rank_val));
		printf("ì»´í“¨??ì¹´ë“œ : %c%d %c%d - %s\n", change_shape(com_shape1), com_num1, change_shape(com_shape2), com_num2, cal_rank(com_shape1, com_shape2, com_num1, com_num2, &com_rank_val));

		referee(user_num1, user_num2, com_num1, com_num2, user_rank_val, com_rank_val, &win_lose);

		if (win_lose == 1)
			cap_user += 2 * betting;
		else if (win_lose == -1)
			cap_user += betting;
		else if (cap_user <= 0) {
			printf("?Œì‚°?˜ì…¨?µë‹ˆ?? ê²Œì„??ì¢…ë£Œ?©ë‹ˆ??\n");
			break;
		}

		games++;
	};

	printf("\nê°€ê°ì•¡ : %dë§Œì›\n", cap_user - 100);
	printf("ê²Œì„ ?Ÿìˆ˜ : %d\n", games);
	printf("ê²Œì„??ì¢…ë£Œ?©ë‹ˆ??\n");

	return 0;
}

void select_usercard(int *shape1, int *shape2, int *num1, int *num2) {

	*shape1 = (rand() % 4) + 1;
	*shape2 = (rand() % 4) + 1;

	*num1 = (rand() % 13) + 1;

	do {
		*num2 = (rand() % 13) + 1;
	} while ((*shape1 == *shape2) && (*num1 == *num2));
}

void select_comcard(int *shape1, int *shape2, int *num1, int *num2, int *usershape1, int *usershape2, int *usernum1, int *usernum2) {

	*shape1 = (rand() % 4) + 1;
	*shape2 = (rand() % 4) + 1;

	do {
		*num1 = (rand() % 13) + 1;
	} while (((*shape1 == *usershape1) && (*num1 == *usernum1)) || ((*shape1 == *usershape2) && (*num1 == *usernum2)));

	do {
		*num2 = (rand() % 13) + 1;
	} while (((*shape1 == *usershape1) && (*num1 == *usernum1)) || ((*shape1 == *usershape2) || (*num1 == *usernum2)) || ((*shape1 == *shape2) && (*num1 == *num2)));
}

char change_shape(int shape) {
	if (shape == 1)
		return 'S';
	else if (shape == 2)
		return 'C';
	else if (shape == 3)
		return 'D';
	else
		return 'H';
}

char* cal_rank(int shape1, int shape2, int num1, int num2, int *rank_val) {

	if (shape1 == shape2) {
		if (((num1 - num2) == 1) || ((num1 - num2) == -1)) {
			*rank_val = 4;
			return "SF";
		}
		else {
			*rank_val = 3;
			return "FL";
		}
	}
	else
		if (((num1 - num2) == 1) || ((num1 - num2) == -1)) {
			*rank_val = 2;
			return "SR";
		}
		else if (num1 == num2) {
			*rank_val = 1;
			return "PR";
		}
		else {
			*rank_val = 0;
			return "SC";
		}
}

void referee(int user_num1, int user_num2, int com_num1, int com_num2, int user_rank, int com_rank, int* win_lose) {

	int usernum, comnum;

	if (user_rank > com_rank) {
		printf("?¬ìš©?ê? ?¹ë¦¬?˜ì??µë‹ˆ??\n\n");
		*win_lose = 1;
	}
	else if (user_rank < com_rank) {
		printf("ì»´í“¨?°ê? ?¹ë¦¬?˜ì??µë‹ˆ??\n\n");
		*win_lose = 0;
	}
	else {
		if (user_num1 >= user_num2)
			usernum = user_num1;
		else
			usernum = user_num2;

		if (com_num1 >= com_num2)
			comnum = com_num1;
		else
			comnum = com_num2;

		if (usernum > comnum) {
			printf("?¬ìš©?ê? ?¹ë¦¬?˜ì??µë‹ˆ??\n\n");
			*win_lose = 1;
		}
		else if (usernum < comnum) {
			printf("ì»´í“¨?°ê? ?¹ë¦¬?˜ì??µë‹ˆ??\n\n");
			*win_lose = 0;
		}
		else {
			printf("ë¬´ìŠ¹ë¶€?…ë‹ˆ??\n\n");
			*win_lose = -1;
		}
	}
}
