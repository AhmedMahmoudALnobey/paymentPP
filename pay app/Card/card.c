#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter card holder name : ");
	fgets(cardData->cardHolderName,25,stdin);

	if (strlen(cardData->cardHolderName) < 20 || cardData->cardHolderName==NULL || strlen(cardData->cardHolderName) > 24 )
		return WRONG_NAME;

	printf("holder card name : %s\n", cardData->cardHolderName);
	 return  car_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter card Expiry Date in format (MM/YY) : ");
	scanf_s("%s", &cardData->cardExpirationDate,6);

	if (strlen(cardData->cardExpirationDate) == 5 && cardData->cardExpirationDate[2] == '/' && 
		isdigit(cardData->cardExpirationDate[0]) && isdigit(cardData->cardExpirationDate[1])
		&&isdigit(cardData->cardExpirationDate[3])&& isdigit(cardData->cardExpirationDate[4]))
	{
		printf("card date : %s\n\n", cardData->cardExpirationDate);
		return car_OK;
	}
	return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter PAN number: ");
	scanf_s(" %s", &cardData->primaryAccountNumber,19);

	if (strlen(cardData->primaryAccountNumber) < 16 || cardData->cardHolderName == NULL) return WRONG_PAN;
	printf("card pan number : %s\n", cardData->primaryAccountNumber);
	return  car_OK;
}