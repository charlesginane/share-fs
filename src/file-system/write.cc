#include "fs.hh"

int write(Process *p, const std::string& name, const std::string& content)
{
  if (p->id == 0)
  {
    Client* c = reinterpret_cast<Client*>(p);
    int code = WRITE_CODE;
    int msg_size = content.size();
    MPI_Send(&code, 1, MPI_INT, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(name.c_str(), name.size(), MPI_BYTE, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(&msg_size, 1, MPI_INT, c->chief, 0, MPI_COMM_WORLD);
    MPI_Send(content.c_str(), content.size(), MPI_BYTE, c->chief, 0, MPI_COMM_WORLD);
  }
}
