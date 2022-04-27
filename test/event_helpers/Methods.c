#include "Methods.h"
#include <stdint.h>

int val_a;
int val_b;
int val_c;

void Method_step_a()
{
	val_a++;
}

void Method_step_b()
{
	val_b++;
}

void Method_step_c()
{
	val_c++;
}

void Method_reset()
{
	val_a = 0;
	val_b = 0;
	val_c = 0;
}

int get_val_a()
{
	return val_a;
}

int get_val_b()
{
	return val_b;
}

int get_val_c()
{
	return val_c;
}

