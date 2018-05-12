#include<stdio.h>
int fun()
{
	if(1 < 2)
	{
		return;
	}
	else
	{
		return 1;
	}
}
int main()
{
	printf("%d\n",fun());
	return 0;
}

