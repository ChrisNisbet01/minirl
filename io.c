#include "io.h"
#include "export.h"

#include <errno.h>
#include <signal.h>
#include <sys/select.h>

NO_EXPORT
bool
fd_is_readable(int const fd, size_t const timeout_ms)
{
	sigset_t sigmask;
	int res;

	sigemptyset(&sigmask);

	do {
		struct timespec const timeout =
		{
			.tv_sec = 0,
			.tv_nsec = timeout_ms * 1000000
		};
		fd_set rfds;

		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);

		res = pselect(fd + 1, &rfds, NULL, NULL, &timeout, &sigmask);
	}
	while (res == -1 && errno == EINTR);

	bool const is_readable = res > 0;

	return is_readable;
}

NO_EXPORT
int
read_byte_with_timeout(int const fd, uint8_t * const byte, size_t const timeout_ms)
{
	return fd_is_readable(fd, timeout_ms) ? io_read(fd, byte, 1) : -1;
}


