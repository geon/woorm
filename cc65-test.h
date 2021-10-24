#include <stdint.h>

void beforeTests();
void afterTests();
void beginTest(char *messageString);
void endTest();
void assertWord(char *messageString, uint16_t result, uint16_t okValue);
void assertByte(char *messageString, uint8_t result, uint8_t okValue);
