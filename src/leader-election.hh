#pragma once

#include "mpi.h"

#include "file-system/process.hh"
#include "print-message.hh"

int leader_election(struct Process p, int size);
