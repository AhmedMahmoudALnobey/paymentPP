#include<stdio.h>
#include"../Card/card.h"
#include"../Server/server.h"
#include"../Terminal/terminal.h"
void appStart(void);
int main()
{
	appStart();
}
void appStart(void)
{
	EN_cardError_t cardholdername, cardexpirydate, cardpan;

	ST_cardData_t cardolderdata;
	ST_cardData_t* carddate = &cardolderdata;
	
	if (cardholdername = getCardHolderName(carddate) == WRONG_NAME)
	{
		printf(" WRONG_NAME "); return 0;
	}
	if (cardexpirydate = getCardExpiryDate(carddate) == WRONG_EXP_DATE)
	{
		printf(" WRONG_EXP_DATE "); return 0;
	}
	if (cardpan = getCardPAN(carddate) == WRONG_PAN)
	{
		printf("  WRONG_PAN ");
		return 0;
	}
	
	EN_terminalError_t vaildpan, transactiandate, cardepired, maxammount, transactianamount, belowmaxamount;

	ST_terminalData_t termianldata;
	ST_terminalData_t* termData = &termianldata;
	if (vaildpan = isValidCardPAN(carddate) == INVALID_CARD)
	{
		printf(" INVALID_CARD ");
		return 0;
	}
	setMaxAmount(termData);
	getTransactionDate(termData);
	if (cardepired = isCardExpired(cardolderdata, termianldata) == EXPIRED_CARD)
	{
		printf(" EXPIRED_CARD ");
		return 0;
	}
	if (transactianamount = getTransactionAmount(termData) == INVALID_AMOUNT)
	{
		printf("invaild amount");
		return 0;
	}
	if (belowmaxamount = isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
	{
		printf(" EXCEED MAX AMOUNT\nmax amount : 200000 ");
		return 0;
	}

	EN_transState_t recievetrans;
	ST_transaction_t transactionsdata;
	ST_transaction_t* transData = &transactionsdata;
	transData->cardHolderData = cardolderdata;
	transData->terminalData = termianldata;
	recievetrans = recieveTransactionData(transData);
	if (recievetrans == APPROVED)
		printf("\ntransactian success");
	if (recievetrans == DECLINED_INSUFFECIENT_FUND)
	{
		saveTransaction(transData);
		printf("transactian DECLINED_INSUFFECIENT_FUND");
		return 0;
	}
	if (recievetrans == DECLINED_STOLEN_CARD)
	{
		saveTransaction(transData);
		printf("transactian DECLINED_STOLEN_CARD");
		return 0;
	}
	if (recievetrans == INTERNAL_SERVER_ERROR)
	{
		saveTransaction(transData);
		printf("transactian DECLINED_INTERNAL_SERVER_ERROR");
		return 0;
	}
}