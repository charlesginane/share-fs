#include "fs.hh"
#include <cstring>

int remove(Process *p, const std::string& name)
{
  int code = REMOVE_CODE;
  int response;
  MPI_Status status;
  int name_size = name.size();


  if (p->id == 0) //client
  {
    //Contact le serveur
    MPI_Send(&code, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);

    //Envoie la taille du message
    MPI_Send(&name_size, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);

    //Envoie le message
    MPI_Send(name.c_str(), name.size(), MPI_CHAR, p->chief, 0, MPI_COMM_WORLD);
    MPI_Recv(&response, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);
  }

  if(p->id != p->chief)
  {
    int size;
    File *f = reinterpret_cast<File*>(p);
    //Contact le process
    MPI_Recv(0, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD, &status);

    memset(f->content, 0,  f->size);

    MPI_Send(0, 1, MPI_INT, p->chief, 0, MPI_COMM_WORLD);
    
  }
}
