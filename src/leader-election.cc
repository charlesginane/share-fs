#include "leader-election.hh"

int leader_election(int rank, int size) {
    int imsg;
    int omsg;
    int leader;
    MPI_Status status;
    MPI_Request request;
    if (rank == 0) {
        MPI_Status status;
        print_info(rank, "Waiting for leader election");
        MPI_Recv(&omsg, size,  MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        print_info(rank, "Getting the leader");
        leader = omsg;

    }
    else {
        if ((rank + 1) % size != 0)
            MPI_Send(&rank, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
        else
            MPI_Send(&rank, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        while (1) {
            if ((rank-1)%size == 0)
                MPI_Recv(&imsg, 1, MPI_INT, size-1, 1, MPI_COMM_WORLD, &status);
            else
                MPI_Recv(&imsg, 1, MPI_INT, (rank-1)%size, 1, MPI_COMM_WORLD, &status);

            print_info(rank, "Receive message");
            std::cout << imsg << std::endl;

            if (imsg == rank) {
                leader = rank;
                print_info(rank, "This is the leader !!!!");
                MPI_Send(&rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
                break;
            }

            if (leader == imsg) {
                break;
            }

            omsg = rank;
            if (imsg < rank) {
                omsg = imsg;
                leader = imsg;
            }


            if ((rank + 1) % size != 0)
                MPI_Send(&omsg, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
            else
                MPI_Send(&omsg, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        }
        if ((rank + 1) % size != 0)
            MPI_Send(&omsg, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
        else
            MPI_Send(&omsg, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    }
    return leader;
}
