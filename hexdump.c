
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "hexdump.h"


#define CONSOLE_COLOR_WHITE     15
#define CONSOLE_COLOR_GRAY      7
#define CONSOLE_COLOR_GRAY2     8
#define CONSOLE_COLOR_BLACK     0

#define CONSOLE_COLOR_RED       9
#define CONSOLE_COLOR_RED2      196
#define CONSOLE_COLOR_RED3      160

#define CONSOLE_COLOR_CYAN      14
#define CONSOLE_COLOR_CYAN2     51

#define CONSOLE_COLOR_GREEN     10
#define CONSOLE_COLOR_GREEN2    40
#define CONSOLE_COLOR_GREEN3    82

#define CONSOLE_COLOR_YELLOW    11
#define CONSOLE_COLOR_YELLOW2   220
#define CONSOLE_COLOR_YELLOW3   226


#define COLORED_PRINTF(str, fg, bg ,...) do { \
                            printf(console_color_set(fg,bg));\
                            printf(str __VA_OPT__(,) __VA_ARGS__);\
                            printf(console_color_reset());\
                            } while(0)



static char *console_color_set(uint8_t fg, uint8_t bg)
{
    static char str[30] = {0};
    sprintf( str,"\033[38;5;%i;48;5;%im", fg, bg);
    return str;
}


static char *console_color_reset()
{
    return "\033[00m";
}



static void header(size_t WIDTH)
{
    printf("\r\n");
    // title
    COLORED_PRINTF("        ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    const char str[] = " ~~[ H3X DUMP V1.0 ]~~ ";
    size_t spaces = (WIDTH*3 - sizeof(str)) / 2;
    for (int i=0; i<spaces; i++)
        COLORED_PRINTF(" ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    COLORED_PRINTF("%s", CONSOLE_COLOR_GREEN3, CONSOLE_COLOR_GRAY2, str);
    for (int i=0; i<spaces+3; i++)
        COLORED_PRINTF(" ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    printf("\r\n");


    //columns
    COLORED_PRINTF("------  ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    for (int i=0; i<WIDTH; i++){
        COLORED_PRINTF("%02i ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2, i);
    }
    COLORED_PRINTF(" |", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    printf("\r\n");
}

static void footer(size_t WIDTH)
{
    COLORED_PRINTF("------| ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    for (int i=0; i<WIDTH; i++){
        COLORED_PRINTF("   ", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    }
    COLORED_PRINTF(" |", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    printf("\r\n");
}



static void printAddress(uint32_t address){
    COLORED_PRINTF("0x%04X|", CONSOLE_COLOR_RED, CONSOLE_COLOR_BLACK, address);
    printf(" ");
}

static void fillRestOfLine(size_t WIDTH, int pos){
    uint8_t tail = WIDTH - (pos % WIDTH);
    for (int j=0; j<tail; j++)
        printf("   ");
    COLORED_PRINTF(" |", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
    printf("\r\n");
}



void hex_dump(const void *const mem, int length)
{
    hex_dump_highlight(mem, length, 0, 0);
}

void hex_dump_highlight(const void *const mem, int length, int highlight_start, int highlight_length)
{
    
    if (length <= 0){
        return;
    }

    const uint8_t *memBuf = mem;
    const size_t WIDTH = 32U;
    header(WIDTH);

    for (int i=0; i<length; i++){
        //print address
        if (i % WIDTH == 0)
            printAddress(i);
        //print value
        if(highlight_length != 0 && (i >= highlight_start && i<= (highlight_length+highlight_start))){
            if (i != (highlight_length+highlight_start)){
                COLORED_PRINTF("%02X ",CONSOLE_COLOR_BLACK,CONSOLE_COLOR_YELLOW3, memBuf[i]);
            }else{
                COLORED_PRINTF("%02X",CONSOLE_COLOR_BLACK,CONSOLE_COLOR_YELLOW3, memBuf[i]);
                printf(" ");
            }
        }else{
            printf("%02X ", memBuf[i]);
        }

        //print border
        if (i % WIDTH == (WIDTH-1)){
            COLORED_PRINTF(" |", CONSOLE_COLOR_GREEN, CONSOLE_COLOR_GRAY2);
            printf("\r\n");
        }
    }
    if (length % WIDTH != 0){
        fillRestOfLine(WIDTH, length);
    }
    footer(WIDTH);
}