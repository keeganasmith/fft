#include "fft.cpp"
using std::vector, std::cout;
vector<complex_number> random_generator(int n){
    vector<complex_number> result;
    for(int i = 0; i < n; i++){
        result.push_back(complex_number(rand() % 10,0));
    }
    return result;
}
void pretty_print(vector<complex_number> joe){
    cout << "{";
    for(size_t i = 0; i < joe.size()-1; i++){
        joe.at(i).print();
        cout << ", ";
    }
    joe.at(joe.size()-1).print();
    cout << "}\n";
}
void does_it_work(){
    // vector<complex_number> coefficients({complex_number(3,0),complex_number(6,0),complex_number(7,0),complex_number(5, 0)});
    // vector<complex_number> result = fft(coefficients);
    // pretty_print(result);
    // vector<complex_number> test1({complex_number(3,0),complex_number(6,0),complex_number(7,0),complex_number(5,0),complex_number(3,0),complex_number(5, 0)});
    // test1 = fft(test1);
    // pretty_print(test1);
    vector<complex_number> coefficients({complex_number(2, 0), complex_number(1, 0), complex_number(2, 0), complex_number(0, 0)});
    vector<complex_number> test1 = fft(coefficients);
    pretty_print(test1);
    vector<complex_number> back = ifft(test1);
    pretty_print(back);
}

void print(vector<complex_number> joe){
    cout << "{";
    for(size_t i = 0; i < joe.size()-1; i++){
        cout << "complex_number(" << joe.at(i).real << "," << joe.at(i).imaginary << "),";
    }
    cout << "complex_number(" << joe.at(joe.size()-1).real << ", " << joe.at(joe.size()-1).imaginary << ")}\n";
}
int main(){
    //print(random_generator(6));
    //does_it_work();
    cout << multiply(5120, 2312) << "\n";
}