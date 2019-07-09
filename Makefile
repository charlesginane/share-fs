
SRC_FILES = src/main.cc src/leader-election.cc

all:
	mpic++ ${SRC_FILES}
