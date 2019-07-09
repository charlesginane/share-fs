#pragma once

enum
{
  SIZE_FILE = 100;
};

struct Process
{
  std::size_t id;
  std::size_t size;
};

struct Leader : public Process
{
  std::map<std::string, std::size_t> location;
};

struct Client : public Process
{
  std::size_t chief;
};

struct File : public Process
{
  char[SIZE_FILE] content;
  bool hasNext;
  std::size_t next;
};
