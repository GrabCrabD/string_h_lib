#include "s21_string.h"

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

// COPY FUNCTIONS

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *tmp_dest = (char *)dest;
  const char *tmp_src = (const char *)src;
  if ((tmp_dest != s21_NULL) && (tmp_src != s21_NULL)) {
    while (n--) {
      *(tmp_dest++) = *(tmp_src++);
    }
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *tmp_dest = (char *)dest;
  const char *tmp_src = (const char *)src;
  char *buf = (char *)malloc(sizeof(char) * n);
  for (unsigned int i = 0; i < n; i++) {
    buf[i] = tmp_src[i];
  }
  for (unsigned int i = 0; i < n; i++) {
    tmp_dest[i] = buf[i];
  }
  free(buf);
  return dest;
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t len = s21_strlen(src);
  while (*src) {
    (*(char *)dest) = (*(char *)src);
    dest++;
    src++;
  }
  (*(char *)dest) = '\0';
  return dest - len;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n) {
    if ((*src)) {
      (*(char *)dest) = (*(char *)src);
      src++;
    } else {
      (*(char *)dest) = '\0';
    }
    dest++;
    i++;
  }
  return dest - i;
}

// CONCATENATION FUNCTIONS

char *s21_strcat(char *dest, const char *src) {
  s21_size_t len = s21_strlen(dest);
  s21_size_t i = 0 + len;
  for (; i < s21_strlen(src) + len; i++) {
    (*((char *)dest + i)) = (*((char *)src + i - len));
  }
  (*((char *)dest + i)) = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t len = s21_strlen(dest);
  s21_size_t i = 0 + len;
  for (; i < s21_strlen(src) + len && i - len < n; i++) {
    (*((char *)dest + i)) = (*((char *)src + i - len));
  }
  (*((char *)dest + i)) = '\0';
  return dest;
}

// COMPAIRSON FUNCTIONS

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  int diff = 0;
  for (; i < n && diff == 0; i++) {
    diff = (*((char *)str1 + i) - *((char *)str2 + i));
    if (n - i - 1 == 0) {
      result += diff;
    } else {
      result += (diff)*pow(sizeof(*(str1 + i)), (n - i - 1));
    }
  }
  return result;
}

int s21_strcmp(const char *str1, const char *str2) {
  int i = 0;
  int res = 0;
  while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0') {
    i++;
  }
  res = (int)(*(str1 + i) - *(str2 + i));

  return res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;
  int res = 0;
  while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0' && i < n) {
    i++;
  }
  if (i != n) {
    res = (int)(*(str1 + i) - *(str2 + i));
  }

  return res;
}

// SEARCH FUNCTIONS

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;
  unsigned char *finded_char = s21_NULL;
  while ((str != s21_NULL) && (n--)) {
    if (*p != (unsigned char)c) {
      p++;
    } else {
      finded_char = p;
      break;
    }
  }
  return finded_char;
}

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str) {
    if (*str == c) {
      result = (char *)str;
      break;
    }
    str++;
  }
  if (*str == c) {
    result = (char *)str;
  }
  return result;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  int flag = 0;
  if (str1 != s21_NULL || str2 != s21_NULL) {
    for (const char *i = str1; *i != '\0'; i++) {
      for (const char *j = str2; *j != '\0'; j++) {
        if (*i == *j) {
          flag = 1;
          break;
        }
      }
      if (flag) {
        break;
      }
      len++;
    }
  }
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *c = s21_NULL;
  int flag = 0;
  if (str1 != s21_NULL || str2 != s21_NULL) {
    for (const char *i = str1; *i != '\0'; i++) {
      for (const char *j = str2; *j != '\0'; j++) {
        if (*i == *j) {
          c = (char *)i;
          flag = 1;
          break;
        }
      }
      if (flag) {
        break;
      }
    }
  }
  return c;
}

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == c) {
      result = (char *)str;
    }
  }
  if (result == s21_NULL) {
    result = (char *)str;
  }
  return *result == c ? (char *)result : s21_NULL;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  int flag = 0;
  if (str1 != s21_NULL || str2 != s21_NULL) {
    for (const char *i = str1; *i != '\0'; i++) {
      for (const char *j = str2; *j != '\0'; j++) {
        if (*i == *j) {
          len++;
          flag = 1;
          break;
        }
      }
      if (flag == 0) {
        break;
      }
      flag = 0;
    }
  }
  return len;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *answer = s21_NULL;
  int pi[2048] = {'\0'};

  if (needle && haystack) {
    s21_size_t k, i, len = s21_strlen(needle);
    pi[0] = 0;
    for (i = 1; i < len; ++i) {
      int j = pi[i - 1];
      while ((j > 0) && (needle[i] != needle[j])) j = pi[j - 1];
      if (needle[i] == needle[j]) ++j;
      pi[i] = j;
    }

    for (k = 0, i = 0; haystack[k] && !answer; k++) {
      while ((i > 0) && (needle[i] != haystack[k])) i = pi[i];
      if (needle[i] == haystack[k]) ++i;
      if (i == len) {
        answer = (char *)haystack + k - len + 1;
      }
    }
    if (!s21_strcmp(needle, "")) answer = (char *)haystack;
  }
  return answer;
}

