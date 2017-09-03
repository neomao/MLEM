#include <iostream>
#include <vector>
using namespace std;

void returnActivity(const vector<double> &Cijt, const vector<double> &Yit, const vector<double> &lambdaBefore, vector<double> &lambdaAfter, const vector<double> &Sit, int I, int J, int T)
{
	vector<double> Cj(J);

	for (int j_ = 0; j_ < J; j_++) {
		Cj[j_] = 0;
	}
	for (int j_ = 0; j_ < J; j_++) {
		for (int t_ = 0; t_ < T; t_++) {
			for (int i_ = 0; i_ < I; i_++) {
				Cj[j_] += Cijt[(t_ * I * J) + (i_ * J) + j_];
			}
		}
	}

	vector<double> denominator(I * T);
	for (int t_ = 0; t_ < T; t_++) {
		for (int i_ = 0; i_ < I; i_++) {
			denominator[(t_ * I) + i_] = 0;
		}
	}

	for (int t_ = 0; t_ < T; t_++) {
		for (int i_ = 0; i_ < I; i_++) {
			for (int j_ = 0; j_ < J; j_++) {
				denominator[(t_ * I) + i_] += Cijt[(t_ * I * J) + (i_ * J) + j_] * lambdaBefore[j_];
			}
			denominator[(t_ * I) + i_] += Sit[(t_ * I) + i_];
		}
	}

	double temp;

	for (int j_ = 0; j_ < J; j_++) {
		temp = 0;
		for (int t_ = 0; t_ < T; t_++) {
			for (int i_ = 0; i_ < I; i_++) {
				temp += ((Cijt[(t_ * I * J) + (i_ * J) + j_] * Yit[(I * t_) + i_]) / denominator[(t_ * I) + i_]);
			}
		}
		lambdaAfter[j_] = (lambdaBefore[j_] / Cj[j_]) * temp;
	}
}

int main() {
	int I = 0;
	int J = 0;
	int T = 0;

	//test
	T = 1;
	I = 6;
	J = 9;
	//

	vector<double> Cijt(I * T * J);
	vector<double> lambdaBefore(J);
	vector<double> lambdaAfter(J);
	vector<double> Yit(I * T);
	vector<double> Yi(I);
	vector<double> Sit(I * T);

	//test
	for (int t = 0; t < T; t++) {
		for (int i = 0; i < I; i++) {
			for (int j = 0; j < J; j++) {
				Cijt[(t * I * J) + (i * J) + j] = 0;
				if (j == 0) {
					if (i == 0 || i == 3) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 1) {
					if (i == 1 || i == 3) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 2) {
					if (i == 2 || i == 3) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 3) {
					if (i == 0 || i == 4) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 4) {
					if (i == 1 || i == 4) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 5) {
					if (i == 2 || i == 4) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 6) {
					if (i == 0 || i == 5) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 7) {
					if (i == 1 || i == 5) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
				else if (j == 8) {
					if (i == 2 || i == 5) {
						Cijt[(t * I * J) + (i * J) + j] = 1;
					}
				}
			}
		}
	}

	for (int j = 0; j < J; j++) {
		lambdaBefore[j] = 1;
		lambdaAfter[j] = 0;
	}

	//test
	for (int t = 0; t < T; t++) {
		for (int i = 0; i < I; i++) {
			Sit[(t * I) + i] = 0;
		}
	}

	//test
	Yit[0] = 12;
	Yit[1] = 15;
	Yit[2] = 18;
	Yit[3] = 6;
	Yit[4] = 15;
	Yit[5] = 24;

	for (int i = 0; i < I; i++) {
		Yi[i] = 0;
	}
	for (int count = 0; count < 10; count++) {
		returnActivity(Cijt, Yit, lambdaBefore, lambdaAfter, Sit, I, J, T);
		for (int i = 0; i < I; i++) {
			for (int t = 0; t < T; t++) {
				for (int j = 0; j < J; j++) {
					Yi[i] += Cijt[(I * J * t) + (i * J) + j] * lambdaAfter[j];
				}
			}
		}

		cout << "ƒÉF";
		for (int j = 0; j < J; j++) {
			cout << lambdaAfter[j] << ", ";
		}
		cout << "\n\n";

		cout << "yF";
		for (int i = 0; i < I; i++) {
			cout << Yi[i] << ", ";
		}
		cout << "\n\n";

		for (int i = 0; i < I; i++) {
			Yi[i] = 0;
		}

		for (int j = 0; j < J; j++) {
			lambdaBefore[j] = lambdaAfter[j];
			lambdaAfter[j] = 0;
		}
	}
}



