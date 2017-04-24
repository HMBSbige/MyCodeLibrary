static void mm_generate(float* matA,float* matB,float* matC,const int M,const int N,const int K,const int strideA,const int strideB,const int strideC)
{
	for (int i = 0; i < M;i++)
	{
		for (int j = 0; j < N;j++)
		{
			float sum = 0.0f;
			for (int k = 0; k < K;k++)
			{
				sum += matA[i*strideA + k] * matB[k*strideB + j];
			}
			matC[i*strideC + j] = sum;
		}
	}
}
static void mm_strassen(float* matA, float* matB, float* matC, const int M, const int N, const int K, const int strideA, const int strideB, const int strideC)
{
	if ((M <= 64) || (M%2 != 0 ||N%2 != 0 ||K%2!=0))
	{
		return mm_generate(matA, matB, matC, M, N, K, strideA, strideB, strideC);
	}
	memset(matC, 0, M*strideC*sizeof(float));
	int offset = 0;
	//M1 = (A11+A22)*(B11+B22)
	std::vector<float> M1((M / 2) * (N / 2));
	{
		memset(&M1[0], 0, M1.size()*sizeof(float));
		//M1_0 = (A11+A22)
		std::vector<float> M1_0((M / 2) * (K / 2));
		offset = M*strideA / 2 + K / 2;
		for (int i = 0; i < M / 2; i++)
		{
			for (int j = 0; j < K/2; j++)
			{
				const int baseIdx = i*strideA + j;
				M1_0[i*K/2+j] = matA[baseIdx] + matA[baseIdx + offset];
			}
		}
		//M1_1 = (B11+B22)
		std::vector<float> M1_1((K / 2) * (N / 2));
		offset = K*strideB / 2 + N / 2;
		for (int i = 0; i < K / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				const int baseIdx = i*strideB + j;
				M1_1[i*N/2+j] = matB[baseIdx] + matB[baseIdx + offset];
			}
		}
		mm_strassen(&M1_0[0], &M1_1[0], &M1[0], M / 2, N / 2, K / 2,
			K/2,N/2,N/2);
	}
	//M2 = (A21+A22)*B11
	std::vector<float> M2((M / 2) * (N / 2));
	{
		memset(&M2[0], 0, M2.size()*sizeof(float));
		//M2_0 = (A21+A22)
		std::vector<float> M2_0((M / 2) * (K / 2));
		offset = K / 2;
		for (int i = M / 2; i < M; i++)
		{
			for (int j = 0; j < K / 2; j++)
			{
				const int baseIdx = i*strideA + j;
				M2_0[(i-M/2)*K/2+j] = matA[baseIdx] + matA[baseIdx + offset];
			}
		}
		//M2_2 = B11
		mm_strassen(&M2_0[0], &matB[N / 2], &M2[0], M / 2, N / 2, K / 2,
			K / 2, strideB, N / 2);
	}
	//M3 = A11*(B12-B22)
	std::vector<float> M3((M / 2) * (N / 2));
	{
		memset(&M3[0], 0, M3.size()*sizeof(float));
		//M3_0 = A11
		//M3_1 = (B12-B22)
		std::vector<float> M3_1((K / 2) * (N / 2));
		offset = K*strideB / 2;
		for (int i = 0; i < K/2; i++)
		{
			for (int j = N/2; j < N; j++)
			{
				const int baseIdx = i*strideB + j;
				M3_1[i*N/2+j-N/2] = matB[baseIdx] - matB[baseIdx + offset];
			}
		}
		mm_strassen(matA, &M3_1[0], &M3[0], M / 2, N / 2, K / 2,
			strideA, N / 2, N / 2);
	}
	//M4 = A22*(B21-B11)
	std::vector<float> M4((M / 2) * (N / 2));
	{
		memset(&M4[0], 0, M4.size()*sizeof(float));
		//M4_0 = A22
		//M4_1 = (B12-B22)
		std::vector<float> M4_1((K / 2) * (N / 2));
		offset = K*strideB / 2;
		for (int i = 0; i < K / 2; i++)
		{
			for (int j = N / 2; j < N; j++)
			{
				const int baseIdx = i*strideB + j;
				M4_1[i*N/2+j-N/2] = matB[baseIdx + offset] - matB[baseIdx];
			}
		}
		mm_strassen(matA + M*strideA / 2 + K / 2, &M4_1[0], &M4[0], M / 2, K / 2, N / 2,
			strideA, N / 2, N / 2);
	}
	//M5 = (A11+A12)*B22
	std::vector<float> M5((M / 2) * (N / 2));
	{
		memset(&M5[0], 0, M5.size()*sizeof(float));
		//M5_0 = (A11+A12)
		std::vector<float> M5_0((M / 2) * (K / 2));
		offset = K / 2;
		for (int i = 0; i < M/2; i++)
		{
			for (int j = 0; j < K / 2; j++)
			{
				const int baseIdx = i*strideA + j;
				M5_0[i*K / 2 + j] = matA[baseIdx] + matA[baseIdx + offset];
			}
		}
		//M5_1 = B22
		mm_strassen(&M5_0[0], &matB[K*strideB / 2 + N / 2], &M5[0], M / 2, N / 2, K / 2,
			K / 2, strideB, N / 2);
	}
	//M6 = (A21-A11)*(B11+B12)
	std::vector<float> M6((M / 2) * (N / 2));
	{
		memset(&M6[0], 0, M6.size()*sizeof(float));
		//M6_0 = (A21-A11)
		std::vector<float> M6_0((M / 2) * (K / 2));
		offset = K*N / 2;
		for (int i = 0; i < M / 2; i++)
		{
			for (int j = 0; j < K/2; j++)
			{
				const int baseIdx = i*strideA + j;
				M6_0[i*K/2+j] = matA[baseIdx + offset] - matA[baseIdx];
			}
		}
		//M6_1 = (B11+B12)
		std::vector<float> M6_1((K / 2) * (N / 2));
		offset = N / 2;
		for (int i = 0; i < K / 2; i++)
		{
			for (int j = 0; j < N/2; j++)
			{
				const int baseIdx = i*strideB + j;
				M6_1[i*N/2+j] = matB[baseIdx] + matB[baseIdx + offset];
			}
		}
		mm_strassen(&M6_0[0], &M6_1[0], &M6[0], M / 2, N / 2, K / 2,
			K / 2, N / 2, N / 2);
	}
	//M7 = (A12-A22)*(B21+B22)
	std::vector<float> M7((M / 2) * (N / 2));
	{
		memset(&M7[0], 0, M7.size()*sizeof(float));
		//M7_0 = (A12-A22)
		std::vector<float> M7_0((M / 2) * (K / 2));
		offset = M*strideA / 2;
		for (int i = 0; i < M / 2; i++)
		{
			for (int j = K/2; j < K; j++)
			{
				const int baseIdx = i*strideA + j;
				M7_0[i*K / 2 + j - K / 2] = matA[baseIdx] - matA[baseIdx + offset];
			}
		}
		//M7_1 = (B21+B22)
		std::vector<float> M7_1((K / 2) * (N / 2));
		offset = N / 2;
		for (int i = K/2; i < K; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				const int baseIdx = i*strideB + j;
				M7_1[(i-K/2)*N / 2 + j] = matB[baseIdx] + matB[baseIdx + offset];
			}
		}
		mm_strassen(&M7_0[0], &M7_1[0], &M7[0], M / 2, N / 2, K / 2,
			K / 2, N / 2, N / 2);
	}	
	for (int i = 0; i < M / 2;i++)
	{
		for (int j = 0; j < N / 2;j++)
		{
			const int idx = i*N / 2 + j;
			//C11 = M1+M4-M5+M7
			matC[i*strideC + j] = M1[idx] + M4[idx] - M5[idx] + M7[idx];
			//C12 = M3+M5
			matC[i*strideC + j + N/2] = M3[idx] + M5[idx];
			//C21 = M2+M4
			matC[(i+M/2)*strideC + j] = M2[idx] + M4[idx];
			//C22 = M1-M2+M3+M6
			matC[(i+M/2)*strideC + j + N/2] = M1[idx] - M2[idx] + M3[idx] + M6[idx];
		}
	}
}