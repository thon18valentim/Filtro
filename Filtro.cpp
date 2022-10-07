#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace mat;
int median(std::vector<int> vet);
int main()
{
	std::string tipo;
	int coluna = 0, linha = 0, max;
	auto matrix = Matrix<int>();
	auto matrix_copia = Matrix<int>();

	std::string fileName = "003";
	std::ifstream arquivo{ fileName + ".pgm"};
	if (arquivo.good()) {
		arquivo >> tipo >> coluna >> linha >> max;
		matrix.set_size(linha, coluna);
		int num, i = 0, j = 0;
		while (arquivo >> num) {
			matrix.at(i, j) = num;
			j++;
			if (j == coluna) {
				i++;
				j = 0;
			}
		}
	}
	//std::cout << matrix.serialize() << "\n";

	matrix_copia = matrix;
	for (int i = 0; i < linha - 1; i++) {
		for (int j = 0; j < coluna - 1; j++) {
			std::vector<int> vet;
			if (i > 0) {
				vet.push_back(matrix.at(i - 1, j));
			}
			if (i < coluna - 1) {
				vet.push_back(matrix.at(i + 1, j));
			}
			if (j > 0) {
				vet.push_back(matrix.at(i, j - 1));
			}
			if (j == linha - 1) {
				vet.push_back(matrix.at(i, j + 1));
			}

			if (j > 0 && i > 0) {
				vet.push_back(matrix.at(i - 1, j - 1));
			}
			if (j < coluna - 1 && i > 0) {
				vet.push_back(matrix.at(i - 1, j + 1));
			}
			if (j > 0 && i < linha - 1) {
				vet.push_back(matrix.at(i + 1, j - 1));
			}
			if (j < coluna - 1 && i < linha - 1) {
				vet.push_back(matrix.at(i + 1, j + 1));
			}
			std::sort(vet.begin(), vet.end());
			matrix_copia.at(i, j) = median(vet);
		}
	}

	std::ofstream arquivo_filtro{ fileName + "_filtro.pgm" };
	arquivo_filtro << tipo << "\n" << coluna << " " << linha << "\n" << max << "\n";
	for (int i = 0; i < linha - 1; i++) {
		for (int j = 0; j < coluna - 1; j++) {
			arquivo_filtro << matrix_copia.at(i, j) << " ";
		}
		arquivo_filtro << "\n";
	}

}

int median(std::vector<int> vet) {
	int size = vet.size() - 1;
	if (size % 2 == 0) {
		int i = vet[(size) / 2];
		int j = vet[(size) / 2 + 1];
		return (i + j) / 2;
	}
	else {
		return vet[(size) / 2];
	}
}
