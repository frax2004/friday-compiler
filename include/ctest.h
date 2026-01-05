#ifndef CTEST_H
#define CTEST_H

#define assertCheck(condition, fmt, ...) do { if(!(condition)) { printf(__FILE__":%d\n"fmt __VA_OPT__(,) __VA_ARGS__, __LINE__); exit(1); } } while(0)
#define assertTrue(condition) assertCheck((condition), # condition " should be true, but resulted to false")
#define assertFalse(condition) assertCheck(!(condition), # condition " should be false, but resulted to true")
#define assertEquals(expected, actual) assertCheck((expected) == (actual), # expected " should be equal to " #actual ", but equality is not satisfied")
#define assertNotEquals(expected, actual) assertCheck((expected) != (actual), # expected " should be different from " #actual ", but inequality is not satisfied")
#define assertNull(expression) assertCheck((expression) == NULL, # expression " should be null, but it is not null")
#define assertNotNull(expression) assertCheck((expression) != NULL, # expression " should not be null, but it is null")

#endif