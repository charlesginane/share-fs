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
    std::cout << "in" << std::endl;
    int t = 2;
    auto client = reinterpret_cast<Client*>(p);
    MPI_Send(&t, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&out_int, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);

    std::cout << "Reponse: " << out_int << std::endl;
   MPI_Send(name.c_str(), name.size(), MPI_CHAR, p->chief, 0, MPI_COMM_WORLD);
   MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);
  }
}
