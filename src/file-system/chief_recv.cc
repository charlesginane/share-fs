#include "fs.hh"

void chief_recv(Process *p)
{
  if (p->id == p->chief)
  {
    Chief *c = reinterpret_cast<Chief*>(p);
    int action;
    MPI_Recv(&action, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
    switch (action)
    {
    case WRITE_CODE:
      break;

    case SEND_CODE:
      break;

    case CREATE_CODE:
      break;

    case REMOVE_CODE:
      break;
    }
  }
}
