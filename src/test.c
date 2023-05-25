#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strlen) {
  char *strings[] = {
      "",
      "\0",
      "  \n\0\0",
      "oireub ejenrgi",
      "oireub ejenrgi\0",
      "ernv\0 ergerw",
      "394fn43 43punf\n9034 i2 f0u94585\t9n54rij vi04389j3-21ieopn2v"};
  for (size_t i = 0; i < sizeof(strings) / sizeof(*strings); i++) {
    ck_assert_int_eq(strlen(strings[i]), s21_strlen(strings[i]));
  }
}
END_TEST

START_TEST(test_memset) {
  char str_21[11] = "";
  char str_31[30] = "oireub ejenrgi\n jr oi";
  char str_41[50] = " schhol21\0roep";
  char *p41 = str_41 + 9;
  char str_51[50] = "          ";
  char str_61[60] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
  char *p61 = str_61 + 6;
  char str_71[10] = "\0";
  char str_22[11] = "";
  char str_32[30] = "oireub ejenrgi\n jr oi";
  char str_42[50] = " schhol21\0roep";
  char *p42 = str_42 + 9;
  char str_52[50] = "          ";
  char str_62[60] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
  char *p62 = str_62 + 6;
  char str_72[10] = "\0";
  ck_assert_str_eq(memset(str_21, '0', 7), s21_memset(str_22, '0', 7));
  ck_assert_str_eq(memset(str_31, '\0', 1), s21_memset(str_32, '\0', 1));
  ck_assert_str_eq(memset(p41, 'q', 2), s21_memset(p42, 'q', 2));
  ck_assert_str_eq(memset(str_51, 's', 20), s21_memset(str_52, 's', 20));
  ck_assert_str_eq(memset(p61, '%', 5), s21_memset(p62, '%', 5));
  ck_assert_str_eq(memset(str_71, 'q', 0), s21_memset(str_72, 'q', 0));
  ck_assert_str_eq(memset(str_71, 'q', 8), s21_memset(str_72, 'q', 8));
}
END_TEST

START_TEST(test_memcmp) {
  char *strings[] = {
      "",
      "67^2",
      "6743",
      "oireub ejenrgi",
      "oIOggreub ejenrgi",
      "ernv\0 ergerw",
      "ernv ergerw",
      "394fn43 43punf\n9034 i2 f0u94585\t9n54rij vi04389j3-21ieopn2v"};
  ck_assert_int_eq(memcmp(strings[0], strings[1], 3),
                   s21_memcmp(strings[0], strings[1], 3));
  ck_assert_int_eq(memcmp(strings[1], strings[2], 4),
                   s21_memcmp(strings[1], strings[2], 4));
  ck_assert_int_eq(memcmp(strings[1], strings[2], 2),
                   s21_memcmp(strings[1], strings[2], 2));
  ck_assert_int_eq(memcmp(strings[1], strings[2], 0),
                   s21_memcmp(strings[1], strings[2], 0));
  ck_assert_int_eq(memcmp(strings[3], strings[4], 10),
                   s21_memcmp(strings[3], strings[4], 10));
  ck_assert_int_eq(memcmp(strings[5], strings[6], 5),
                   s21_memcmp(strings[5], strings[6], 5));
  ck_assert_int_eq(memcmp(strings[7], strings[6], 1),
                   s21_memcmp(strings[7], strings[6], 1));
}
END_TEST

START_TEST(test_strcmp) {
  char *strings[] = {
      "",
      "6753",
      "6734",
      "oireub ejenrgi",
      "oiggreub ejenrgi",
      "ernv\0 ergerw",
      "ernv ergerw",
      "394fn43 43punf\n9034 i2 f0u94585\t9n54rij vi04389j3-21ieopn2v"};
  ck_assert_int_eq(strcmp(strings[0], strings[1]),
                   s21_strcmp(strings[0], strings[1]));
  ck_assert_int_eq(strcmp(strings[1], strings[2]),
                   s21_strcmp(strings[1], strings[2]));
  ck_assert_int_eq(strcmp(strings[1], strings[2]),
                   s21_strcmp(strings[1], strings[2]));
  ck_assert_int_eq(strcmp(strings[1], strings[2]),
                   s21_strcmp(strings[1], strings[2]));
  ck_assert_int_eq(strcmp(strings[3], strings[4]),
                   s21_strcmp(strings[3], strings[4]));
  ck_assert_int_eq(strcmp(strings[5], strings[6]),
                   s21_strcmp(strings[5], strings[6]));
  ck_assert_int_eq(strcmp(strings[7], strings[6]),
                   s21_strcmp(strings[7], strings[6]));
}
END_TEST

