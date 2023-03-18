#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
using namespace std;
float func_first(float);
float func_second(float);
float simpsons(float ll, float ul, int n, float (*) (float));
vector <float> Intersection(float step, int rounding, float (*) (float));
vector <float> Intersection(float step, int rounding, float (*) (float), float (*) (float));

int main() {
	vector <float> dots = Intersection(0.00001, 5, func_first, func_second);
	cout << "Intersection points:" << '\n';
	for (int i = 0; i < dots.size(); i++) {
		cout << "(" << dots.at(i) << ", " << func_first(dots.at(i)) << ")" << '\n';
	}
	cout << endl;
	cout << "Intersections of functions with 0x axis :" << '\n';
	vector <float> interX_1 = Intersection(0.0001, 5, func_first);
	vector <float> interX_2 = Intersection(0.0001, 5, func_second);
	if (interX_1.size() == 0) {
		cout << "There is no intersections" << '\n';
	}
	else {
		cout << "Intersection of first function with 0x axis: ";
		for (int i = 0; i < interX_1.size(); i++) {
			cout << "(" << interX_1.at(i) << ", " << func_first(interX_1.at(i)) << ")" << '\n';
		}
	}
	if (interX_2.size() == 0) {
		cout << "There is no intersections" << '\n';
	}
	else {
		cout << "Intersection of second function with 0x axis: ";
		for (int i = 0; i < interX_2.size(); i++) {
			cout << "(" << interX_2.at(i) << ", " << func_second(interX_2.at(i)) << ")" << '\n';
		}
	}
	double square = abs(simpsons(dots.at(1), dots.at(2), 10, func_first) - simpsons(dots.at(1), dots.at(2), 10, func_second));
	cout << endl;
	cout << "Square = " << square << '\n';
	return 0;
}

float func_first(float x) {
	float y = 1 / (1 + x);
	return y;
}
float func_second(float x) {
	float y = -1 * pow(x, 2) + 4 * x + 5;
	return y;
}

float simpsons(float ll, float ul, int n, float (*func) (float)) {
	// calculating the value of h
	float h = (ul - ll) / n;
	// array for soring value of x and f(x)
	float x[11], fx[11];
	// calculating the value of x and f(x)
	for (int i = 0; i <= n; i++) {
		x[i] = ll + i * h;
		fx[i] = func(x[i]);
	}
	// calculating result
	float res = 0;
	for (int i = 0; i <= n; i++) {
		if (i == 0 || i == n)
			res += fx[i];
		else if (i % 2 != 0)
			res += 4 * fx[i];
		else
			res += 2 * fx[i];
	}
	res = res * (h / 3);
	return res;
}

vector <float> Intersection(float step, int rounding, float (*func) (float)) {
	vector <float> arr;
	vector <float> res;
	for (float i = -100.0; i <= 100; i = i + step) {
		if (abs(func(i)) <= step) {
			arr.push_back(i);
		}
	}
	if (arr.size() != 0) {
		int count = 1;
		float arr_sum = arr.at(0);
		for (int i = 1; i < arr.size(); i++) {
			if ((arr.at(i) - arr.at(i - 1)) <= step * 2.0) {
				arr_sum += arr.at(i);
				count++;
			}
			else {
				res.push_back(round(arr_sum / count * pow(10, rounding)) / pow(10, rounding));
				count = 1;
				arr_sum = arr.at(i);
			}
		}
		res.push_back(round(arr_sum / count * pow(10, rounding)) / pow(10, rounding));
	}
	return res;
}
vector <float> Intersection(float step, int rounding, float (*func1) (float), float (*func2) (float)) {
	vector <float> arr;
	vector <float> res;
	for (float i = -200.0; i <= 200; i = i + step) {
		if (abs(func1(i) - func2(i)) <= 10.0 * step) {
			arr.push_back(i);
		}
	}
	int count = 1;
	float arr_sum = arr.at(0);
	for (int i = 1; i < arr.size(); i++) {
		if ((arr.at(i) - arr.at(i - 1)) <= step * 2.0) {
			arr_sum += arr.at(i);
			count++;
		}
		else {
			res.push_back(round(arr_sum / count * pow(10, rounding)) / pow(10, rounding));
			count = 1;
			arr_sum = arr.at(i);
		}
	}
	res.push_back(round(arr_sum / count * pow(10, rounding)) / pow(10, rounding));
	return res;
}