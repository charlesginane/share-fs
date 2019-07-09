#include "process.hh"
#include "fs.hh"
#include <iostream>

int create(Process* p, const std::string& name)
{ 
  int response;
  MPI_Status status;
  MPI_Request request;
  int name_size = name.size();


  if (p->id == 0)
  {
    std::cout << "in" << std::endl;
    int code = CREATE_CODE;
    //auto client = reinterpret_cast<Client*>(p);
    MPI_Send(&code, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);

    MPI_Send(&name_size, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);


    std::cout << "Reponse: " << response << std::endl;
    MPI_Send(name.c_str(), name.size(), MPI_CHAR, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);
  }
}
