#include "s21_string.h"

// SPRINTF

int s21_sprintf(char *str, const char *format, ...) {
  s21_size_t i = 0, count = 0;
  char *str_val = s21_NULL;
  va_list ap;
  va_start(ap, format);
  while (format[i] != '\0') {
    if (format[i] != '%') {
      str[count++] = format[i++];
      continue;
    }
    Format form = {0, 0, 0, 0, 0, 0, -1, '\0', '\0', 0, 0, '\0', 0};
    i++;
    if (format[i] == '\0') return -1;
    if (format[i] == '%') {
      str[count++] = format[i++];
      continue;
    }
    while (format[i] && format[i] == ' ' && format[i + 1] == ' ') i++;
    s21_parse_flags(format, &i, &form);
    s21_parse_width(&ap, format, &i, &form);
    s21_parse_accuracy(&ap, format, &i, &form);
    s21_parse_length(format, &i, &form);
    form.spec = format[i];
    str_val = s21_switch_spec(&ap, count, &form);
    s21_process_flags(str_val, &form);
    s21_strcpy(&str[count], str_val);
    count += s21_strlen(str_val);
    if (str_val) free(str_val);
    str_val = s21_NULL;
    i++;
  }
  va_end(ap);
  str[count] = '\0';
  return count;
}

// SPRINTF FUNCTIONS

int s21_parse_flags(const char *format, s21_size_t *i, Format *form) {
  while (s21_strchr("# +-0", format[*i]) != s21_NULL && format[*i]) {
    if (format[*i] == '#' && form->flag_r == 0)
      form->flag_r = 1;
    else if (format[*i] == ' ' && form->flag_s == 0)
      form->flag_s = 1;
    else if (format[*i] == '+' && form->flag_p == 0)
      form->flag_p = 1;
    else if (format[*i] == '-' && form->flag_m == 0)
      form->flag_m = 1;
    else if (format[*i] == '0' && form->flag_z == 0)
      form->flag_z = 1;
    (*i)++;
  }
  return 0;
}

int s21_parse_width(va_list *ap, const char *format, s21_size_t *i,
                    Format *form) {
  if (s21_strchr("-0123456789", format[*i]) != s21_NULL) {
    if (format[*i] == '-') (*i)++;
    while (s21_strchr("-0123456789", format[*i]) != s21_NULL) {
      form->width = form->width * 10 + ((int)format[*i] - '0');
      (*i)++;
    }
  } else if (format[*i] == '*') {
    form->width = va_arg(*ap, int);
    if (form->width < 0) {
      form->width = -form->width;
      form->flag_m = 1;
    }
    (*i)++;
  }
  return 0;
}

int s21_parse_accuracy(va_list *ap, const char *format, s21_size_t *i,
                       Format *form) {
  if (format[*i] == '.') {
    (*i)++;
    if (s21_strchr("0123456789", format[*i]) != s21_NULL) {
      form->accuracy = 0;
      while (s21_strchr("0123456789", format[*i]) != s21_NULL) {
        form->accuracy = form->accuracy * 10 + ((int)format[*i] - '0');
        (*i)++;
      }
    } else if (format[*i] == '*') {
      form->accuracy = va_arg(*ap, int);
      if (form->accuracy < 0) form->accuracy = 6;
      (*i)++;
    } else {
      form->accuracy = 0;
    }
  }
  return 0;
}

int s21_parse_length(const char *format, s21_size_t *i, Format *form) {
  if (s21_strchr("hlL", format[*i]) != s21_NULL) {
    form->length = format[*i];
    (*i)++;
    if (s21_strchr("hlL", format[*i]) != s21_NULL) {
      form->length2 = format[*i];
      (*i)++;
    }
  }
  return 0;
}

char *s21_switch_spec(va_list *ap, s21_size_t j, Format *form) {
  char *res = s21_NULL;
  switch (form->spec) {
    case 'n': {
      res = s21_process_spec_n(ap, j);
      break;
    }
    case 'i':
    case 'd': {
      res = s21_process_spec_id(ap, form);
      break;
    }
    case 'X':
    case 'x':
    case 'u':
    case 'o': {
      res = s21_process_spec_xuo(ap, form);
      break;
    }
    case 'p': {
      res = s21_process_spec_p(ap, form);
      break;
    }
    case 'f': {
      res = s21_process_spec_f(ap, form);
      break;
    }
    case 'E':
    case 'e': {
      res = s21_process_spec_e(ap, form);
      break;
    }
    case 'G':
    case 'g': {
      res = s21_process_spec_g(ap, form);
      break;
    }
    case 'c': {
      res = s21_process_spec_c(ap, form);
      break;
    }
    case 's': {
      res = s21_process_spec_s(ap, form);
      break;
    }
    default:
      break;
  }
  return res;
}

