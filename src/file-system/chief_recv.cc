#include <mpi.h>
#include <iostream>

#include "fs.hh"

void chief_recv(Process *p)
{
  MPI_Status status;
  auto id_process = 0;
  char out_msg[SIZE_FILE];
  if (p->id == p->chief)
  {
    auto c = reinterpret_cast<Leader*>(p);
    int action;
    MPI_Recv(&action, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    switch (action)
    {
    case WRITE_CODE:
    {
      int name_size, content_size;
      MPI_Recv(&name_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      char name[name_size];
      MPI_Recv(&name, name_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(&content_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      char content[content_size];
      MPI_Recv(&content, content_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      std::cout << "[CHIEF] WRITE " << name << "(" << name_size << ") " << content << " (" << content_size << ")\n";

      std::size_t node_number = c->location[std::string(name)];

      MPI_Send(&content_size, 1, MPI_INT, node_number, 0, MPI_COMM_WORLD);
      MPI_Send(&content, content_size, MPI_BYTE, node_number, 0, MPI_COMM_WORLD);
    }
      break;

    case READ_CODE:
    {
      int t = 0;
      MPI_Send(&t, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

      MPI_Recv(&out_msg, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);

      id_process = c->location.find(out_msg)->second;

      MPI_Send(&out_msg, 100, MPI_CHAR, id_process, 1, MPI_COMM_WORLD);

      MPI_Recv(&out_msg, 100, MPI_CHAR, id_process, 1, MPI_COMM_WORLD, &status);
      MPI_Send(&out_msg, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
      break;
    }

    case CREATE_CODE:
      {
      int test = 0;
      std::cout << "[CHIEF] CREATE" << std::endl;
      MPI_Send(&test, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&out_msg, SIZE_FILE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
      std::cout << "msg: " << out_msg << std::endl;
      auto search = c->location.find("");
      int value = search->second;
      c->location.erase(search->first);
      c->location.emplace(std::make_pair(out_msg, value));
      MPI_Send(&test, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      std::cout << "[CHIEF] END OF CREATION" << std::endl;
      }
      break;

    case REMOVE_CODE:
      break;
    }
  }
}
