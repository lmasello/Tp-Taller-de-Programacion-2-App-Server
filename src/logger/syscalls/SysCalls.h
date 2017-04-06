#ifndef SRC_UTILS_SYSCALLS_H_
#define SRC_UTILS_SYSCALLS_H_

#include <asm-generic/errno-base.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <string>
#include <vector>

#include "exceptions/SysCallException.h"

using namespace std;

namespace syscalls {


	inline int open(const char *pathname, int flags, int otherFlags) {
		int response = ::open(pathname, flags, otherFlags);
		if (response < 0 && errno != EINTR) {
			throw SysCallException("Error trying to execute a open()");
		}
		return response;
	}

	inline int close(int fd) {
		int response = ::close(fd);
		if (response < 0 && errno != EINTR) {
			throw SysCallException("Error trying to execute a close()");
		}
		return response;
	}

	inline ssize_t write(int fd, const void *buf, size_t count) {
		int response = ::write(fd, buf, count);
		if (response < 0 && errno != EINTR) {
			throw SysCallException("Error trying to execute a write()");
		}
		return response;
	}

	inline off_t lseek(int fd, off_t offset, int whence) {
		off_t response = ::lseek(fd, offset, whence);
		if (response < 0 && errno != EINTR) {
			throw SysCallException("Error trying to execute a lseek()");
		}
		return response;
	}

}

#endif /* SRC_UTILS_SYSCALLS_H_ */