char *s21_process_spec_n(va_list *ap, s21_size_t j) {
  int *n = va_arg(*ap, int *);
  *n = j;
  char *res = calloc(1, sizeof(char));
  return res;
}

char *s21_process_spec_id(va_list *ap, Format *form) {
  int base = 10;
  char *res = s21_NULL;
  if (form->length == 'h' && form->length2 != 'h')
    res = s21_itoa((short)va_arg(*ap, int), base, form);
  else if (form->length == 'h' && form->length2 == 'h')
    res = s21_itoa((signed char)va_arg(*ap, int), base, form);
  else if (form->length == 'l' && form->length2 != 'l')
    res = s21_itoa(va_arg(*ap, long int), base, form);
  else if (form->length == 'l' && form->length2 == 'l')
    res = s21_itoa(va_arg(*ap, long long int), base, form);
  else
    res = s21_itoa(va_arg(*ap, int), base, form);
  return res;
}

char *s21_process_spec_xuo(va_list *ap, Format *form) {
  form->unsign = 1;
  char *res = s21_NULL;
  int base = 10;
  if (form->spec == 'x' || form->spec == 'X') base = 16;
  if (form->spec == 'o') base = 8;
  if (form->length == 'h' && form->length2 != 'h')
    res = s21_itoa((unsigned short)va_arg(*ap, int), base, form);
  else if (form->length == 'h' && form->length2 == 'h')
    res = s21_itoa((unsigned char)va_arg(*ap, int), base, form);
  else if (form->length == 'l' && form->length2 != 'l')
    res = s21_itoa(va_arg(*ap, unsigned long), base, form);
  else if (form->length == 'l' && form->length2 == 'l')
    res = s21_itoa(va_arg(*ap, unsigned long long), base, form);
  else
    res = s21_itoa(va_arg(*ap, unsigned int), base, form);
  return res;
}

char *s21_process_spec_p(va_list *ap, Format *form) {
  char *res = s21_NULL;
  form->flag_r = 1;
  res = s21_itoa(va_arg(*ap, unsigned long long int), 16, form);
  return res;
}

char *s21_process_spec_f(va_list *ap, Format *form) {
  char *res = s21_NULL;
  if (form->accuracy < 0) form->accuracy = 6;
  if (form->length == 'L')
    res = s21_ftoa(va_arg(*ap, long double), form->accuracy, form);
  else
    res = s21_ftoa(va_arg(*ap, double), form->accuracy, form);
  return res;
}

char *s21_process_spec_e(va_list *ap, Format *form) {
  char *res = s21_NULL;
  if (form->accuracy == -1) form->accuracy = 6;
  if (form->length == 'L')
    res = s21_ftoexp(va_arg(*ap, long double), form);
  else
    res = s21_ftoexp(va_arg(*ap, double), form);
  return res;
}

char *s21_process_spec_g(va_list *ap, Format *form) {
  char *res = s21_NULL;
  if (form->accuracy == -1) form->accuracy = 6;
  if (form->length == 'L')
    res = s21_ftog(va_arg(*ap, long double), form);
  else
    res = s21_ftog(va_arg(*ap, double), form);
  return res;
}

char *s21_process_spec_c(va_list *ap, Format *form) {
  char *res = s21_NULL;
  int c = va_arg(*ap, int);
  int bytes = ((c >> 16 > 0) ? 4 : (c >> 12 > 0) ? 3 : (c >> 8 > 0) ? 2 : 1);
  res = calloc(abs(form->width) + bytes + 1, sizeof(char));
  res[0] = c;
  return res;
}

char *s21_process_spec_s(va_list *ap, Format *form) {
  char *res = s21_NULL;
  char *tmp = va_arg(*ap, char *);
  int len_dif = 0;
  int acc = (int)s21_strlen(tmp);
  if (form->accuracy > 0 && ((int)s21_strlen(tmp) - form->accuracy > 0)) {
    len_dif = (int)s21_strlen(tmp) - form->accuracy;
    acc = form->accuracy;
  }
  res = calloc((int)s21_strlen(tmp) - len_dif + form->width + 1, sizeof(char));
  int k = 0;
  while (tmp[k] != '\0' && k < acc) {
    res[k] = tmp[k];
    k++;
  }
  res[k] = '\0';

  return res;
}

void s21_reverse(char str[], int len) {
  int start, end;
  char temp;
  for (start = 0, end = len - 1; start < end; start++, end--) {
    temp = *(str + start);
    *(str + start) = *(str + end);
    *(str + end) = temp;
  }
}

