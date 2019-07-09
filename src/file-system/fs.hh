#pragma once

enum command_code
{
  READ_CODE,
  WRITE_CODE,
  CREATE_CODE,
  DELETE_CODE
};

int create(const std::string& name);

std::string read(const std::string& name);

int write(const std::string& name, const std::string& content);

int delete(const std::string& name);
