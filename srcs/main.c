#include "../includes/malloc.h"


int main (int argc, char** argv)
{
	int sz = getpagesize();
  	printf("%d", sz);
  	return (0);
}