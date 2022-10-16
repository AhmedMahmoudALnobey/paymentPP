#include<stdio.h>
#include<string.h>
#include"server.h"
#include"../Card/card.h"
#include"../Terminal/terminal.h"

ST_accountsDB_t server_side_accounts[255] = { {1000.5,"123456789101112131"},{1300.0,"1234567891011122"},{1800.0,"1234567891011123"},
{1059.7,"1234567891011124"},{200000.9,"1234567891011125"},{23948.9,"1234567891011126"},{190.0,"5399353562786336"}
,{155.0,"5399353562786443"},{2000.0,"8989374615436851"} };
ST_transaction_t server_side_transactions[255] = { 0 };

uint32_t trans_num = 0;
uint16_t i = 0;

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (; i < 255; i++)
	{
		if (strcmp(server_side_accounts[i].primaryAccountNumber,cardData->primaryAccountNumber ) == 0 )
			return ser_OK;
	}
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount < server_side_accounts[i].balance)
		return ser_OK;

	return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber = trans_num;
	if (transData->transactionSequenceNumber < 255)
	{
		server_side_transactions[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		server_side_transactions[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		server_side_transactions[transData->transactionSequenceNumber].transState = transData->transState;
		server_side_transactions[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;

		trans_num++;
		return ser_OK;
	}
	return SAVING_FAILED;
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_serverError_t va;
	EN_serverError_t aav;
	EN_serverError_t st;

	if (aav = isAmountAvailable(&transData->terminalData) == LOW_BALANCE) return DECLINED_INSUFFECIENT_FUND;

	if (va = isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) return DECLINED_STOLEN_CARD;

	if (st = saveTransaction(transData) == SAVING_FAILED) return INTERNAL_SERVER_ERROR;

	printf("\nbalance before transactian : %.3f", server_side_accounts[i].balance);
	server_side_accounts[i].balance -= transData->terminalData.transAmount;
	printf("\nbalance after trwnsactian : %.3f", server_side_accounts[i].balance);
	return APPROVED;
}

//EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
