#include "LockFile.h"

LockFile::LockFile(const std::string name) {
	this->name = name;
	this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
	this->fd = syscalls::open(this->name.c_str(), O_CREAT|O_WRONLY, 0777);
}

int LockFile::lock() {
	this->fl.l_type = F_WRLCK;
	return fcntl(this->fd, F_SETLKW, &(this->fl));
}

int LockFile::unlock() {
	this->fl.l_type = F_UNLCK;
	return fcntl(this->fd, F_SETLK, &(this->fl));
}

ssize_t LockFile::write(const void* buffer,const ssize_t size) {
	lock();
	syscalls::lseek(this->fd, 0, SEEK_END);
	ssize_t response = syscalls::write(this->fd, buffer,size);
	this->unlock();

	return response;
}

LockFile::~LockFile () {
	syscalls::close(this->fd);
}
