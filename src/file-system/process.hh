#pragma once

#include <map>

enum
{
  SIZE_FILE = 100
};

struct Process
{
  Process(std::size_t cid, std::size_t csize)
    : id(cid)
    , size(csize)
    {}
  
  const std::size_t id;
  const std::size_t size;
};

struct Leader : public Process
{
  Leader(std::size_t cid, std::size_t csize)
    : Process(cid, csize)
    {}
  
  std::map<std::string, std::size_t> location;
};

struct Client : public Process
{
  Client(std::size_t cid, std::size_t csize, std::size_t cchief)
    : Process(cid, csize)
    , chief(cchief)
    {}
  
  std::size_t chief;
};

struct File : public Process
{
  File(std::size_t cid, std::size_t csize)
    : Process(cid, csize)
    , hasNext(false)
    {}

  char content[SIZE_FILE];
  bool hasNext;
  std::size_t next;
};
