#pragma once

#include <map>

enum
{
  SIZE_FILE = 100
};

struct Process
{
  Process(std::size_t cid, std::size_t csize, std::size_t cchief)
    : id(cid)
    , size(csize)
    , chief(cchief)
    {}
  
  const std::size_t id;
  const std::size_t size;
  const std::size_t chief;
};

struct Leader : public Process
{
  Leader(std::size_t cid, std::size_t csize, std::size_t cchief)
    : Process(cid, csize, ccshief)
    {}
  
  std::map<std::string, std::size_t> location;
};

struct Client : public Process
{
  Client(std::size_t cid, std::size_t csize, std::size_t cchief)
    : Process(cid, csize, cchief)
    {}
};

struct File : public Process
{
  File(std::size_t cid, std::size_t csize, std::size_t cchief)
    : Process(cid, csize, cchief)
    , hasNext(false)
    {}

  char content[SIZE_FILE];
  bool hasNext;
  std::size_t next;
};
