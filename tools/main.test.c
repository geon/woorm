#include "../cc65-test.h"
#include "charset-char.test.h"
#include "charset.test.h"
#include "partial-charset.test.h"

int main(void)
{

	beforeTests();

	charsetCharTest();
	charsetTest();
	partialCharsetTest();

	afterTests();

	return 0;
}
