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
      break;

    case REMOVE_CODE:
      break;
    }
  }
}
