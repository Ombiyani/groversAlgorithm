#ifndef ILINE_H
#define ILINE_H
#include <vector>
#include <SFML/Graphics.hpp>
class ILine{
    public:
        /**
         * @brief Destroy the ILine object
         * 
         */
        virtual ~ILine() {}
        /**
         * @brief draws the objects
         * 
         * @param window 
         */
        virtual void draw(sf::RenderTarget& window) = 0;
        /**
         * @brief returns the vector of SFML x coordinates
         * 
         * @return std::vector<double> 
         */
        virtual std::vector<double> getNewX() const = 0; 
        /**
         * @brief returns the vector of SFML y coordinates
         * 
         * @return std::vector<double> 
         */
        virtual std::vector<double> getNewY() const = 0;

};
#endif