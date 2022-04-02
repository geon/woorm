#include "../cc65-test.h"
#include "charset-char.test.h"
#include "charset.test.h"

int main(void)
{

	beforeTests();

	charsetCharTest();
	charsetTest();

	afterTests();

	return 0;
}
