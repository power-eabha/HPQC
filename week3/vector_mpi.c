#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int check_args(int argc, char **argv);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int my_rank, uni_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &uni_size);

    int num_arg = check_args(argc, argv);

    int chunk_size = num_arg / uni_size;
    int remainder = num_arg % uni_size;

    int start, end;

    if (my_rank < remainder)
    {
        start = my_rank * (chunk_size + 1) + 1;
        end = start + chunk_size;
    }
    else
    {
        start = my_rank * chunk_size + remainder + 1;
        end = start + chunk_size - 1;
    }

    double start_time = MPI_Wtime();

    int local_sum = 0;
    for (int i = start; i <= end; i++)
    {
        local_sum += i;
    }

    int total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (my_rank == 0)
    {
        printf("Sum: %d\n", total_sum);
        printf("Internal runtime: %.6f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}

int check_args(int argc, char **argv)
{
    int num_arg = 0;

    if (argc == 2)
    {
        num_arg = atoi(argv[1]);
    }
    else
    {
        fprintf(stderr, "ERROR: You did not provide a numerical argument!\n");
        fprintf(stderr, "Correct use: %s [NUMBER]\n", argv[0]);
        exit(-1);
    }

    return num_arg;
}
