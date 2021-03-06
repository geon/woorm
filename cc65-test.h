#include <stdbool.h>
#include <stdint.h>

void beforeTests(void);
void afterTests(void);
void beginTest(char *messageString);
void endTest(void);

void assertWord(char *messageString, uint16_t result, uint16_t okValue);
void assertByte(char *messageString, uint8_t result, uint8_t okValue);
void assertWordDecimal(char *messageString, uint16_t result, uint16_t okValue);
void assertByteDecimal(char *messageString, uint8_t result, uint8_t okValue);
void assertTrue(char *messageString, bool success);
void assertIntDecimal(char *messageString, int result, int okValue);

void fail(char *messageString, char *result, char *okValue);
