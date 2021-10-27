#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __C64__
#include <c64.h>
#include <conio.h>
#endif

char *lastMessageStringPointer = NULL;

void beforeTests()
{
#ifdef __C64__
	clrscr();
	textcolor(COLOR_WHITE);
#endif

	printf("Running tests:\n");
	printf("----------------------------------------\n");
}

void afterTests()
{
#ifdef __C64__
	// Color for success.
	bgcolor(COLOR_GREEN);
	bordercolor(COLOR_LIGHTGREEN);
#endif

	// Display test result.
	printf("----------------------------------------\n");
	printf("All tests passed.\n");

	exit(0);
}

void fail(char *messageString, char *result, char *okValue)
{
#ifdef __C64__
	// Color for error.
	bgcolor(COLOR_RED);
	bordercolor(COLOR_LIGHTRED);
#endif

	printf("========================================\n");
	printf("Test failed:\n");
	printf("* %s\n", lastMessageStringPointer);
	printf("Assertion: %s\n", messageString);
	printf("Expected:  %s\n", okValue);
	printf("Actual:    %s\n", result);

	exit(1);
}

void beginTest(char *messageString)
{
	lastMessageStringPointer = messageString;
}

void endTest()
{
	printf("* %s\n", lastMessageStringPointer);
}

void assertWord(char *messageString, uint16_t result, uint16_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[7], okBuffer[7]; // 6 chars + null
		sprintf(resultBuffer, "0x%.4x", result);
		sprintf(okBuffer, "0x%.4x", okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertByte(char *messageString, uint8_t result, uint8_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[5], okBuffer[5]; // 4 chars + null
		sprintf(resultBuffer, "0x%.2x", result);
		sprintf(okBuffer, "0x%.2x", okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertWordDecimal(char *messageString, uint16_t result, uint16_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[6], okBuffer[6]; // 5 chars + null
		sprintf(resultBuffer, "%*i", 5, result);
		sprintf(okBuffer, "%*i", 5, okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertByteDecimal(char *messageString, uint8_t result, uint8_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[4], okBuffer[4]; // 3 chars + null
		sprintf(resultBuffer, "%*i", 3, result);
		sprintf(okBuffer, "%*i", 3, okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertTrue(char *messageString, bool success)
{
	if (!success)
	{
		fail(messageString, "false", "true");
	}
}
