#include <iostream>

#include "print-message.hh"
#include "mpi.h"

struct process {
    bool is_client;
    int id;
    char* data;
    int leader;
};


int leader_election(struct process p, int size) {
    int buf;
    int imsg[1];
    int omsg[1];
    int leader;
    MPI_Status status;
    MPI_Request request;
    if (p.id == 0) {
        MPI_Status status;
        //MPI_Request request;
        print_info(p.id, "Waiting for leader election");
        MPI_Recv(&omsg, size,  MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        print_info(p.id, "Getting the leader");
        p.leader = omsg[0];

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
            std::cout << imsg[0] << std::endl;

            if (imsg[0] == p.id) {
                leader = p.id;
                print_info(p.id, "This is the leader !!!!");
                MPI_Send(&p.id, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
                break;
            }

            if (p.leader == imsg[0]) {
                break;
            }

            omsg[0] = p.id;
            if (imsg[0] < p.id) {
                omsg[0] = imsg[0];
                p.leader = imsg[0];
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
    p.data = nullptr;
    if (rank == 0)
        p.is_client = true;
    else
        p.is_client = false;
    p.leader = -1;
    print_info(rank, "create process");
    leader_election(p, size);
    print_info(rank, "End of election");
    MPI_Finalize();

    return 0;
}
