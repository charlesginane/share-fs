#include "fs.hh"

std::string read(struct Process* p, const std::string& name) {
  int out_int;
  char out_msg[SIZE_FILE];
  MPI_Status status;
  MPI_Request request;
  if (p->id == 0) {
    auto p_cl = reinterpret_cast<Client*>(p); // FIXME
    MPI_Send(0, 1, MPI_INT, p->chief, 1, MPI_COMM_WORLD);
    MPI_Recv(&out_int, 100, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    // if (out_int != 0) {
    //   // FIXME -- ERROR
    // }

    MPI_Send(name.c_str(), name.size(), MPI_CHAR, p->chief, 1, MPI_COMM_WORLD);
    MPI_Recv(&out_msg, 100, MPI_CHAR, p->chief, 1, MPI_COMM_WORLD, &status);
  }

  else {
    auto p_file = reinterpret_cast<File*>(p);
    MPI_Recv(&out_msg, 100, MPI_CHAR, p_file->chief, 1, MPI_COMM_WORLD, &status);
    MPI_Send(&content, 100, MPI_CHAR, p_file->chief, 1, MPI_COMM_WORLD);
  }
}
