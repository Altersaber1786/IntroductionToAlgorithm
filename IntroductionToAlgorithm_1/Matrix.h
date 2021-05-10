#pragma once
#include<vector>
#include<cassert>


namespace My_Matrix
{

	template <typename T>
	class Matrix
	{
	public:
		Matrix(const Matrix& mat)
		{
			rows = mat.rows;
			columns = mat.columns;
			stride = mat.stride;
			startSlot = mat.startSlot;
			data = new std::vector<T>();
			for (unsigned int i = 0; i < mat.data->size(); i++)
			{
				data->push_back(mat.data->at(i)) ;
			}
		};

		Matrix(int n, int m)
		{
			//Create the Identity matrix
			rows = n;
			columns = m;
			stride = m;
			data = new std::vector<T>();
			for (int i = 1; i <= rows; i++)
				for (int j = 1; j <= columns; j++)
				{
					if (j == i)
						data->push_back(1);
					else
						data->push_back(0);
				};
			startSlot = 0;
		}

		Matrix(int n, int m, T x)
		{
			rows = n;
			columns = m;
			stride = m;
			data = new std::vector<T>(rows*columns, x);
			startSlot = 0;
		}

		Matrix(int n, int m, T A[])
		{
			rows = n;
			columns = m;
			stride = m;
			data = new std::vector<T>();
			for (int i = 0; i < rows*columns; i++)
			{
				data->push_back(A[i]);
			}
			startSlot = 0;
		}
		Matrix(int n, int m, const std::initializer_list<T>& init_List)
		{
			const T* A = init_List.begin();
			rows = n;
			columns = m;
			stride = m;
			data = new std::vector<T>();
			for (int i = 0; i < rows*columns; i++)
			{
				data->push_back(A[i]);
			}
			startSlot = 0;
		}
		Matrix(Matrix& mat, int n, int m, int n0, int m0)
		{
			rows = n;
			columns = m;
			stride = mat.stride;
			data = mat.data;
			startSlot  = startSlot + (n0 - 1)*stride + m0 - 1;
		}

		~Matrix() {
			delete data;
		};
		T& operator()(int x, int y) const
		{
			return data->at(startSlot + (x - 1)*stride + y - 1);
		};

		Matrix& operator=(const Matrix& A)
		{
			assert(this->rows == A.rows && this->columns == A.columns);
			startSlot = A.startSlot;
			stride = A.stride;
			data = new std::vector<T>();
			for (int i = 1; i <= A.rows; i++)
			{
				for (int j = 1; j <= A.columns; j++)
				{
					data->push_back(A(i, j));
				}
			}
			startSlot = 0;
			return *this;
		}

		Matrix operator+(const Matrix& B)
		{
			assert(this->rows == B.rows && this->columns == B.columns);

			Matrix C = Matrix(B.rows, B.columns);
			for (int i = 1; i <= C.rows; i++)
				for (int j = 1; j <= C.columns; j++)
					C(i, j) = (*this)(i, j) +B(i, j);
			return C;
		}
		Matrix operator-(const Matrix& B)
		{
			assert(this->rows == B.rows && this->columns == B.columns);

			Matrix C = Matrix(B.rows, B.columns);
			for (int i = 1; i <= C.rows; i++)
				for (int j = 1; j <= C.columns; j++)
					C(i, j) = (*this)(i, j) - B(i, j);
			return C;
		}

		Matrix operator*(const Matrix& B)
		{
			assert(this->columns == B.rows);
			Matrix C = Matrix(this->rows, B.columns, (T)0);
			for (int i = 1; i <= this->rows; i++)
				for (int j = 1; j <= B.columns; j++)
					for (int k = 1; k <= this->columns; k++)
					{
						C(i, j) += (this->operator()(i, k))*B(k, j);
					}
			return C;
		}
		bool LU_Factorize(Matrix<T>&, Matrix<T>&);
		void Print();
		int stride;
		int rows;
		int columns;
		unsigned int startSlot;

	private:
		std::vector<T>* data;
	};
	
	
	Matrix<int> StrassenMatrixMultiply(Matrix<int> a, Matrix<int> b);
	Matrix<int> SquareMatrixPow(Matrix<int> a, uint32_t n);
	Matrix<int> MatrixSorting(Matrix<int>);
	
}