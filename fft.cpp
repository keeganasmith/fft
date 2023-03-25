#include <iostream>
#include <vector>
#include <math.h>     

using std::cout, std::cin, std::vector;

#define PI 3.14159265358979
class complex_number{
    public:
    double imaginary;
    double real;
    complex_number(): imaginary{0}, real{0} {}
    complex_number(double real, double imag): imaginary{imag}, real{real} {}
    complex_number operator+(complex_number& other){
        return complex_number(this->real + other.real, this->imaginary + other.imaginary);
    }
    complex_number operator*(complex_number& other){
        double real_first = other.real * (this->real+this->imaginary);
        double common = this->imaginary * (other.real+other.imaginary);
        double imag_first = other.imaginary * (this->real - this->imaginary);
        return complex_number(real_first - common, imag_first + common);
    }
    complex_number operator-(complex_number& other){
        return complex_number(this->real - other.real, this->imaginary - other.imaginary);
    }
    complex_number operator/(int val){
        return complex_number(this->real/val, this->imaginary/val);
    }
    void print(){
        cout << this->real << " + " << this->imaginary << "i";
    }
};
template <typename T>
vector<vector<T>> evenOddIndices(vector<T>& coefficients){
    vector<vector<T>> result(2);
    for(int i = 0; i < coefficients.size(); i++){
        if(i % 2 == 0){
            result.at(0).push_back(coefficients.at(i));
        }
        else{
            result.at(1).push_back(coefficients.at(i));
        }
    }
    return result;
}
complex_number kth_root_of_unity(int k, int n){
    complex_number result;
    double inside = 2 * PI * double(k) / n;
    result.imaginary = sin(inside);
    result.real = cos(inside);
    return result;
}
vector<complex_number> ifft_helper(vector<complex_number>& point_values){
    if(point_values.size() == 1){
        return point_values;
    }
    vector<vector<complex_number>> evenodd = evenOddIndices(point_values);
    
    vector<complex_number> evens = ifft_helper(evenodd.at(0));
    vector<complex_number> odds = ifft_helper(evenodd.at(1));
    //even = evenodd.at(0), odd = evenodd.at(1)
    vector<complex_number> result(point_values.size());
    for(int i = 0; i < point_values.size()/2; i++){
        //w_k = e^{2pi(i)k/n} = cos(2pik/n) + isin(2pik/n)
        complex_number w_k = kth_root_of_unity(-i, point_values.size());
        complex_number w_kTimesodd = w_k * odds.at(i);
        result.at(i) = (evens.at(i) + w_kTimesodd);
        result.at(point_values.size()/2 + i) = (evens.at(i) - w_kTimesodd); 
        
    }
    return result;
}
vector<complex_number> ifft(vector<complex_number>& point_values){
    vector<complex_number> inter = ifft_helper(point_values);
    for(int i = 0; i < inter.size(); i++){
        inter.at(i) = inter.at(i) / point_values.size();
    }
    return inter;
}
vector<complex_number> fft(vector<complex_number>& coefficients){
    if(coefficients.size() == 1){
        return coefficients;
    }
    vector<vector<complex_number>> evenodd = evenOddIndices(coefficients);
    
    vector<complex_number> evens = fft(evenodd.at(0));
    vector<complex_number> odds = fft(evenodd.at(1));
    vector<complex_number> result(coefficients.size());
    for(int i = 0; i < coefficients.size()/2; i++){
        complex_number w_k = kth_root_of_unity(i, coefficients.size());
        complex_number w_kTimesodd = w_k * odds.at(i);
        result.at(i) = evens.at(i) + w_kTimesodd;
        result.at(coefficients.size()/2 + i) = evens.at(i) - w_kTimesodd; 
    }
    return result;
}
vector<complex_number> multiply(vector<complex_number> pv1, vector<complex_number> pv2){
    vector<complex_number> result;
    for(int i = 0; i < pv1.size(); i++){
        result.push_back(pv1.at(i) * pv2.at(i));
    }
    return result;
}
double multiply(int one, int two){
    vector<complex_number> one_coefficients;
    vector<complex_number> two_coefficients;
    while(one > 0){
        one_coefficients.push_back(complex_number(one % 10, 0));
        one /= 10;
    }
    while(two > 0){
        two_coefficients.push_back(complex_number(two % 10, 0));
        two /= 10;
    }
    int d_1 = one_coefficients.size()-1;
    int d_2 = two_coefficients.size()-1;
    while(one_coefficients.size() < d_1 + d_2 + 2){
        one_coefficients.push_back(complex_number(0, 0));
    }
    while(two_coefficients.size() < d_1 + d_2 + 2){
        two_coefficients.push_back(complex_number(0, 0));
    }
    vector<complex_number> one_pv = fft(one_coefficients);
    vector<complex_number> two_pv = fft(two_coefficients);
    vector<complex_number> result_pv = multiply(one_pv, two_pv);
    vector<complex_number> result = ifft(result_pv);
    double sum = 0;
    double curr_pow = 1;
    for(int i = 0; i < result.size(); i++){
        sum += result.at(i).real * curr_pow;
        curr_pow *= 10;
    }
    return sum;
}
