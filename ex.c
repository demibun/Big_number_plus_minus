#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max 101
int check = 0;
char result[max * 2] = "";

struct numbers
{
	char num[max];
	char numstr[max];
};

void plus(struct numbers nums[])
{

	int sum = 0, i, carry = 0;

	for (i = max - 2; i >= 0; i--)
	{
		sum = (nums[0].numstr[i] - '0') + (nums[1].numstr[i] - '0') + carry;
		carry = sum / 10;
		sum = sum % 10;
		result[i + 1] = sum + '0';
	}
	result[0] = carry + '0';



}

void minus(struct numbers nums[])
{

	int sum = 0, i, carry = 0, count1 = 0, count2 = 0;
	for (int i = 0; i < strlen(nums[0].numstr); i++)
	{
		if (nums[0].numstr[i] == '0')
			count1++;
	}
	for (int i = 0; i < strlen(nums[1].numstr); i++)
	{
		if (nums[1].numstr[i] == '0')
			count2++;
	}

	if (count1 < count2)
	{
		for (i = max - 2; i >= 0; i--)
		{
			sum = (nums[0].numstr[i] - '0') - (nums[1].numstr[i] - '0') + carry;

			if (sum >= 0)
			{
				carry = -(sum / 10);
				sum = sum % 10;
			}
			else
			{
				sum = 10 - (nums[1].numstr[i] - '0') + (nums[0].numstr[i] - '0') + carry;
				carry = -1;
			}

			result[i + 1] = sum + '0';
			result[0] = -carry + '0';
		}

		for (i = 0; result[i] == '0'; i++);

	}
	else if (count1 > count2)
	{
		for (i = max - 2; i >= 0; i--)
		{
			sum = (nums[1].numstr[i] - '0') - (nums[0].numstr[i] - '0') + carry;

			if (sum >= 0)
			{
				carry = -(sum / 10);
				sum = sum % 10;
			}
			else
			{
				sum = 10 - (nums[0].numstr[i] - '0') + (nums[1].numstr[i] - '0') + carry;
				carry = -1;
			}

			result[i + 1] = sum + '0';
			result[0] = -carry + '0';
		}

		for (i = 0; result[i] == '0'; i++);
		check = 1;
	}
	else
	{
		for (i = strlen(nums[0].numstr) - count1; i < strlen(nums[0].numstr); i++)
		{
			if (nums[0].numstr[i] > nums[1].numstr[i])
			{
				for (i = max - 2; i >= 0; i--)
				{
					sum = (nums[0].numstr[i] - '0') - (nums[1].numstr[i] - '0') + carry;

					if (sum >= 0)
					{
						carry = -(sum / 10);
						sum = sum % 10;
					}
					else
					{
						sum = 10 - (nums[1].numstr[i] - '0') + (nums[0].numstr[i] - '0') + carry;
						carry = -1;
					}

					result[i + 1] = sum + '0';
					result[0] = -carry + '0';
				}

				for (i = 0; result[i] == '0'; i++);
				break;
			}
			else if (nums[0].numstr[i] < nums[1].numstr[i])
			{
				for (i = max - 2; i >= 0; i--)
				{
					sum = (nums[1].numstr[i] - '0') - (nums[0].numstr[i] - '0') + carry;

					if (sum >= 0)
					{
						carry = -(sum / 10);
						sum = sum % 10;
					}
					else
					{
						sum = 10 - (nums[0].numstr[i] - '0') + (nums[1].numstr[i] - '0') + carry;
						carry = -1;
					}

					result[i + 1] = sum + '0';
					result[0] = -carry + '0';
				}

				for (i = 0; result[i] == '0'; i++);
				check = 1;
				break;
			}

		}
	}

}
void multi(struct numbers nums[])
{
	for (int i = 0; i < nums[0].numstr; i++)
	{
		plus(nums);
	}

}

int main(void)
{
	struct numbers nums[2];
	char geti[max * 3] /* 공백 포함 입력 */, getf[max * 3] = { 0 }; /* 공백 제거 */
	int i, j = 0, num_len = 0, len = 0, lenf = 0;
	int c1 = 0, c2 = 0, cnt = 0;

	for (i = 0; i < max; i++)
	{
		nums[0].num[i] = '\0';
		nums[1].num[i] = '\0';
	}

	printf("사용법: 숫자와 연산자를 입력하고 엔터를 누르세요.\nex) 32 * 532 / 2 - 7 + 8\n\n");
	scanf(" %[^\n]", geti);

	len = strlen(geti);

	for (i = 0; i < len; i++)
	{
		if (geti[i] != ' ')
		{
			getf[j] = geti[i];
			j++;
		}

	}
	lenf = strlen(getf);

	for (i = 0; i < lenf; i++) // 모든 숫자와 연산자 확인
	{
		if ((getf[i] == '+') || (getf[i] == '-') || (getf[i] == '*') || (getf[i] == '/'))
		{
			for (int z = 0; z < i; z++) {
				nums[0].num[c1] = getf[z];
				c1++;
			}

			for (int w = i + 1; w < lenf; w++)
			{
				nums[1].num[c2] = getf[w];
				c2++;
			}

			break;

		}

	}
	sprintf(nums[0].numstr, "%0100s", nums[0].num);
	sprintf(nums[1].numstr, "%0100s", nums[1].num);

	for (i = 0; i < lenf; i++)

	{
		if (cnt == 1) {
			break;
		}
		switch (getf[i])
		{
		case ('+'): plus(nums), cnt++;
			break;
		case ('-'): minus(nums), cnt++;
			break;
		case ('*'):multi(nums), cnt++;
			break;
		case ('/'):
			break;

		}
	}

	if (check == 0)
	{
		for (i = 0; result[i] == '0'; i++);
		printf("%s\n", result+i);
			printf("\n");
	}
	else if (check == 1)
	{
		for (i = 0; result[i] == '0'; i++);
		printf("-%s\n", result+i);
			printf("\n");
	}
	return 0;
}
