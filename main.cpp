#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tgmath.h>
#include <cctype>

using namespace std;

bool isPrime(int input_int);
bool number_check(string input_string, vector<char> input_vector);
bool unique_digits(string input_string);
bool action_permission(char input_char);

void compute_optimal_number(vector<std::string> input_vector);
void display_instructions();

int main() {
    
    vector <std::string> prime_numbers{};
    vector <int> prime_numbers_score{};
    vector <char> unused_numbers{};
    
    string input_number;
    string output;
    bool solution=false;
    
    for (int i=10000; i<100000; i++){
        if (isPrime(i)){
            prime_numbers.push_back(to_string(i));
        }
    }
    
    for (int i=0; i<prime_numbers.size(); i++){
        prime_numbers_score.push_back(0);
    }
    
    compute_optimal_number(prime_numbers);
    display_instructions();
    
    while (!solution){
        
        cout<<"input: ";
        cin>>input_number;
        
        cout<<"output: ";
        cin>>output;
        
        cout<<"indexing ..."<<endl;
        
        for (int i=0; i<prime_numbers.size(); i++){
            for (int c=0; c<5; c++){
                switch(output.at(c)){
                    case '0':
                        if (prime_numbers[i].find(input_number.at(c))!=std::string::npos){
                            prime_numbers_score[i]=prime_numbers_score[i]-32;
                        }else{
                            if (number_check(prime_numbers[i], unused_numbers)){
                                prime_numbers_score[i]=prime_numbers_score[i]+6;
                            }else{
                                prime_numbers_score[i]=prime_numbers_score[i]-32;
                            }
                        }
                        unused_numbers.push_back(input_number.at(c));
                        break;
                    case '1':
                        if (prime_numbers[i].at(c)==input_number.at(c)){
                            prime_numbers_score[i]=prime_numbers_score[i]-32;
                        }else{
                            if (prime_numbers[i].find(input_number.at(c))==std::string::npos){
                                prime_numbers_score[i]=prime_numbers_score[i]-32;
                            }else{
                                if (number_check(prime_numbers[i], unused_numbers)){
                                    prime_numbers_score[i]=prime_numbers_score[i]+3;
                                }else{
                                    prime_numbers_score[i]=prime_numbers_score[i]-32;
                                }
                            }
                        }
                        break;
                    case '2':
                        if (prime_numbers[i].at(c)==input_number.at(c)){
                            prime_numbers_score[i]=prime_numbers_score[i]+32;
                        }else{
                            prime_numbers_score[i]=prime_numbers_score[i]-32;
                        }
                        break;
                    default:
                        cout<<"input mismatch ...";
                        exit (EXIT_FAILURE);
                }
            }
            if (unique_digits(prime_numbers[i])){
                prime_numbers_score[i]=prime_numbers_score[i]+11;
            }
        }
        
        for (int i=0; i<prime_numbers.size(); i++){
            for (int c=i+1; c<prime_numbers.size(); c++){
                if (prime_numbers_score[i]<prime_numbers_score[c]){
                    int tmp_int=prime_numbers_score[c];
                    prime_numbers_score[c]=prime_numbers_score[i];
                    prime_numbers_score[i]=tmp_int;
                    
                    string tmp_string=prime_numbers[c];
                    prime_numbers[c]=prime_numbers[i];
                    prime_numbers[i]=tmp_string;
                }
            }
        }
        
        for (int i=0; i<20; i++){
            cout<<"#   "<<prime_numbers_score[i]<<" "<<prime_numbers[i]<<endl<<endl;
        }
        
        int tmp_int=0;
        for (int i=0; i<5; i++){
            if (output.at(i)=='2'){
                tmp_int++;
            }
        }
        
        char input_char;
        if (tmp_int==5){
            cout<<"prime number found, restart session (Y/n): ";
            cin>>input_char;
            if (!action_permission(input_char)){
                cout<<"cleaning up ..."<<endl;
                solution=true;
            }
        }
    }
    return 0;
}

bool isPrime(int input_int){
    for (int i=2; i<input_int; i++){
        if (input_int%i==0){
            return false;
        }
    }
    return true;
}

bool number_check(string input_string, vector<char> input_vector){
    for (int i=0; i<input_vector.size(); i++){
        if (input_string.find(input_vector[i])!=std::string::npos){
            return false;
        }
    }
    return true;
}

bool unique_digits(string input_string){
    vector<char> used_digits{};
    for (int i=0; i<5; i++){
        for (int c=0; c<used_digits.size(); c++){
            if (input_string.find(used_digits[c])!=std::string::npos){
                return false;
            }
        }
        used_digits.push_back(input_string.at(i));
    }
    return true;
}

bool action_permission(char input_char){
    switch(input_char){
        case 'Y':
        case 'y':
            return true;
            break;
        case 'N':
        case 'n':
            return false;
            break;
        default:
            cout<<"input mismatch ... proceeding in normal mode ..."<<endl;
            return false;
            break;
    }
}

void compute_optimal_number(vector<std::string> input_vector){
    vector<int> optimal_score;
    char digits[10]={'0','1','2','3','4','5','6','7','8','9'};
    int digits_score[10]={0,0,0,0,0,0,0,0,0,0};
    
    cout<<"computing optimal starting prime numbers ..."<<endl;
    
    for (int i=0; i<input_vector.size(); i++){
        optimal_score.push_back(0);
    }
    
    for (int i=0; i<input_vector.size(); i++){
        for (int c=0; c<10; c++){
            if (input_vector[i].find(digits[c])!=std::string::npos){
                digits_score[c]++;
            }
        }
    }
    
    for (int i=0; i<input_vector.size(); i++){
        for (int c=0; c<10; c++){
            if (input_vector[i].find(digits[c])!=std::string::npos){
                optimal_score[i]=optimal_score[i]+digits_score[c];
            }
        }
    }
    
    for (int i=0; i<input_vector.size(); i++){
        for (int c=i+1; c<input_vector.size(); c++){
            if (optimal_score[i]<optimal_score[c]){
                int tmp_int=optimal_score[c];
                optimal_score[c]=optimal_score[i];
                optimal_score[i]=tmp_int;
                
                string tmp_string=input_vector[c];
                input_vector[c]=input_vector[i];
                input_vector[i]=tmp_string;
            }
        }
    }
    
    for (int i=0; i<9; i++){
        cout<<"#  "<<optimal_score[i]<<" "<<input_vector[i]<<endl;
    }
}

void display_instructions(){
    cout<<"caution: output 0 - no match, 1 - match/wrong location, 2 - match/right location"<<endl;
    cout<<"caution: do not use space between digits for input/output (ex. 19237 / 21111)"<<endl;
    cout<<"caution: prime numbers scored and displayed in descending order"<<endl;
}
