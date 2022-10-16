#define _CRT_SECURE_NO_WARNINGS 

#include<stdint.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"../Card/card.h"
#include"terminal.h" 


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	//0123456789
	//dd/mm/yyyy

	uint8_t da[3], ma[3], ye[5];
	time_t sdate = time(NULL);
	struct tm tim = *localtime(&sdate);
	sprintf(da, "%d", tim.tm_mday);
	if (tim.tm_mday < 10)
	{
		(termData->transactionDate[0]) = '0';
		(termData->transactionDate[1]) = da[0];
	}
	else {
		(termData->transactionDate[0]) = da[0];
		(termData->transactionDate[1]) = da[1];
	}
	sprintf(ma, "%d", tim.tm_mon + 1);
	if ((tim.tm_mon + 1) < 10)
	{
		(termData->transactionDate[3]) = '0';
		(termData->transactionDate[4]) = ma[0];
	}
	else {
		(termData->transactionDate[3]) = ma[0];
		(termData->transactionDate[4]) = ma[1];
	}
	sprintf(ye, "%d", tim.tm_year + 1900);
	termData->transactionDate[5] = '/';
	termData->transactionDate[6] = ye[0];
	termData->transactionDate[7] = ye[1];
	termData->transactionDate[8] = ye[2];
	termData->transactionDate[9] = ye[3];
	termData->transactionDate[10] = '\0';
	if (termData->transactionDate == NULL) return WRONG_DATE;
	else 
	{ 
		printf("today Date is: %02d - %02d - %02d\n", tim.tm_mday, tim.tm_mon + 1, tim.tm_year + 1900); 
	     return ter_OK; 
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (cardData.cardExpirationDate[4] < termData.transactionDate[9]) return EXPIRED_CARD;

	if (cardData.cardExpirationDate[3] == termData.transactionDate[8])
	{
		if (cardData.cardExpirationDate[4] < termData.transactionDate[9]) return EXPIRED_CARD;

		if (cardData.cardExpirationDate[4] == termData.transactionDate[9])
		{
			if (cardData.cardExpirationDate[0] < termData.transactionDate[3]) return EXPIRED_CARD;

			if (cardData.cardExpirationDate[0] == termData.transactionDate[3])
			{
				if (cardData.cardExpirationDate[1] < termData.transactionDate[4]) return EXPIRED_CARD;
			}
		}
	}
	return ter_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint16_t sum = 0;
	uint16_t panlen;
	uint16_t counter = 1;
	uint16_t pandigits[20] = { 0 };
	panlen = (uint16_t)strlen(cardData->primaryAccountNumber);

	for (uint16_t i = panlen - 1; i > 0; i--)
	{
		if (counter % 2 == 0)
		{
			uint16_t temp = (cardData->primaryAccountNumber[i] - '0') * 2;
			if ((temp / 10) > 0)
			{
				temp = (temp % 10) + 1;
				pandigits[i] = temp;
			}
			else 
			{
				pandigits[i] = temp;
			}
		}
		else
		{
			pandigits[i] = (cardData->primaryAccountNumber[i] - '0');
		}
		counter++;
	}

	if (counter % 2 == 0)
	{
		uint16_t temp = (cardData->primaryAccountNumber[0] - '0') * 2;
		if ((temp / 10) > 0)
		{
			temp = (temp % 10) + 1;
			pandigits[0] = temp;
		}
		else
		{
			pandigits[0] = temp;
		}
	}
	else
	{
		pandigits[0] = (cardData->primaryAccountNumber[0] - '0');
	}

	for (uint16_t i = 0; i < panlen; i++)
	{
		sum += pandigits[i];
	}

	if (sum % 10 == 0)
	{
		printf("vaild card\n");
		return ter_OK;
	}
	else
		return INVALID_CARD;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = 200000;
	return ter_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Enter transaction amount : ");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0) 
		return INVALID_AMOUNT;
	printf("your transaction amount : %.3f\n", termData->transAmount);
	return ter_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	return ter_OK;
}

