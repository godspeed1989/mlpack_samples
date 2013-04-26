#include <mlpack/core.hpp>
#include <mlpack/methods/sparse_coding/sparse_coding.hpp>
using namespace mlpack;

void chk_coding(const arma::mat& dict, const arma::mat& code, const arma::mat& X)
{
	assert(dict.n_cols == code.n_rows);
	const arma::uword& samples = code.n_cols;
	const arma::uword& dimension = dict.n_rows;
	arma::mat result(dimension, samples);
	result = dict * code;
	result = abs(result - X);
	result.print();
}

void coding()
{
	double lambda1 = 0.02;
	double lambda2 = 0;
	arma::mat X;
	X.load("sparse.csv");
	Log::Info << "==TrainData Info==" << std::endl;
	Log::Info << "Cols(Samples):    " << X.n_cols << std::endl;
	Log::Info << "Rows(Dimensions): " << X.n_rows << std::endl;
	X.print();
	arma::uword nAtoms = X.n_rows * 2 / 3 ; // reduce the dimension by 1/3
	sparse_coding::SparseCoding<> sc(X, nAtoms, lambda1, lambda2);
	
	sc.Encode(0, 0.01, 1e-6);

	const arma::mat& D = sc.Dictionary();
	Log::Info << "==Dictionary Info==" << std::endl;
	Log::Info << "Cols(Codes):       " << D.n_cols << std::endl;
	Log::Info << "Rows(Dim) = X.dim  " << D.n_rows << std::endl;
	D.print();
	const arma::mat& Z = sc.Codes();
	Log::Info << "====Codes Info====" << std::endl;
	Log::Info << "Cols(Samples):    " << Z.n_cols << std::endl;
	Log::Info << "Rows(Dimensions): " << Z.n_rows << std::endl;
	Z.print();
	Log::Info << "===Check Coding===" << std::endl;
	chk_coding(D, Z, X);
	Log::Info << "===Try Encoding===" << std::endl;
	arma::mat test = X.col(0);
	arma::mat code = arma::pinv(D) * test;
	code.print();
	Log::Info << "===Check Coding===" << std::endl;
	chk_coding(D, code, test);
}

int main(int argc, char* argv[])
{
	CLI::ParseCommandLine(argc, argv);
	coding();
	return 0;
}

