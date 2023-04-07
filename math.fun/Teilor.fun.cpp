#include "stdio.h"
#include "math.h"
#include "locale.h"


double sin_pr(double x, double fel, int ind) {
	if (x == 0) return 0;
	else {
		fel *= (-1) * x * x / (2 * ind * (2 * ind + 1));
		return fel;
	}
}

double cos_pr(double x, double fel, int ind) {
	if (x == 0) return 1;
	else {
		fel *= (-1) * x * x / (2 * ind * (2 * ind - 1));
		return fel;
	}
}

double log_pr(double x, double fel, int ind) {
	fel *= (-1) * x * ind / (ind + 1);
	return fel;
}

double exp_pr(double x, double fel, int ind) {
	fel *= x / ind;
	return fel;
}

//обратная сумма
double sin_ob(double x, double fel, int ind) {
	fel = -fel * (2 * ind) * (2 * ind + 1) / (x * x);
	return fel;
}

double cos_ob(double x, double fel, int ind) {
	fel = -fel * (2 * ind) * (2 * ind - 1) / (x * x);
	return fel;
}

double ln_ob(double x, double fel, int ind) {
	if (ind == 0) return 0;
	if (ind == 1) return 0;
	fel = -fel * ind / (x * (ind - 1));
	return fel;
}

double exp_ob(double x, double fel, int ind) {
	fel = fel * ind / x;
	return fel;
}


double summ(double suma, double(*fun)(double, double, int), double x, double fel) {
	suma += fel;
	for (int i = 1; i < 100; i++) {
		fel = fun(x, fel, i);
		suma += fel;
	}
	return suma;
}


double summ_ob(double suma, double(*fun)(double, double, int), double x, double fel) {
	suma += fel;
	for (int i = 100; i > -1; i--) {
		fel = fun(x, fel, i);
		suma += fel;
	}
	return suma;
}

int main() {

	setlocale(LC_ALL, "Russian");
	double x;
	double minuss; //эпсилон
	double sinp = 0, cosp = 0, lnp = 0, expp = 0; //прямой счёт
	double sino = 0, coso = 0, lno = 0, expo = 0; //обратный счёт
	double sin_can = 0, cos_can = 0, ln_can = 0, exp_can = 0; //канон
	double fel; //первый элемент
	double lel; //последний элемент
	printf("Введите значение х: ");
	scanf_s("%lf", &x);
	printf("\n");

	//sinx
	fel = x;
	sinp = summ(sinp, sin_pr, x, fel);
	sin_can = sin(x);
	printf("sin(x) = %.20lf\n", sinp);
	//
	lel = 1;
	for (int j = 1; j < 202; j++) {
		lel = lel * x / j;
	}
	sino = summ_ob(sino, sin_ob, x, lel);
	printf("Обратный sin(x) = %.20lf\n", sino);
	//
	printf("канонный sin(x) = %.20lf\n", sin_can);
	minuss = labs(sinp - sin_can);
	printf("Разница Эпсилон: %.20lf\n\n", minuss);

	//cosx
	fel = 1;
	cosp = summ(cosp, cos_pr, x, fel);
	cos_can = cos(x);
	printf("cos(x) = %.20lf\n", cosp);
	//
	lel = 1;
	for (int j = 1; j < 201; j++) {
		lel *= x / j;
	}
	coso = summ_ob(coso, cos_ob, x, lel);
	printf("Обратный cos(x) = %.20lf\n", coso);
	//
	printf("канонный cos(x) = %.20lf\n", cos_can);
	minuss = labs(cosp - cos_can);
	printf("Разница Эпсилон: %.20lf\n\n", minuss);

	//ln(1+x)
	if ((x > -1) && (x <= 1)) {
		fel = x;
		lnp = summ(lnp, log_pr, x, fel);
		ln_can = log(1 + x);
		printf("ln(x+1) = %.20lf\n", lnp);
		//
		lel = -pow(x, 100) / 100;
		lno = summ_ob(lno, ln_ob, x, lel);
		printf("Обратная ln(1+x): %.20lf\n", lno);
		//
		printf("канонный ln(x+1) = %.20lf\n", ln_can);
		minuss = labs(lnp - ln_can);
		printf("Разница Эпсилон: %.20lf\n\n", minuss);
	}
	else
		printf("Недопустимые значения для ln(1+x)\n\n");

	//exp^x
	fel = 1;
	expp = summ(expp, exp_pr, x, fel);
	exp_can = exp(x);
	printf("exp^x = %.20lf\n", expp);
	//
	lel = 1;
	for (int j = 1; j < 101; j++) {
		lel *= x / j;
	}
	expo = summ_ob(expo, exp_ob, x, lel);
	printf("Обратная exp^x: %.20lf\n", expo);
	//
	printf("канонная exp^x = %.20lf\n", exp_can);
	minuss = labs(expp - exp_can);
	printf("Разница Эпсилон: %.20lf\n\n", minuss);

	return 0;
}