START_TEST(test_strncmp) {
  char *strings[] = {
      "",
      "6753",
      "6734",
      "oireub ejenrgi",
      "oiggreub ejenrgi",
      "ernv\0 ergerw",
      "ernv ergerw",
      "394fn43 43punf\n9034 i2 f0u94585\t9n54rij vi04389j3-21ieopn2v"};
  ck_assert_int_eq(strncmp(strings[1], strings[2], 4),
                   s21_strncmp(strings[1], strings[2], 4));
  ck_assert_int_eq(strncmp(strings[0], strings[1], 3),
                   s21_strncmp(strings[0], strings[1], 3));
  ck_assert_int_eq(strncmp(strings[1], strings[2], 2),
                   s21_strncmp(strings[1], strings[2], 2));
  ck_assert_int_eq(strncmp(strings[1], strings[2], 0),
                   s21_strncmp(strings[1], strings[2], 0));
  ck_assert_int_eq(strncmp(strings[3], strings[4], 10),
                   s21_strncmp(strings[3], strings[4], 10));
  ck_assert_int_eq(strncmp(strings[5], strings[6], 5),
                   s21_strncmp(strings[5], strings[6], 5));
  ck_assert_int_eq(strncmp(strings[7], strings[6], 1),
                   s21_strncmp(strings[7], strings[6], 1));
}
END_TEST

START_TEST(test_strstr) {
  char *patt[] = {"qwertyadl34 ", " 76vqw erty", " 743qwertyQWERTY",
                  "EHMqwerty,B NVH", "7823"};
  char *needles[] = {"qwerty", " ", "q", "y", ""};
  char *strings[] = {
      "34909u544566734sdtg4r",
      "6734",
      "ejenrgi",
      "oiggreub ejenrgi",
      "ernv\0 ergerw",
      "ergerw",
      "394fn43 43punf\n9034 i2 f0u94585\t9n54rij vi04389j3-21ieopn2v"};
  for (int i = 0; i < 5; i++) {
    for (int k = 0; k < 5; k++) {
      ck_assert_ptr_eq(strstr(patt[i], needles[k]),
                       s21_strstr(patt[i], needles[k]));
      ck_assert_ptr_eq(strstr(needles[k], patt[i]),
                       s21_strstr(needles[k], patt[i]));
    }
  }
  ck_assert_ptr_eq(strstr(strings[1], strings[0]),
                   s21_strstr(strings[1], strings[0]));
  ck_assert_ptr_eq(strstr(strings[2], strings[3]),
                   s21_strstr(strings[2], strings[3]));
  ck_assert_ptr_eq(strstr(strings[5], strings[4]),
                   s21_strstr(strings[5], strings[4]));
  ck_assert_ptr_eq(strstr(strings[0], strings[6]),
                   s21_strstr(strings[0], strings[6]));
}
END_TEST

