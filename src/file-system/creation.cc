#include "process.hh"
#include "fs.hh"


int create(Process* p, const std::string& name)
{
  int out_int;
  int response;
  MPI_Status status;
  MPI_Request request;


  if (p->id ==0)
  {
    auto client = reinterpret_cast<Client*>(p);
    MPI_SEND(2, 1, MPI_INT, p->chief, 1, MPI_COMM_WORLD);
    MPI_Recv(&out_int, 1, MPI_INT, p->chief, 1, MPI_COMM_WORLD, &status);


   MPI_Send(name.c_str(), name.size(), MPI_CHAR, p->chief, 1, MPI_COMM_WORLD);
   MPI_Recv(&response, 1, MPI_CHAR, p->chief, 1, MPI_COMM_WORLD, &status);
  }
}