long long s21_atoi(char *str) {
  long long res = 0;
  for (int i = 0; str[i] != '\0'; ++i) {
    res = res * 10 + str[i] - '0';
  }
  return res;
}

void s21_process_flags(char *str, Format *form) {
  int len = s21_strlen(str);
  int i = len;
  int width = form->width;
  char c = ' ';
  s21_reverse(str, len);
  if (form->flag_z == 0) {
    if (form->flag_s == 1 || form->flag_p == 1 || form->flag_m == 1) {
      if (form->flag_p == 1 && form->spec != 'u' && form->spec != 'c' &&
          form->spec != 's' && form->spec != 'x' && form->spec != 'X' &&
          form->spec != 'o' && form->is_negative == 0) {
        str[i++] = '+';
      }
    }
    if (form->is_negative == 1) str[i++] = '-';
  }
  if (form->flag_z == 1) c = '0';
  if (form->flag_r == 1) {
    if (form->spec == 'p' && s21_atoi(str) == 0) {
      i = 0;
      str[i++] = '0';
      str[i++] = 'x';
      str[i++] = '0';
    } else if ((form->spec == 'x' || form->spec == 'p') && s21_atoi(str) != 0) {
      str[i++] = 'x';
      str[i++] = '0';
      width -= 2;
    } else if (form->spec == 'X' && s21_atoi(str) != 0) {
      str[i++] = 'X';
      str[i++] = '0';
      width -= 2;
    } else if (form->spec == 'o') {
      if (str[i - 1] != '0') {
        str[i++] = '0';
        width -= 1;
      }
    }
    str[i] = '\0';
  }
  if (form->unsign == 1) form->is_negative = 0;
  if ((form->is_negative == 1 || form->flag_p == 1) && form->spec != 's' &&
      form->spec != 'c' && form->spec != 'u') {
    width = width - len - 1;
  } else {
    width -= len;
  }
  if (form->flag_m == 0 && width > 0) {
    while (width > 0) {
      if (width == 1 && form->flag_s == 1 && form->flag_z == 1)
        str[i++] = ' ';
      else
        str[i++] = c;
      width--;
    }
  } else if (width <= 0 && form->flag_s == 1 && form->is_negative == 0 &&
             form->flag_p == 0 && form->spec != 'c' && form->spec != 's' &&
             form->spec != 'u') {
    str[i++] = ' ';
  }
  if (form->flag_z == 1) {
    if (form->flag_s == 1 || form->flag_p == 1 || form->flag_m == 1) {
      if (form->flag_p == 1 && form->spec != 'u' && form->spec != 'c' &&
          form->spec != 's' && form->is_negative == 0)
        str[i++] = '+';
    }
    if (form->is_negative == 1) str[i++] = '-';
  }
  str[i] = '\0';
  s21_reverse(str, i);
  if (form->flag_m == 1) {
    while (width > 0) {
      str[i++] = c;
      width--;
    }
  }
  str[i] = '\0';
}

char *s21_itoa(long long num, int base, Format *form) {
  int i = 0;
  int flag = 0;
  s21_size_t temp_num = num;
  char upper_letter = (form->spec == 'X') ? 'A' : 'a';
  char *temp_str = calloc(BUFFERSIZE, sizeof(char));
  if (temp_num == 0) {
    if (form->accuracy == 0 && form->spec != 'f') {
      temp_str[i] = '\0';
      flag = 1;

    } else if (form->spec == 'g' || form->spec == 'G') {
      temp_str[i] = '0';
      temp_str[i + 1] = '\0';
      flag = 2;
    }
  }
  if (!flag) {
    if (num < 0 && base == 10 && form->float_part == 0) {
      form->is_negative = 1;
      if (form->unsign == 0) temp_num = -num;
    }
    while (temp_num) {
      int rem = temp_num % base;
      temp_str[i++] = (rem > 9) ? (rem - 10) + upper_letter : rem + '0';
      temp_num /= base;
    }

    //  точность для 16 и 8-ричных систем счислений заполняется нулями
    if (s21_strchr("xXouid", form->spec) != s21_NULL) {
      int acc = form->accuracy;
      if (acc > 0) acc -= (int)s21_strlen(temp_str);
      while (acc > 0) {
        temp_str[i++] = '0';
        acc--;
      }
      if (s21_strchr("xXo", form->spec) != s21_NULL) form->flag_z = 0;
    }
    if (num == 0 && form->spec == 'f') temp_str[i++] = '0';
    temp_str[i] = '\0';
    s21_reverse(temp_str, i);
  }
  return temp_str;
}

