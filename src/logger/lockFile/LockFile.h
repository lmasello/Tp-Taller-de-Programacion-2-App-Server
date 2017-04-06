#ifndef LOCKFILE_H_
#define LOCKFILE_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include "../syscalls/SysCalls.h"

class LockFile {

private:
	struct flock fl;
	int fd;
	std::string name;

public:
	LockFile (const std::string name);
	~LockFile();

	ssize_t write(const void *buffer, const ssize_t size) const;

private:
	int lock();
	int unlock();

};

#endif /* LOCKFILE_H_ */
