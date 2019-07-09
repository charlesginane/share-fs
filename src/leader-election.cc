#include "leader-election.hh"

int leader_election(struct Process p, int size) {
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
