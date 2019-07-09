#pragma once

#include "mpi.h"

#include "file-system/process.hh"
#include "print-message.hh"

int leader_election(int rank, int size);
