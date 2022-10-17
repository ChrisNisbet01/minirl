#pragma once

#include "minirl.h"
#include "buffer.h"
#include "key_binding.h"

#include <termios.h>

#define MINIRL_DEFAULT_HISTORY_MAX_LEN 100
#define MINIRL_MAX_LINE 4096

/* The minirlState structure represents the state during line editing.
 * We pass this state to functions implementing specific editing
 * functionalities. */
typedef struct row_col_st {
	int row;
	int col;
} row_col_st;


struct minirl_state
{
    struct buffer * line_buf;

    char const * prompt; /* Prompt to display. */
    size_t prompt_len;   /* Prompt length. */
    size_t pos;          /* Current cursor position. */
    size_t len;          /* Current edited line length. */

    size_t oldpos;       /* Previous refresh cursor position. */
    size_t cols;         /* Number of columns in terminal. */
    size_t maxrows;      /* Maximum num of rows used so far (multiline mode) */
    int history_index;   /* The history index we are currently editing. */

    row_col_st previous_cursor;
    row_col_st previous_line_end;
};

struct minirl_st
{
    struct
    {
        FILE * stream;
        int fd;
    } in;
    struct
    {
        FILE * stream;
        int fd;
    } out;

    bool is_a_tty;
    bool in_raw_mode;
    struct termios orig_termios;
    struct minirl_keymap * keymap;
    struct minirl_state state;

    struct
    {
        bool mask_mode;
        bool force_isatty;
    } options;

    struct
    {
        size_t max_len;
        size_t current_len;
        char ** history;
    } history;
};


