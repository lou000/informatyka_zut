package lab_5;

class lab5_Model
{

    ////////MULTIPLICATION
    int[][] multiply_matrices(int[][] A, int[][] B)
    {
        if(A[0].length != B.length)
            return null; //        assert A[0].length == B.length : "Matrices are the wrong size";
        int[][] C = new int[A.length][B[0].length];
        for (int row = 0; row < C.length; row++)
        {
            for(int column = 0; column<C[0].length; column++)
            {
                for (int i = 0; i < B.length; i++) {
                    C[row][column] += A[row][i] * B[i][column];
                }
            }
        }
        return C;
    }

    /////////TRANSPOSITION
    int[][] transpose_matrix(int[][] A) {
        int[][] C = new int[A[0].length][A.length];
        for (int row = 0; row < A.length; row++) {
            for (int column = 0; column < A[0].length; column++) {
                C[column][row] = A[row][column];
            }
        }
        return C;
    }

    int matrix_A[][];
    int matrix_B[][];
    int matrix_C[][];
}