char *s21_ftoa(long double f, int acc, Format *form) {
  int accuracy = acc;
  char *str = s21_NULL, *part = s21_NULL;
  long long int int_part;
  if (acc > 0) f = roundl(f * pow(10, acc)) / pow(10, acc);
  if (signbit(f)) {
    form->is_negative = 1;
    f = -f;
  }
  if (acc > 0)
    int_part = (long long int)(f + EPSILON_VALUE);
  else
    int_part = (long long int)(roundl(f) + EPSILON_VALUE);
  long double float_part = f - (long double)int_part;
  if (float_part < 0) {
    float_part = -float_part;
  }
  str = s21_itoa(int_part, 10, form);
  s21_size_t len = s21_strlen(str);
  if (acc == 0 && form->flag_r == 1) str[len] = '.';
  if (acc > 0) {
    str[len] = '.';
    long long int temp_itoa = 0;
    while (accuracy > 0) {
      float_part *= 10;
      accuracy--;
    }
    temp_itoa = (long long int)(float_part + 0.5f);
    part = s21_itoa(temp_itoa, 10, form);
    int part_len = (int)s21_strlen(part);
    int i = part_len;
    s21_reverse(part, part_len);
    accuracy = acc - part_len;
    while (accuracy > 0) {
      part[i++] = '0';
      accuracy--;
    }
    part[i] = '\0';
    s21_reverse(part, i);
    form->float_part = 0;
    s21_strcpy(&str[++len], part);
    free(part);
  }

  return str;
}

void s21_delete_zero(char *str) {
  int size_str = s21_strlen(str);
  if (size_str > 0) {
    while (str[size_str - 1] == '0' || str[size_str - 1] == '.') {
      char c = str[size_str - 1];
      str[size_str - 1] = '\0';
      size_str--;
      if ((size_str == 0) || c == '.' || (size_str == 1 && str[0] == '0'))
        break;
    }
  }
}

char *s21_ftoexp(long double f, Format *form) {
  char *str = s21_NULL;
  long double temp = (long double)f;
  s21_size_t i = 0;
  long long int int_part = 0;
  int e = 0;
  if (signbit(temp)) {
    temp = -temp;
    form->is_negative = 1;
  }
  while (temp > 0) {
    int_part = (long long int)(temp + EPSILON_VALUE);
    if ((int_part > 0 && int_part < 10)) {
      break;
    } else if (int_part >= 10) {
      temp /= 10;
      e += 1;
    } else if (int_part == 0) {
      temp *= 10;
      e -= 1;
    }
  }
  Format s_temp = {form->flag_r, 0, 0, 0, 0, 0, -1, '\0', '\0', 0, 0, '\0', 0};
  int ifg = 0;
  str = s21_ftoa(temp, form->accuracy, &s_temp);
  if (form->spec == 'g') {
    if (form->flag_r == 0) s21_delete_zero(str);
    form->spec = 'e';
    ifg = 1;
  }
  if (form->spec == 'G') {
    if (form->flag_r == 0) s21_delete_zero(str);
    form->spec = 'E';
    ifg = 1;
  }
  if (e != 0 || ifg == 0) {
    i = s21_strlen(str);
    str[i++] = form->spec;
    if (e < 0)
      str[i++] = '-';
    else
      str[i++] = '+';
    char *tm = s21_itoa(e, 10, &s_temp);
    if (s21_strlen(tm) < 2) str[i++] = '0';
    s21_strcpy(&str[i], tm);
    free(tm);
  }

  return str;
}

char *s21_ftog(long double f, Format *form) {
  char *str = s21_NULL;
  long double temp = (long double)f;

  if (signbit(temp)) {
    temp = -temp;
    form->is_negative = 1;
  }
  double tmp = temp;
  if (tmp < 0) tmp = -tmp;
  int count_c = 0;
  if (tmp == 0) count_c = 1;
  while (tmp >= 1) {
    tmp = tmp / 10;
    count_c++;
  }
  int pos_right = count_c;
  while (temp < pow(10, pos_right) && temp != 0) pos_right--;
  if (count_c > form->accuracy || pos_right < -4) {
    if (form->accuracy > 0) form->accuracy--;
    str = s21_ftoexp(f, form);
  } else {
    if (pos_right < 0 && form->accuracy < abs(pos_right))
      form->accuracy = abs(pos_right);
    str = s21_ftoa(f, form->accuracy - count_c, form);
    if (form->flag_r == 0) s21_delete_zero(str);
  }

  return str;
}

void clear_buffs(char **buffer, char **buffer2) {
  for (int i = 0; i < 1024; i++) {
    (*buffer)[i] = (*buffer2)[i] = '\0';
  }
}
