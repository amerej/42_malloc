#include "../includes/malloc.h"


int main (int argc, char** argv)
{
	char *str;

	str = (char *)malloc(5);
	str = "couc";
	write(1, "ca marche\n", 10);
}