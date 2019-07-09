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
      int name_size, content_size;
      MPI_Recv(&name_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
      char name[name_size];
      MPI_Recv(&name, name_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
      MPI_Recv(&content_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
      char content[content_size];
      MPI_Recv(&content, content_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
      break;

    case READ_CODE:
      MPI_Send(0, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

      MPI_Recv(&out_msg, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);

      id_process = c->location.find(out_msg)->second;

      MPI_Send(&out_msg, 100, MPI_CHAR, id_process, 1, MPI_COMM_WORLD);

      MPI_Recv(&out_msg, 100, MPI_CHAR, id_process, 1, MPI_COMM_WORLD, &status);
      MPI_Send(&out_msg, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
      break;

    case CREATE_CODE:
      {
      MPI_Send(0, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
      MPI_Recv(&out_msg, SIZE_FILE, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);

      auto search = c->location.find("");
      int value = search->second;
      c->location.erase(search->first);
      c->location.emplace(std::make_pair(out_msg, value));
      }
      break;
	
    case REMOVE_CODE:
      break;
    }
  }
}
