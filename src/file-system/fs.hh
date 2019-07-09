#pragma once

#include <string>

#include "process.hh"
#include "mpi.h"

enum command_code
{
  READ_CODE,
  WRITE_CODE,
  CREATE_CODE,
  REMOVE_CODE
};

void chief_recv(Process* p);

int create(Process p, const std::string& name);

std::string read(Process* p, const std::string& name);

int write(Process *p, const std::string& name, const std::string& content);

int remove(Process p, const std::string& name);