START_TEST(test_strerror) {
  for (int i = 0; i <= N + 10; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(test_strcat) {
  char str11[10] = "6753";
  char str21[10] = "6734";
  char str12[10] = "6753";
  char str22[10] = "6734";
  char str31[130] = "oireub ejenrgi";
  char str41[130] = "oiggreub ejenrgi";
  char str32[130] = "oireub ejenrgi";
  char str42[130] = "oiggreub ejenrgi";
  char str51[130] = "ernv\0 ergerw";
  char str61[130] = "ernv ergerw";
  char str52[130] = "ernv\0 ergerw";
  char str62[130] = "ernv ergerw";

  ck_assert_str_eq(strcat(str11, str21), s21_strcat(str12, str22));
  ck_assert_str_eq(strcat(str31, str41), s21_strcat(str32, str42));
  ck_assert_str_eq(strcat(str51, str61), s21_strcat(str52, str62));
  ck_assert_str_eq(strcat(str61, str51), s21_strcat(str62, str52));
}
END_TEST

START_TEST(test_strncat) {
  char str11[10] = "6753";
  char str21[10] = "6734";
  char str12[10] = "6753";
  char str22[10] = "6734";
  char str31[130] = "oireub ejenrgi";
  char str41[130] = "oiggreub ejenrgi";
  char str32[130] = "oireub ejenrgi";
  char str42[130] = "oiggreub ejenrgi";
  char str51[130] = "ernv\0 ergerw";
  char str61[130] = "ernv ergerw";
  char str52[130] = "ernv\0 ergerw";
  char str62[130] = "ernv ergerw";

  ck_assert_str_eq(strncat(str11, str21, 2), s21_strncat(str12, str22, 2));
  ck_assert_str_eq(strncat(str31, str41, 5), s21_strncat(str32, str42, 5));
  ck_assert_str_eq(strncat(str51, str61, 4), s21_strncat(str52, str62, 4));
  ck_assert_str_eq(strncat(str61, str51, 100), s21_strncat(str62, str52, 100));
}
END_TEST

START_TEST(test_strcpy) {
  char str11[10] = "6753";
  char str21[10] = "6734";
  char str12[10] = "6753";
  char str22[10] = "6734";
  char str31[130] = "oireub ejenrgi";
  char str41[130] = "oiggreub ejenrgi";
  char str32[130] = "oireub ejenrgi";
  char str42[130] = "oiggreub ejenrgi";
  char str51[130] = "ernv\0 ergerw";
  char str61[130] = "ernv ergerw";
  char str52[130] = "ernv\0 ergerw";
  char str62[130] = "ernv ergerw";
  char str7[10] = "";

  ck_assert_str_eq(strcpy(str11, str21), s21_strcpy(str12, str22));
  ck_assert_str_eq(strcpy(str31, str41), s21_strcpy(str32, str42));
  ck_assert_str_eq(strcpy(str51, str61), s21_strcpy(str52, str62));
  ck_assert_str_eq(strcpy(str61, str51), s21_strcpy(str62, str52));
  ck_assert_str_eq(strcpy(str11, str7), s21_strcpy(str11, str7));
}
END_TEST

START_TEST(test_strncpy) {
  char str11[10] = "6753";
  char str21[10] = "6734";
  char str12[10] = "6753";
  char str22[10] = "6734";
  char str31[130] = "oireub ejenrgi";
  char str41[130] = "oiggreub ejenrgi";
  char str32[130] = "oireub ejenrgi";
  char str42[130] = "oiggreub ejenrgi";
  char str51[130] = "ernv\0 ergerw";
  char str61[130] = "ernv ergerw";
  char str52[130] = "ernv\0 ergerw";
  char str62[130] = "ernv ergerw";
  char str7[10] = "";

  ck_assert_str_eq(strncpy(str11, str21, 3), s21_strncpy(str12, str22, 3));
  ck_assert_str_eq(strncpy(str11, str21, 5), s21_strncpy(str12, str22, 5));
  ck_assert_str_eq(strncpy(str31, str41 + 2, 11),
                   s21_strncpy(str32, str42 + 2, 11));
  ck_assert_str_eq(strncpy(str61, str51, 10), s21_strncpy(str62, str52, 10));
  ck_assert_str_eq(strncpy(str51, str61, 10), s21_strncpy(str52, str62, 10));
  ck_assert_str_eq(strncpy(str11, str7, 0), s21_strncpy(str11, str7, 0));
}
END_TEST

START_TEST(test_memcpy) {
  char str1[30] = "1232435465";
  char str2[30] = "pwek";
  char str3[30] = {'\0'};
  char str4[30] = "98\089";

  char str11[30] = "1232435465";
  char str12[30] = "pwek";
  char str13[30] = {'\0'};
  char str14[30] = "98\089";

  ck_assert_str_eq(memcpy(str3, str1, 4), s21_memcpy(str13, str11, 4));
  ck_assert_str_eq(memcpy(str1, str2 + 1, strlen(str2) + 1),
                   s21_memcpy(str11, str12 + 1, strlen(str12) + 1));
  ck_assert_str_eq(memcpy(str2, str4, 7), s21_memcpy(str12, str14, 7));
}
END_TEST

START_TEST(test_memmove) {
  char str1[30] = "1232435465";
  char str2[30] = "pwek";
  char str3[30] = {'\0'};
  char str4[30] = "98\089";

  char str11[30] = "1232435465";
  char str12[30] = "pwek";
  char str13[30] = {'\0'};
  char str14[30] = "98\089";

  ck_assert_str_eq(memmove(str3, str1 + 3, 4),
                   s21_memmove(str13, str11 + 3, 4));
  ck_assert_str_eq(memmove(str1 + 4, str2 + 1, strlen(str2) + 1),
                   s21_memmove(str11 + 4, str12 + 1, strlen(str2) + 1));
  ck_assert_str_eq(memmove(str2, str4, 7), s21_memmove(str12, str14, 7));
}
END_TEST

START_TEST(test_memchr) {
  char str1[30] = "1232435465";
  char str2[30] = "pwek";
  char str3[30] = {'\0'};
  char str4[30] = "98\0j9";
  char str5[30] = "54343878393674523795";
  char str6[30] = "uebiurn eknds";

  ck_assert_str_eq(memchr(str1, '5', 30), s21_memchr(str1, '5', 30));
  ck_assert_ptr_eq(memchr(str1, '5', 30), s21_memchr(str1, '5', 30));
  ck_assert_str_eq(memchr(str2, 'k', 4), s21_memchr(str2, 'k', 4));
  ck_assert_ptr_eq(memchr(str2, 'k', 4), s21_memchr(str2, 'k', 4));
  ck_assert_ptr_eq(memchr(str2, '\0', 4), s21_memchr(str2, '\0', 4));
  ck_assert_ptr_eq(memchr(str3, 'j', 7), s21_memchr(str3, 'j', 7));
  ck_assert_str_eq(memchr(str4, 'j', 7), s21_memchr(str4, 'j', 7));
  ck_assert_ptr_eq(memchr(str4, 'j', 7), s21_memchr(str4, 'j', 7));
  ck_assert_ptr_eq(memchr(str5, '8', 3), s21_memchr(str5, '8', 3));
  ck_assert_ptr_eq(memchr(str6, 'u', 3), s21_memchr(str6, 'u', 3));
  ck_assert_ptr_eq(memchr(str6, 'u', 3), s21_memchr(str6, 'u', 3));
  ck_assert_ptr_eq(memchr(str6, 'k', 100), s21_memchr(str6, 'k', 100));
  ck_assert_ptr_eq(memchr(str6, 'k', 100), s21_memchr(str6, 'k', 100));
}
END_TEST

START_TEST(test_strchr) {
  char str_1[10] = "\0";
  char str_2[50] = "Per aspera ad astra";
  char str_3[12] = "i am\nproger";
  char str_4[50] = " schhol213222432\0";
  char str_5[50] = " \n\0\0";
  char str_6[10] = " a\n\0";
  char str_7[10] = " a\n\0ui";
  char str_10[] = "Hello";

  ck_assert_str_eq(strchr(str_1, '\0'), s21_strchr(str_1, '\0'));
  ck_assert_str_eq(strchr(str_3, '\n'), s21_strchr(str_3, '\n'));
  ck_assert_str_eq(strchr(str_4, '2'), s21_strchr(str_4, '2'));
  ck_assert_str_eq(strchr(str_5, ' '), s21_strchr(str_5, ' '));
  ck_assert_str_eq(strchr(str_6, 'a'), s21_strchr(str_6, 'a'));
  ck_assert_ptr_eq(strchr(str_7, 'i'), s21_strchr(str_7, 'i'));
  ck_assert_ptr_eq(strchr(str_2, '7'), s21_strchr(str_2, '7'));
  ck_assert_str_eq(strchr(str_10, 'o'), s21_strchr(str_10, 'o'));
}
END_TEST

START_TEST(test_strrchr) {
  char str_1[10] = "\0";
  char str_2[50] = "Per aspera ad astra";
  char str_3[12] = "i am\nproger";
  char str_4[50] = " schhol213222432\0";
  char str_5[50] = " \n\0\0";
  char str_6[10] = " a\n\0";
  char str_7[10] = " a\n\0ui";
  char str_10[] = "Hello";

  ck_assert_str_eq(strrchr(str_1, '\0'), s21_strrchr(str_1, '\0'));
  ck_assert_str_eq(strrchr(str_3, 'r'), s21_strrchr(str_3, 'r'));
  ck_assert_str_eq(strrchr(str_4, '3'), s21_strrchr(str_4, '3'));
  ck_assert_str_eq(strrchr(str_5, ' '), s21_strrchr(str_5, ' '));
  ck_assert_str_eq(strrchr(str_6, 'a'), s21_strrchr(str_6, 'a'));
  ck_assert_ptr_eq(strrchr(str_7, 'i'), s21_strrchr(str_7, 'i'));
  ck_assert_ptr_eq(strrchr(str_2, '7'), s21_strrchr(str_2, '7'));
  ck_assert_str_eq(strrchr(str_10, 'o'), s21_strrchr(str_10, 'o'));
}
END_TEST

START_TEST(test_strspn) {
  char str1[30] = "12djdb [pow wp32435\n465";
  char str11[20] = "234pw";
  char str2[30] = "pwek";
  char str22[30] = "pwekd";
  char str3[30] = {'\0'};
  char str33[30] = "9vd";
  char str4[30] = "98\0j9";
  char str44[30] = "jio";
  char str5[50] = "4555544534545454545454454545455445";
  char str55[30] = "45";
  char str6[30] = "ue4b4iurn ek5nds";
  char str66[30] = "uue45";

  ck_assert_int_eq(strspn(str1, str11), s21_strspn(str1, str11));
  ck_assert_int_eq(strspn(str2, str22), s21_strspn(str2, str22));
  ck_assert_int_eq(strspn(str3, str33), s21_strspn(str3, str33));
  ck_assert_int_eq(strspn(str4, str44), s21_strspn(str4, str44));
  ck_assert_int_eq(strspn(str5, str55), s21_strspn(str5, str55));
  ck_assert_int_eq(strspn(str6, str66), s21_strspn(str6, str66));
}
END_TEST

START_TEST(test_strcspn) {
  char str1[30] = "12djdb [pow wp32435\n465";
  char str11[20] = "234pw";
  char str2[30] = "pwek";
  char str22[30] = "l";
  char str3[30] = {'\0'};
  char str33[30] = "9vd";
  char str4[30] = "98\0j9";
  char str44[30] = "jio";
  char str5[50] = "4555544534545454545454454545455445";
  char str55[30] = "f9";
  char str6[30] = "ue4b4iurn ek5nds";
  char str66[30] = "k93";

  ck_assert_int_eq(strcspn(str2, str22), s21_strcspn(str2, str22));
  ck_assert_int_eq(strcspn(str1, str11), s21_strcspn(str1, str11));
  ck_assert_int_eq(strcspn(str3, str33), s21_strcspn(str3, str33));
  ck_assert_int_eq(strcspn(str4, str44), s21_strcspn(str4, str44));
  ck_assert_int_eq(strcspn(str5, str55), s21_strcspn(str5, str55));
  ck_assert_int_eq(strcspn(str6, str66), s21_strcspn(str6, str66));
}
END_TEST

START_TEST(test_strpbrk) {
  char str1[30] = "12djdb [pow wp32435\n465";
  char str11[20] = "234pw";
  char str2[30] = "pwek";
  char str22[30] = "l";
  char str3[30] = {'\0'};
  char str33[30] = "9vd";
  char str4[30] = "98\0j9";
  char str44[30] = "ji8o";
  char str5[50] = "45555445345454545454544545345455445";
  char str55[30] = "3";
  char str6[40] = "ue4b4iurn ek5njeirwnpowkeqo-43ds";
  char str66[30] = "k93";

  ck_assert_ptr_eq(strpbrk(str2, str22), s21_strpbrk(str2, str22));
  ck_assert_ptr_eq(strpbrk(str1, str11), s21_strpbrk(str1, str11));
  ck_assert_str_eq(strpbrk(str1, str11), s21_strpbrk(str1, str11));
  ck_assert_ptr_eq(strpbrk(str3, str33), s21_strpbrk(str3, str33));
  ck_assert_ptr_eq(strpbrk(str4, str44), s21_strpbrk(str4, str44));
  ck_assert_ptr_eq(strpbrk(str5, str55), s21_strpbrk(str5, str55));
  ck_assert_str_eq(strpbrk(str5, str55), s21_strpbrk(str5, str55));
  ck_assert_ptr_eq(strpbrk(str6, str66), s21_strpbrk(str6, str66));
  ck_assert_str_eq(strpbrk(str6, str66), s21_strpbrk(str6, str66));
}
END_TEST

START_TEST(test_strtok) {
  char *p = NULL;
  char *p2 = s21_NULL;
  char str1[50] = "48-343-454-683-4gv43-9900.,v-343-0";
  char str12[50] = "48-343-454-683-4gv43-9900.,v-343-0";
  char str2[30] = "**********";
  char str22[30] = "**********";
  char str4[30] = "98\0j9\0w";
  char str44[30] = "98\0j9\0w";
  char str5[50] = "some sht - nso$dhj, wj.Nwoie - weo";
  char str55[50] = "some sht - nso$dhj, wj.Nwoie - weo";
  char str6[30] = "ue4b4iurn ek5nds";
  char str66[30] = "ue4b4iurn ek5nds";

  p = strtok(str1, "-");
  p2 = s21_strtok(str12, "-");
  while (p != NULL) {
    ck_assert_pstr_eq(p, p2);
    p = strtok(NULL, "-");
    p2 = s21_strtok(s21_NULL, "-");
  }

  p = strtok(str2, "*");
  p2 = s21_strtok(str22, "*");
  while (p != NULL) {
    ck_assert_pstr_eq(p, p2);
    p = strtok(NULL, "*");
    p2 = s21_strtok(s21_NULL, "*");
  }

  p = strtok(str4, "\0");
  p2 = s21_strtok(str44, "\0");
  while (p != NULL) {
    ck_assert_pstr_eq(p, p2);
    p = strtok(NULL, "\0");
    p2 = s21_strtok(s21_NULL, "\0");
  }

  p = strtok(str5, " -,$.");
  p2 = s21_strtok(str55, " -,$.");
  while (p != NULL) {
    ck_assert_pstr_eq(p, p2);
    p = strtok(NULL, " -,$.");
    p2 = s21_strtok(s21_NULL, " -,$.");
  }

  p = strtok(str6, "#");
  p2 = s21_strtok(str66, "#");
  while (p != NULL) {
    ck_assert_pstr_eq(p, p2);
    p = strtok(NULL, "#");
    p2 = s21_strtok(s21_NULL, "#");
  }
}
END_TEST

START_TEST(test_toupper) {
  ck_assert_str_eq("3ME-IMMNU-KINYBVYNIB-JUTCGKHYFUIJ",
                   s21_to_upper("3me-imMNU-kinybvyNIB-jUtCgKHyfuiJ"));
  ck_assert_str_eq("", s21_to_upper(""));
  ck_assert_str_eq("AAAAAAAAAAAAAA", s21_to_upper("AAAAAAAAAAAAAA"));
  ck_assert_str_eq("24534678909876\0 54-04743986 sfd",
                   s21_to_upper("24534678909876\0 sfd"));
  ck_assert_str_eq("ABCDEFGH", s21_to_upper("AbCdEfGh"));
  ck_assert_ptr_eq(NULL, s21_to_upper(s21_NULL));
}
END_TEST

START_TEST(test_tolower) {
  ck_assert_str_eq("3me-immnu-kinybvynib-jutcgkhyfuij",
                   s21_to_lower("3me-imMNU-kinybvyNIB-jUtCgKHyfuiJ"));
  ck_assert_str_eq("", s21_to_lower(""));
  ck_assert_str_eq("aaaaaaaaaaaaaa", s21_to_lower("AAAAAAAAAAAAAA"));
  ck_assert_str_eq("24534678909876\0 54-04743986 SFD",
                   s21_to_lower("24534678909876\0 SFD"));
  ck_assert_str_eq("abcdefgh", s21_to_lower("AbCdEfGh"));
  ck_assert_ptr_eq(NULL, s21_to_lower(s21_NULL));
}
END_TEST

START_TEST(test_insert) {
  ck_assert_str_eq("666999666", s21_insert("666666", "999", 3));
  ck_assert_str_eq("sfg-------", s21_insert("-------", "sfg", 0));
  ck_assert_str_eq("bc04394034627839y", s21_insert("bcy", "04394034627839", 2));
  ck_assert_str_eq("bcy04394034627839", s21_insert("bcy", "04394034627839", 3));
  ck_assert_str_eq("150\% string", s21_insert("150 string", "%", 3));
  ck_assert_ptr_eq(NULL, s21_insert(s21_NULL, "999", 3));
  ck_assert_ptr_eq(NULL, s21_insert("9r34", s21_NULL, 3));
  ck_assert_ptr_eq(NULL, s21_insert("9r34", "982", 67));
}
END_TEST

START_TEST(test_trim) {
  ck_assert_str_eq("666-090-666", s21_trim("-090-666-090-666-090-", "90-"));
  ck_assert_str_eq("6669-0666", s21_trim("6669-0666", ""));
  ck_assert_str_eq("bdolso;moivdk", s21_trim("bdolso;moivdk32+=", "+=23"));
  ck_assert_str_eq("+", s21_trim("-+", "-"));
  ck_assert_str_eq("9 0 3 9 4 8", s21_trim(" 9 0 3 9 4 8 ", " "));
  ck_assert_ptr_eq(NULL, s21_trim(s21_NULL, "999"));
}
END_TEST

START_TEST(test_simple_sprintf) {
  char str1[1024] = {'\0'};
  char str2[1024] = {'\0'};
  char *p = str1, *p2 = str2;
  ck_assert_int_eq(sprintf(str1, "KLer%c' Mah", 'k'),
                   s21_sprintf(str2, "KLer%c' Mah", 'k'));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%%' Mah"),
                   s21_sprintf(str2, "KLer%%' Mah"));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%s' Mah", "kus"),
                   s21_sprintf(str2, "KLer%s' Mah", "kus"));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%d' Mah", 67),
                   s21_sprintf(str2, "KLer%d' Mah", 67));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%d' Mah", -67),
                   s21_sprintf(str2, "KLer%d' Mah", -67));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%i' Mah", 67),
                   s21_sprintf(str2, "KLer%i' Mah", 67));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%u' Mah", 67),
                   s21_sprintf(str2, "KLer%u' Mah", 67));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%f' Mah", 7.878),
                   s21_sprintf(str2, "KLer%f' Mah", 7.878));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%f' Mah", 4.7),
                   s21_sprintf(str2, "KLer%f' Mah", 4.7));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%f' Mah", 4.0003),
                   s21_sprintf(str2, "KLer%f' Mah", 4.0003));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(
      sprintf(str1, "KLer%d' Mah %c uh %s lw %f", 67, '$', "tyur we", 7.2),
      s21_sprintf(str2, "KLer%d' Mah %c uh %s lw %f", 67, '$', "tyur we", 7.2));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
}
END_TEST

