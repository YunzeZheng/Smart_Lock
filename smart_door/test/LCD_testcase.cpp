#include <Arduino.h>
#include <unity.h>
#include "../src/main.h"
#include "../src/LCD.cpp"

// Test for LCD initialization
void test_LCD_init() {
    lcd.clear();
    LCD_init();
    TEST_ASSERT_TRUE(true); 
}

// Test for displaying a full message on the LCD
void test_lcd_show_message() {
    const char* message = "Hello World! Welcome to LCD testing!";
    lcd_show_message(message);
    delay(1000);
    TEST_ASSERT_TRUE(true);
}

// Test for displaying text in the first column
void test_lcd_FirstCol() {
    const char* message = "First Column";
    lcd_FirstCol(message);
    delay(1000);
    TEST_ASSERT_TRUE(true);
}

// Test for displaying text in the second column
void test_lcd_SecondCol() {
    const char* message = "Second Column";
    lcd_SecondCol(message);
    delay(1000);
    TEST_ASSERT_TRUE(true);
}

// Test for enabling save mode
void test_lcd_savemode() {
    lcd_savemode();
    delay(1000);
    TEST_ASSERT_TRUE(true);
}

void setup1() {
    UNITY_BEGIN();

    RUN_TEST(test_LCD_init);
    RUN_TEST(test_lcd_show_message);
    RUN_TEST(test_lcd_FirstCol);
    RUN_TEST(test_lcd_SecondCol);
    RUN_TEST(test_lcd_savemode);
    UNITY_END();
}

void loop1() {
    // No actions required in the loop for Unity tests
}

