
SRC_FILES = src/main.cc src/leader-election.cc src/file-system/write.cc src/file-system/read.cc src/file-system/chief_recv.cc

all:
	mpic++ ${SRC_FILES}
