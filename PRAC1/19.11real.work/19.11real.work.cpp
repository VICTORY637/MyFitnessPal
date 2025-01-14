//PRAKTIKUM 1 - VICTORIA BAMBALOVA


#include <iostream>
#include <cmath>

using namespace std;

//1
void print_happy_day() {
	cout << "Oh what" << endl << "a happy day!" << endl << "Oh yes," << endl << "what a happy day!" << endl;
}

//2
void print_S_P_rectangle() {
	double lendth = 7.9;
	double width = 5.4;
	double S = lendth * width;
	double P = 2 * (lendth + width);
	cout << "S = " << S << endl << "P = " << P << endl;
}
//3
void euro_dollar_converter() {
	double leva;
	cout << "Leva: "; cin >> leva;
	const double INDEX_DOLLAR = 0.54;
	const double INDEX_EURO = 0.51;
	double dollar_value = leva * INDEX_DOLLAR;
	double euro_value = leva * INDEX_EURO;
	cout << "Dollar: " << dollar_value << endl << "Euro: " << euro_value;
}


//4
void input_sides_print_S_P() {
	double lendth;
	double width;
	cout << "Please enter the length of the first side: "; cin >> lendth;
	cout << "Please enter the length of the second side:"; cin >> width;
	
	double S = lendth * width;
	double P = 2 * (lendth + width);
	cout << "S = " << S << endl << "P = " << P << endl;
}

//5
bool first_is_bigger() {
	int first_num, second_num;
	cin >> first_num;
	cin >> second_num;
	bool first_is_bigger = first_num > second_num;
	return first_is_bigger;
}

//6
void print_quotient_remainder() {
	int num1, num2;
	cout << "Dividend: ";
	cin >> num1;
	cout << "Divisor: ";
	cin >> num2;

	int quotient = num1 / num2;
	int remainder = num1 % num2;

	cout << "The quotient of the division is: " << quotient << "\nThe remainder of the division is: " << remainder;

}
//7
void Pesho() {
	int apples, pears, bananas;
	cout << "Apples: "; cin >> apples;
	cout << "Pears: "; cin >> pears;
	cout << "Bananas: "; cin >> bananas;
	cout << "Pesho, don't forget to buy " << apples << " apples, " << pears << " pears and " << bananas << " bananas!";
}
//8
double square(double a) {
	return a * a;
}
void circle_area_length() {
	const double PI = 3.14159265;
	double radius;
	cout << "Radius: "; cin >> radius;
	double length = 2 * PI * radius;
	double area = PI * square(radius);
	cout << "S = " << area << endl << "C = " << length;

}
//9
void quadratic_equations() {
	int a, b, c;
	double x1, x2;
	cout << "Input values for a, b and c: ";
	cin >> a >> b >> c;
	if (a == 0) {
		x1 = double(( - c) / b);
		cout << x1;
	}
	else if (b == 0)
	{
		if (((-c) / a) > 0) {
			x1 = double(sqrt((-c) / a));
			x2 = double(-(sqrt((-c) / a)));
			cout << x1 << endl << x2;
		}
		else if (((-c) / a) < 0) {
			cout << "No real roots";
		}
	}
	else if (c == 0) {
		x1 = 0;
		x2 = double(-b / a);
		cout << x1 << endl << x2;
	}
	else {
		double D = double(square(b) - 4 * a * c);
		if (D > 0) {
			x1 = (-b + sqrt(D)) / (2 * a);
			x2 = (-b - sqrt(D)) / (2 * a);
			cout << x1 << endl << x2;

		}
		else if (D == 0) {
			x1 = (-b) / (2 * a);
			cout << x1;
		}
		else {
			cout << "No roots";
		}
	}
	
	
}
//10
// without temporary var
void swap() {
	int a, b;
	cout << "Input a, b: ";
	cin >> a >> b;
	a = a + b;
	b = a - b;
	a = a - b;
	cout << a << " " << b;

}

//with temporary var
void swap1() {
	int a, b, c;
	cout << "Input a, b: ";
	cin >> a >> b;
	c = a;
	a = b;
	b = c;

	cout << a << " " << b;
}
//11
void min_max() {
	int a, b;
	cin >> a >> b;
	int max = (a + b + abs(a - b)) / 2;
	int min = (a + b - abs(a - b)) / 2;
	cout << "max: " << max << "\nmin: " << min << endl;
//2 way
	bool bigger = a > b;
	cout << bigger * a + !bigger * b << endl;
	bool smaller = a < b;
	cout << smaller * a + !smaller * b << endl;
}
//12
void seconds() {
	long input_seconds;
	cout << "Seconds: ";  cin >> input_seconds; //533628
	int days = input_seconds / (24 * 3600); // 6
	int hours = (input_seconds % (24 * 3600)) / 3600; //4
	int minutes = ((input_seconds % (24 * 3600)) % 3600) / 60; //13
	int seconds = (((input_seconds % (24 * 3600)) % 60) % 60);
	cout << days << "days, " << hours << "hours, " << minutes << "minutes, " << seconds << "seconds";
}
//13
double distance() {
	int x1, y1, x2, y2;
	cout << "x1 = ";  cin >> x1;
	cout << "y1 = ";  cin >> y1;
	cout << "x2 = ";  cin >> x2;
	cout << "y2 = ";  cin >> y2;

	double distance = sqrt(square(x1 - x2) + square(y1 - y2));
	double rounded_distance = round(distance * 100) / 100;
	return rounded_distance;

}
//14
int sum() {
	int n;
	cout << "Number: "; cin >> n;
	int sum = ((1 + n) * n) / 2;
	return sum;
}

int main() {
	//1		print_happy_day();
	//2		print_S_P_rectangle();
	//3		euro_dollar_converter();
	//4		input_sides_print_S_P();
	//5		cout << first_is_bigger();
	//6		print_quotient_remainder();
	//7		Pesho();
	//8		circle_area_length();
	//9		quadratic_equations();
	//10with	swap1();
	//10without		swap();
	//11	min_max();
	seconds();
	//13	cout << distance();
	//14 cout << sum();
	return 0;
}