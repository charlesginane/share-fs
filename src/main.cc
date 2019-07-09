#include <iostream>

#include "print-message.hh"
#include "mpi.h"

struct process {
    int size;
    int id;
    //int leader;
};


int leader_election(struct process p, int size) {
    int imsg;
    int omsg;
    int leader;
    MPI_Status status;
    MPI_Request request;
    if (p.id == 0) {
        MPI_Status status;
        print_info(p.id, "Waiting for leader election");
        MPI_Recv(&omsg, size,  MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        print_info(p.id, "Getting the leader");
        leader = omsg;

    }
    else {
        if ((p.id + 1) % size != 0)
            MPI_Send(&p.id, 1, MPI_INT, (p.id + 1) % size, 1, MPI_COMM_WORLD);
        else
            MPI_Send(&p.id, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        while (1) {
            if ((p.id-1)%size == 0)
                MPI_Recv(&imsg, 1, MPI_INT, size-1, 1, MPI_COMM_WORLD, &status);
            else
                MPI_Recv(&imsg, 1, MPI_INT, (p.id-1)%size, 1, MPI_COMM_WORLD, &status);

            print_info(p.id, "Receive message");
            std::cout << imsg << std::endl;

            if (imsg == p.id) {
                leader = p.id;
                print_info(p.id, "This is the leader !!!!");
                MPI_Send(&p.id, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
                break;
            }

            if (leader == imsg) {
                break;
            }

            omsg = p.id;
            if (imsg < p.id) {
                omsg = imsg;
                leader = imsg;
            }


            if ((p.id + 1) % size != 0)
                MPI_Send(&omsg, 1, MPI_INT, (p.id + 1) % size, 1, MPI_COMM_WORLD);
            else
                MPI_Send(&omsg, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        }
        if ((p.id + 1) % size != 0)
            MPI_Send(&omsg, 1, MPI_INT, (p.id + 1) % size, 1, MPI_COMM_WORLD);
        else
            MPI_Send(&omsg, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    }
    return leader;

}


int main(int argc, char** argv) {
    int rank, size, len;

    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    struct process p;
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
