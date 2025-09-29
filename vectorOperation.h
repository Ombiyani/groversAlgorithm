#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H
#include <vector> 
/**
 * @brief return the tensor prouct as nested matrix
 * 
 * @return std::vector<std::vector<double>> 
 */
std::vector<std::vector<double>>  tensorProduct(std::vector<double>, std::vector<double>);
/**
 * @brief returns the scaler/inner product
 * 
 * @return double 
 */
double scalerProduct(std::vector<double>, std::vector<double>);
/**
 * @brief preforms matrix multiplaction by a column vector
 * 
 * @return std::vector<double> 
 */
std::vector<double>  matrixVectorMultiplication ( std::vector<double>, std::vector<std::vector<double>>);
/**
 * @brief subtracts column matracies
 * 
 * @return std::vector<double> 
 */
std::vector<double> subtract(std::vector<double>, std::vector<double>);
/**
 * @brief subtracts square matracies
 * 
 * @return std::vector<double> 
 */
std::vector<std::vector<double>> subtract(std::vector<std::vector<double>>, std::vector<std::vector<double>>);
/**
 * @brief multiplies columns by constent
 * 
 * @return std::vector<double> 
 */
std::vector<double> mutiplyByConstant(std::vector<double>, int);
/**
 * @brief multiplies square matracies by constent
 * 
 * @return std::vector<std::vector<double>> 
 */
std::vector<std::vector<double>> mutiplyByConstant(std::vector<std::vector<double>>, int);

#endif