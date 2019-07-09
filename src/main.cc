#include <iostream>

#include "mpi.h"

#include "print-message.hh"
#include "file-system/process.hh"
#include "leader-election.hh"

int main(int argc, char** argv) {
    int rank, size, len;

    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    struct Process p;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        print_error(-1, "Allow two or more process!");
        MPI_Finalize();
        return 1;
    }
    MPI_Get_library_version(version, &len);
    print_info(size, "Number of process");
    p.id = rank;
    p.size = size;
    print_info(rank, "create process");
    leader_election(p, size);
    print_info(rank, "End of election");
    MPI_Finalize();

    return 0;
}