START_TEST(test_part1_sprintf) {
  char str1[1024] = {'\0'};
  char str2[1024] = {'\0'};
  char *p = str1, *p2 = str2;
  ck_assert_int_eq(sprintf(str1, "KLer%+8.6i' Mah", 9),
                   s21_sprintf(str2, "KLer%+8.6i' Mah", 9));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%-6c' Mah", 78),
                   s21_sprintf(str2, "KLer%-6c' Mah", 78));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%-23c' Mah", 'k'),
                   s21_sprintf(str2, "KLer%-23c' Mah", 'k'));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%3c' Mah", 'k'),
                   s21_sprintf(str2, "KLer%3c' Mah", 'k'));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%3s' Mah", "y3b92 31098 \n 34"),
                   s21_sprintf(str2, "KLer%3s' Mah", "y3b92 31098 \n 34"));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%13.4s'  %-4s Mah", "nba", "89"),
                   s21_sprintf(str2, "KLer%13.4s'  %-4s Mah", "nba", "89"));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  ck_assert_int_eq(
      sprintf(str1, "KLer%13.4s'  %-4s Mah", "nbanbanbanba", "89"),
      s21_sprintf(str2, "KLer%13.4s'  %-4s Mah", "nbanbanbanba", "89"));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  short xxx = -64;
  ck_assert_int_eq(sprintf(str1, "KLer%-5.0hd' Mah", xxx),
                   s21_sprintf(str2, "KLer%-5.0hd' Mah", xxx));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  ck_assert_int_eq(sprintf(str1, "KLer%+5.0hd' Mah", 84846734),
                   s21_sprintf(str2, "KLer%+5.0hd' Mah", 84846734));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  sprintf(str1, "KLer%-+15.0ld' Mah", 1234567890123456789);
  s21_sprintf(str2, "KLer%-+15.0ld' Mah", 1234567890123456789);
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  long long ttt = 1234567890123456789;

  sprintf(str1, "KLer%-+15.0lld' Mah", ttt);
  s21_sprintf(str2, "KLer%-+15.0lld' Mah", ttt);
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  ck_assert_int_eq(sprintf(str1, "KLer%+.7d' Mah", 67),
                   s21_sprintf(str2, "KLer%+.7d' Mah", 67));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%+.7d' Mah", 'b'),
                   s21_sprintf(str2, "KLer%+.7d' Mah", 'b'));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%-10.1f' Mah", 9.37),
                   s21_sprintf(str2, "KLer%-10.1f' Mah", 9.37));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%+.3f' Mah", 67.),
                   s21_sprintf(str2, "KLer%+.3f' Mah", 67.));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%+10.1f' Mah", -9.33),
                   s21_sprintf(str2, "KLer%+10.1f' Mah", -9.33));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%+0.0f' Mah", 9.9999),
                   s21_sprintf(str2, "KLer%+0.0f' Mah", 9.9999));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%.0f'%.0f Mah", 7.8, 7.3),
                   s21_sprintf(str2, "KLer%.0f'%.0f Mah", 7.8, 7.3));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer% 2.7d' Mah", 67),
                   s21_sprintf(str2, "KLer% 2.7d' Mah", 67));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  for (double i = 0.0; i < 4.0; i += 0.00001) {
    ck_assert_int_eq(sprintf(str1, "%f", i), s21_sprintf(str2, "%f", i));
    ck_assert_str_eq(str1, str2);
    clear_buffs(&p, &p2);
  }
}
END_TEST
START_TEST(test_part2_sprintf) {
  char str1[1024] = {'\0'};
  char str2[1024] = {'\0'};
  char *p = str1, *p2 = str2;
  ck_assert_int_eq(sprintf(str1, "KLer%010d' Mah", 342),
                   s21_sprintf(str2, "KLer%010d' Mah", 342));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%#o'%o Mah", 956, -56),
                   s21_sprintf(str2, "KLer%#o'%o Mah", 956, -56));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  long double lf = 2. / 3.;
  ck_assert_int_eq(sprintf(str1, "KLer%Lf' Mah", lf),
                   s21_sprintf(str2, "KLer%Lf' Mah", lf));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  long double lf2 = 1. / 6.;
  ck_assert_int_eq(sprintf(str1, "KLer%+10.8Lf' Mah", lf2),
                   s21_sprintf(str2, "KLer%+10.8Lf' Mah", lf2));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  int io, io2;
  ck_assert_int_eq(sprintf(str1, "KLer%n' Mah", &io),
                   s21_sprintf(str2, "KLer%n' Mah", &io2));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(io, io2);
  clear_buffs(&p, &p2);

  ck_assert_int_eq(sprintf(str1, "KLer%p' Mah", &io),
                   s21_sprintf(str2, "KLer%p' Mah", &io));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  ck_assert_int_eq(sprintf(str1, "KLer%#x' %x Mah", 255, -2423),
                   s21_sprintf(str2, "KLer%#x' %x Mah", 255, -2423));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%#X' Mah", 255),
                   s21_sprintf(str2, "KLer%#X' Mah", 255));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%.4e' Mah", 67e-10),
                   s21_sprintf(str2, "KLer%.4e' Mah", 67e-10));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%#.0e' Mah", 67e-10),
                   s21_sprintf(str2, "KLer%#.0e' Mah", 67e-10));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  long double xyz = 67e-10;
  ck_assert_int_eq(sprintf(str1, "KLer%#.0Le' Mah", xyz),
                   s21_sprintf(str2, "KLer%#.0Le' Mah", xyz));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%.7E' Mah", 453e+7),
                   s21_sprintf(str2, "KLer%.7E' Mah", 453e+7));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%g' Mah", 0.345),
                   s21_sprintf(str2, "KLer%g' Mah", 0.345));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%Lg' Mah", xyz),
                   s21_sprintf(str2, "KLer%Lg' Mah", xyz));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "%g %G", 7671e+7, 78e+10),
                   s21_sprintf(str2, "%g %G", 7671e+7, 78e+10));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);

  ck_assert_int_eq(sprintf(str1, "%G", 78e+10),
                   s21_sprintf(str2, "%G", 78e+10));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(
      sprintf(str1, "%.0g %.0g %.6g %G", 7.0, 7671e+7, 187e-4, 78e+10),
      s21_sprintf(str2, "%.0g %.0g %.6g %G", 7.0, 7671e+7, 187e-4, 78e+10));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%#.0f' Mah", 3.2),
                   s21_sprintf(str2, "KLer%#.0f' Mah", 3.2));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%010f' Mah", 3.2),
                   s21_sprintf(str2, "KLer%010f' Mah", 3.2));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%*.*d' Mah", 7, 3, 24),
                   s21_sprintf(str2, "KLer%*.*d' Mah", 7, 3, 24));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
  ck_assert_int_eq(sprintf(str1, "KLer%*.*d' Mah", -7, 3, 24),
                   s21_sprintf(str2, "KLer%*.*d' Mah", -7, 3, 24));
  ck_assert_str_eq(str1, str2);
  clear_buffs(&p, &p2);
}
END_TEST

