#ifndef HEX_DUMP_H
#define HEX_DUMP_H

/**
 * @brief hex dump with width of 32 with high light option
 * 
 * @param mem memory ptr
 * @param length length to be printed
 * @param highlight_start highlight start at this byte
 * @param highlight_length highlight length
 */
void hex_dump_highlight(const void *const mem, int length, int highlight_start, int highlight_length);

/**
 * @brief hex dump with width of 32
 * 
 * @param mem memory ptr
 * @param length length to be printed
 */
void hex_dump(const void *const mem, int length);

#endif