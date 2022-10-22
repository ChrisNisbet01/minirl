#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct minirl_st minirl_st;

typedef bool (*minirl_key_binding_handler_cb)(
	minirl_st *minirl, char const *key, void *user_ctx);


/*
 * Get the current pointer to the line buffer. Note that any changes made by
 * callbacks may result in this pointer becoming invalid, so it should be
 * reobtained after any modification.
 */
char *
minirl_line_get(minirl_st *minirl);

size_t
minirl_point_get(minirl_st *minirl);

size_t
minirl_end_get(minirl_st *minirl);

void
minirl_point_set(minirl_st *minirl, size_t new_point);

void
minirl_delete_text(minirl_st *minirl, size_t start, size_t end);

bool
minirl_insert_text_len(minirl_st *minirl, char const *text, size_t delta);

bool
minirl_insert_text(minirl_st *minirl, char const *text);

int
minirl_terminal_width(minirl_st *minirl);

bool minirl_complete(
	minirl_st *minirl,
	unsigned start,
	char **matches,
	bool allow_prefix);

void
minirl_display_matches(minirl_st *minirl, char **matches);

bool
minirl_bind_key(
	minirl_st *minirl,
	uint8_t key,
	minirl_key_binding_handler_cb handler,
	void *user_ctx);

bool
minirl_bind_keyseq(
	minirl_st *minirl,
	const char *seq,
	minirl_key_binding_handler_cb handler,
	void *context);

char *
minirl_readline(minirl_st *minirl, char const *prompt);

void
minirl_free(void *ptr);

int
minirl_history_add(minirl_st *minirl, char const *line);

int
minirl_history_set_max_len(minirl_st *minirl, size_t len);

void
minirl_clear_screen(minirl_st *minirl);

void
minirl_force_isatty(minirl_st *minirl);

struct minirl_st *
minirl_new(FILE *in_stream, FILE *out_stream);

void
minirl_delete(minirl_st *minirl);

int
minirl_printf(minirl_st *minirl, char const * fmt, ...);

void
minirl_is_done(minirl_st *minirl);

void
minirl_requires_refresh(minirl_st *minirl);

void
minirl_requires_cursor_refresh(minirl_st *minirl);

void
minirl_had_error(minirl_st *minirl);

void
minirl_reset_line_state(minirl_st *minirl);

void
minirl_enable_echo(minirl_st *minirl);

void
minirl_disable_echo(minirl_st *minirl, char echo_char);

#ifdef __cplusplus
}
#endif

