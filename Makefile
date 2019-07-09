
SRC_FILES = src/main.cc src/leader-election.cc src/file-system/write.cc #src/file-system/read.cc

all:
	mpic++ ${SRC_FILES}
