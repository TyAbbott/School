//Ty Abbott
//Sale calculator
//9-1-15

#include <stdio.h>

int main()
{
	int price=0;
	int sale=0;
	printf("What is the original price?");
	scanf("%d",&price);
	printf("What is the sale percentage?");
	scanf("%d",&sale);
	int finalPrice = price-(price*((float)sale/100));
	printf("An item originally costing $%d on a %d sale is $%d", price, sale, finalPrice);
	return 0;


}
