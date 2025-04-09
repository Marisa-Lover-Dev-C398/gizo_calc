#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>
#include <ncursesw/ncurses.h>

#define INPUT_MAX 256


const char *input_expr;
int pos_expr = 0;

char peek() {
    return input_expr[pos_expr];
}

char get() {
    return input_expr[pos_expr++];
}

void skip_spaces() {
    while (peek() == ' ') get();
}

int parse_expression();

int parse_number() {
    skip_spaces();
    int result = 0;
    while (isdigit(peek())) {
        result = result * 10 + (get() - '0');
    }
    return result;
}

int parse_factor() {
    skip_spaces();
    if (peek() == '(') {
        get();
        int val = parse_expression();
        skip_spaces();
        get();
        return val;
    } else {
        return parse_number();
    }
}

int parse_term() {
    int result = parse_factor();
    skip_spaces();
    while (peek() == '*' || peek() == '/') {
        char op = get();
        int right = parse_factor();
        if (op == '*') result *= right;
        else result /= right;
        skip_spaces();
    }
    return result;
}

int parse_expression() {
    int result = parse_term();
    skip_spaces();
    while (peek() == '+' || peek() == '-') {
        char op = get();
        int right = parse_term();
        if (op == '+') result += right;
        else result -= right;
        skip_spaces();
    }
    return result;
}
int printstr(const char* str) {
    FILE *fp;
    char buf[256];
    wchar_t buf2[4096] = L"";
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "toilet \"%s\" -f mono12 -w 500", str);

    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        wchar_t wbuf[256];
        mbstowcs(wbuf, buf, sizeof(wbuf) / sizeof(wchar_t));
        wcscat(buf2, wbuf);
    }

    clear();
    mvaddwstr(1, 1, buf2);
    box(stdscr, 0, 0);
    refresh();
    pclose(fp);
    return 0;
}

int isoperator(char ch) {
    return strchr("+-*/()", ch) != NULL;
}

int main() {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    char result_str[32];
    char input[INPUT_MAX] = "";
    int pos = 0;
    int flag=0;
    int result;
    box(stdscr, 0, 0);

    refresh();

    int ch;
    while ((ch = getch()) != 'q') {
        if ((isdigit(ch) || isoperator(ch)) && pos < INPUT_MAX - 1 && flag!=1) {
            input[pos++] = ch;
            input[pos] = '\0';
        } else if(ch == '='){
           input_expr = input;
           pos_expr = 0;
           result = parse_expression();
           snprintf(result_str, sizeof(result_str), "=%d", result);
           strncat(input, result_str, INPUT_MAX - strlen(input) - 1);
           pos = strlen(input);
           flag = 1;
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (pos > 0) {
                pos--;
                input[pos] = '\0';
            }
        } else if (ch == 'c' || ch == 'C') {
            pos = 0;
            input[0] = '\0';
            flag=0;
        }

        printstr(input);
    }

    endwin();
    return 0;
}
