#include <gtest/gtest.h>

#include "palindrome.h"

TEST(tests1, NormalWords) {
    EXPECT_EQ(palindrome("topot"), 1);
    EXPECT_EQ(palindrome("polina"), 0);
    EXPECT_EQ(palindrome("zakaz"), 1);
    EXPECT_EQ(palindrome("oop"), 0);

}

TEST(tests2, Abracadabra) {
    EXPECT_EQ(palindrome("a1FcF1а"), 0); // вторая а - рус, первая - англ
    EXPECT_EQ(palindrome("a1FcF1a"), 1); // обе англ
}

TEST(tests3, Numbers) {
    EXPECT_EQ(palindrome("333"), 1);
    EXPECT_EQ(palindrome("7274536"), 0);
    EXPECT_EQ(palindrome("121"), 1);
}

TEST(tests4, Symbols) {
    EXPECT_EQ(palindrome("!##!"), 1);
    EXPECT_EQ(palindrome("!#^%#!"), 0);
}

TEST(tests5, Sentence) {
    EXPECT_EQ(palindrome("A roza upala na lapu Azora"), 1);
    EXPECT_EQ(palindrome("Umer, i mir emu"), 0); // "," - символ 
    EXPECT_EQ(palindrome("Okolo Mihi moloko"), 1);
}