#include "vectorOperation.h"
#include <iostream>
#include <cmath>
#include <exception>
#include <string>

double scalerProduct(std::vector<double> bra, std::vector<double> ket){
    //returns the scalerProduct
    if(bra.size()==ket.size()){
        double sum = 0;
        for(unsigned int i = 0; i< bra.size(); i++)
        {
            sum += bra.at(i)*ket.at(i);
        }
        return sum;
    }
    else{
        throw std::out_of_range("size of vectors is not equal");
    }
}   


std::vector<std::vector<double>>  tensorProduct(std::vector<double> bra, std::vector<double> ket){
    // preforms tensor product where a*b is one row in the nested vector
    std::vector<std::vector<double>> tensor{};
    std::vector<double> values{};
    if(bra.size()==ket.size()){
        for(unsigned int i =0; i< bra.size(); i++ ){
            values.clear();
            for(unsigned int k =0; k < ket.size(); k++){
                values.push_back(bra.at(i)*ket.at(k));
            } 
            tensor.push_back(values);
        }
        return tensor;
    }
    else{throw std::out_of_range("size of vectors is not equal");}
}

std::vector<double>  matrixVectorMultiplication ( std::vector<double> vector, std::vector<std::vector<double>> matrix){
    //multiplies row by column and returns column vector
    std::vector<double> newVector{};
    double sum = 0;
    if(vector.size()==matrix.size()){
        for(unsigned int i =0; i< vector.size(); i++ ){
            sum = 0;
            if(vector.size()==matrix.at(i).size()){
                for(unsigned int s = 0; s< vector.size(); s++){
                    sum += vector.at(s)*matrix.at(s).at(i);
                }
                newVector.push_back(sum);
            }

        }
         return newVector;
    }
    else{throw std::out_of_range("size of vectors is not equal");}
}   

std::vector<double> subtract(std::vector<double> vector1, std::vector<double> vector2){
    //subtracts cell by cell for column matracies
    std::vector<double> combined;
    if(vector1.size()==vector2.size()){
        for(unsigned int i =0; i< vector1.size(); i++ ){
            combined.push_back(vector1.at(i)-vector2.at(i));
        }
        return combined;
    }
    else{throw std::out_of_range("size of vectors is not equal");}
}

std::vector<std::vector<double>> subtract(std::vector<std::vector<double>> vector1, std::vector<std::vector<double>> vector2){
     //subtracts cell by cell for square matracies
    std::vector<std::vector<double>> combined;
    std::vector<double> combinedHolder;
    if(vector1.size()==vector2.size()){
        for(unsigned int i =0; i< vector1.size(); i++ ){
            combinedHolder.clear();
            if(vector1.at(i).size()==vector2.at(i).size()){
                for(unsigned int s =0; s< vector1.size(); s++ ){
                    combinedHolder.push_back(vector1.at(i).at(s)-vector2.at(i).at(s));
                }
                combined.push_back(combinedHolder);
            }
            else{throw std::out_of_range("size of vectors is not equal");}
        }
        return combined;
    }
    else{throw std::out_of_range("size of vectors is not equal");}
}

std::vector<double> mutiplyByConstant(std::vector<double> vector, int mulitplyBy){
     // implementaion of constant multiply columns matracies
    std::vector<double> newVector{};
    for(unsigned int i =0; i< vector.size(); i++ ){
        newVector.push_back(vector.at(i)*mulitplyBy);
    }
    return newVector;
}

std::vector<std::vector<double>> mutiplyByConstant(std::vector<std::vector<double>> vector, int mulitplyBy){
    // implementaion of constant multiply square matracies
    std::vector<std::vector<double>> newVector{};
    std::vector<double> newVectorHolder{};
    for(unsigned int i =0; i< vector.size(); i++ ){
        newVectorHolder.clear();
        for(unsigned int s =0; s< vector.at(i).size(); s++ ){
            newVectorHolder.push_back(vector.at(i).at(s)*mulitplyBy);
        }
        newVector.push_back(newVectorHolder);
    }
    return newVector;
}
