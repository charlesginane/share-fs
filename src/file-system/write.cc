#include <cstring>

#include "fs.hh"

int write(Process *p, const std::string& name, const std::string& content)
{
  if (p->id == 0)
  {
    Client* c = reinterpret_cast<Client*>(p);
    int code = WRITE_CODE;
    int msg_size = content.size();
    int name_size = name.size();
    MPI_Send(&code, 1, MPI_INT, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(&name_size, 1, MPI_INT, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(name.c_str(), name.size(), MPI_BYTE, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(&msg_size, 1, MPI_INT, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(content.c_str(), content.size(), MPI_BYTE, c->chief, 0, MPI_COMM_WORLD);
  }
  else if (p->id != p->chief)
  {
    File *f = reinterpret_cast<File*>(p);
    std::size_t content_size;
    MPI_Recv(&content_size, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    char content[content_size];
    MPI_Recv(&content, content_size, MPI_BYTE, p->chief, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    memcpy(f->content, content, content_size);
  }
}
