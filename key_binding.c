#include "minirl.h"
#include "private.h"
#include "export.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

NO_EXPORT
struct minirl_keymap *
minirl_keymap_new(void)
{
	struct minirl_keymap * const keymap = calloc(1, sizeof(*keymap));

	return keymap;
}

NO_EXPORT
void
minirl_keymap_free(struct minirl_keymap * const keymap)
{
	for (size_t i = 0; i < ARRAY_SIZE(keymap->keys); i++) {
		if (keymap->keys[i].keymap != NULL) {
			minirl_keymap_free(keymap->keys[i].keymap);
		}
	}
	free(keymap);
}

bool
minirl_bind_key_sequence(
	minirl_st * const minirl,
	const char * const seq_in,
	minirl_key_binding_handler_cb const handler,
	void * const user_ctx)
{
	struct minirl_keymap *keymap;
	unsigned char key;
	const char *seq = seq_in;

	if (seq[0] == '\0') {
		return false;
	}

	keymap = minirl->keymap;
	key = seq[0];
	seq++;

	while (seq[0] != '\0') {
		if (keymap->keys[key].keymap == NULL) {
			keymap->keys[key].keymap = minirl_keymap_new();
		}
		if (keymap->keys[key].keymap == NULL) {
			return false;
		}
		keymap = keymap->keys[key].keymap;
		key = seq[0];
		seq++;
	}

	keymap->keys[key].handler = handler;
	keymap->keys[key].user_ctx = user_ctx;

	return true;
}

bool
minirl_bind_key(
	minirl_st * const minirl,
	uint8_t const key,
	minirl_key_binding_handler_cb const handler,
	void * const user_ctx)
{
	char seq[2] = { key, '\0' };

	return minirl_bind_key_sequence(minirl, seq, handler, user_ctx);
}

