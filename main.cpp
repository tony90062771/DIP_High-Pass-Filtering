#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

// ���q�o�i�禡
void highPassFilter(int inputR[][MaxBMPSizeY], int inputG[][MaxBMPSizeY], int inputB[][MaxBMPSizeY], int outputR[][MaxBMPSizeY], int outputG[][MaxBMPSizeY], int outputB[][MaxBMPSizeY], int width, int height)
{
    //���q�o�i���B�n
    int mask[3][3] = {
        {1, 1, 1},
        {1,-8, 1},
        {1, 1, 1}
    };

    // �Ϲ����C�ӹ���
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            // �b�B�n�d�򤺭p�⹳�����`�M
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    sumR += inputR[i + x][j + y] * mask[x + 1][y + 1];
                    sumG += inputG[i + x][j + y] * mask[x + 1][y + 1];
                    sumB += inputB[i + x][j + y] * mask[x + 1][y + 1];
                }
            }

            // �����C��Ȧb 0 �� 255 ���d��
            outputR[i][j] = max(0, min(sumR, 255));
            outputG[i][j] = max(0, min(sumG, 255));
            outputB[i][j] = max(0, min(sumB, 255));
        }
    }
}

int main(int argc, char* argv[])
{
    int width, height;
    int i, j;

    // �}�Ҩ�Ū�����mbmp �v������
    open_bmp("lena.bmp", R, G, B, width, height);

    // ���氪�q�o�i�B�z
    highPassFilter(R, G, B, r, g, b, width, height);

    // �x�s�B�z���G�ܷs�����ɤ�
    save_bmp("lenna_highpass.bmp", r, g, b);

    printf("Job Finished!\n");

    // ���� bmp �v������
    close_bmp();

    system("pause");
    return 0;
}
