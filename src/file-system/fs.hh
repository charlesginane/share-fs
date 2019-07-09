#pragma once

enum command_code
{
  READ_CODE,
  WRITE_CODE,
  CREATE_CODE,
  DELETE_CODE
};

int create(Process p, const std::string& name);

std::string read(Process p, const std::string& name);

int write(Process p, const std::string& name, const std::string& content);

int delete(Process p, const std::string& name);