Suite *string_suite(void) {
  Suite *s = suite_create("String_testcase");
  TCase *tc_string = tcase_create("Core");

  suite_add_tcase(s, tc_string);
  tcase_add_test(tc_string, test_strlen);
  tcase_add_test(tc_string, test_memset);
  tcase_add_test(tc_string, test_memcmp);
  tcase_add_test(tc_string, test_memcpy);
  tcase_add_test(tc_string, test_memmove);
  tcase_add_test(tc_string, test_memchr);
  tcase_add_test(tc_string, test_strcmp);
  tcase_add_test(tc_string, test_strncmp);
  tcase_add_test(tc_string, test_strstr);
  tcase_add_test(tc_string, test_strerror);
  tcase_add_test(tc_string, test_strcat);
  tcase_add_test(tc_string, test_strncat);
  tcase_add_test(tc_string, test_strcpy);
  tcase_add_test(tc_string, test_strncpy);
  tcase_add_test(tc_string, test_strchr);
  tcase_add_test(tc_string, test_strrchr);
  tcase_add_test(tc_string, test_strspn);
  tcase_add_test(tc_string, test_strcspn);
  tcase_add_test(tc_string, test_strpbrk);
  tcase_add_test(tc_string, test_strtok);
  tcase_add_test(tc_string, test_toupper);
  tcase_add_test(tc_string, test_tolower);
  tcase_add_test(tc_string, test_insert);
  tcase_add_test(tc_string, test_trim);
  tcase_add_test(tc_string, test_simple_sprintf);
  tcase_add_test(tc_string, test_part1_sprintf);
  tcase_add_test(tc_string, test_part2_sprintf);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = string_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
