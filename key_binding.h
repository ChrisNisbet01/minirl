#pragma once

#define KEYMAP_SIZE 256

struct key_handler {
	minirl_key_binding_handler_cb handler;
	struct minirl_keymap *keymap;
	void *user_ctx;
};

struct minirl_keymap {
	struct key_handler keys[KEYMAP_SIZE];
};

struct minirl_keymap *
minirl_keymap_new(void);

void
minirl_keymap_free(struct minirl_keymap *keymap);

