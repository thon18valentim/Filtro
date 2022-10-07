#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace mat
{
	template <typename T = double>
	class Matrix
	{
		std::vector< std::vector<T> > data;

	public:

		//constroi matriz vazia
		Matrix()
		{
		}

		//constroi matrix m*n
		Matrix(int m, int n)
		{
			set_size(m, n);
		}

		//acessa elemento
		T& at(int i, int j)
		{
			return data.at(i).at(j);
		}

		//pega numero de linhas
		int get_num_rows() const
		{
			return data.size();
		}

		//pega numero de colunas
		int get_num_cols()
		{
			return data.size() ? data.at(0).size() : 0;
		}

		//seta tamanho da matriz
		void set_size(int m, int n)
		{
			data.resize(m);
			for (auto& row : data)
			{
				row.resize(n);
			}
		}

		//serialize matriz para impressao
		std::string serialize(std::string const& separator = " ")
		{
			std::ostringstream output;
			for (auto& row : data)
			{
				for (auto& item : row)
				{
					output << item << separator;
				}
				output << "\n";
			}
			return output.str();
		}
	};
}