char *s21_strtok(char *str, const char *delim) {
  static char *answer, *ptr;
  s21_size_t i, len = s21_strlen(delim);
  int k;

  if (str) {
    answer = s21_NULL;
  } else if (ptr) {
    answer = s21_NULL;
    str = ptr;
  } else if (ptr == s21_NULL) {
    answer = s21_NULL;
  }

  if (str) {
    for (i = 0; !answer && str[i]; i++) {
      for (k = 0; k < (int)len && delim[k]; k++) {
        if (delim[k] == str[i]) {
          k = -1;
          break;
        }
      }
      if (k != -1) {
        answer = str + i;
      }
    }
  }

  if (answer) {
    for (ptr = answer; *ptr; ptr++) {
      for (k = 0; k < (int)len && delim[k]; k++) {
        if (delim[k] == *ptr) {
          k = -1;
          break;
        }
      }
      if (k == -1) {
        *ptr = 0;
        ++ptr;
        break;
      }
    }
    if (!*ptr) {
      ptr = s21_NULL;
    }
  }
  return answer;
}

// OTHER FUNCTIONS

void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    (*(char *)str) = c;
    str++;
  }
  return str - n;
}

char *s21_strerror(int errnum) {
  char *err_list[] = LIST_ERRORS;
  int flag;
  char *error;
  static char unknown_error[100] = {'\0'};

  if (errnum >= 0 && errnum <= N) {
    error = (char *)err_list[errnum];
    flag = 1;
  } else {
    s21_sprintf(unknown_error, "Unknown error: %d", errnum);
    flag = 0;
  }
  return (flag) ? error : unknown_error;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (*str) {
    len++;
    str++;
  }
  return len;
}

// C# FUNCTIONS

void *s21_to_upper(const char *str) {
  char *answer = s21_NULL;
  if (str) {
    answer = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    s21_strcpy(answer, str);
    for (int i = 0; i < 1024 && answer[i]; i++) {
      if (answer[i] >= 97 && answer[i] <= 122)
        answer[i] = (char)((int)answer[i] - 32);
    }
  }
  return answer;
}

void *s21_to_lower(const char *str) {
  char *answer = s21_NULL;
  if (str) {
    answer = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    s21_strcpy(answer, str);
    for (int i = 0; i < 1024 && answer[i]; i++) {
      if (answer[i] >= 65 && answer[i] <= 90)
        answer[i] = (char)((int)answer[i] + 32);
    }
  }
  return answer;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t i = 0;
  char *result = s21_NULL;
  if (src != s21_NULL && str != s21_NULL && s21_strlen(src) >= start_index) {
    result = calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    for (; i < s21_strlen(str) + s21_strlen(src); i++) {
      if (i < start_index) {
        result[i] = src[i];
      }
      if (i >= start_index && i < start_index + s21_strlen(str)) {
        result[i] = str[i - start_index];
      }
      if (i >= start_index + s21_strlen(str)) {
        result[i] = src[i - s21_strlen(str)];
      }
    }
  }
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) return s21_NULL;
  char def_trim_chars[1024];
  if (trim_chars != s21_NULL && s21_strlen(trim_chars) != 0)
    s21_strcpy(def_trim_chars, trim_chars);
  else
    s21_strcpy(def_trim_chars, "\t\n\v\r\f ");
  int len = s21_strlen(src);
  int newlength = len;
  char *srcfirst = (char *)src;
  char *srclast = (char *)src + len;
  if (len > 0) srclast--;
  while (s21_strchr(def_trim_chars, *srcfirst) && *srcfirst) {
    srcfirst++;
    newlength--;
  }
  while (s21_strchr(def_trim_chars, *srclast) && newlength > 0) {
    srclast--;
    newlength--;
  }
  char *newstr = malloc(sizeof(char) * (newlength + 1));
  if (newstr) {
    int i = 0;
    while (i < newlength) {
      newstr[i] = *srcfirst;
      srcfirst++;
      i++;
    }
    newstr[newlength] = '\0';
  }
  return newstr;
}
