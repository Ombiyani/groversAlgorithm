#ifndef A_Line_Plot_H
#define A_Line_Plot_H
#include "ILine.h"
class ALinePlot:ILine{
    public:
        /**
         * @brief Construct a new ALinePlot object
         * 
         * @param dotColor 
         */
        ALinePlot(std::vector<double>, std::vector<double>, sf::Color);
        /**
         * @brief Destroy the ALinePlot object
         * 
         */
        ~ALinePlot();
        /**
         * @brief draws to window
         * 
         * @param window 
         */
        void draw(sf::RenderTarget& window) override;
        /**
         * @brief Get the New X object, sfml x coordinates
         * 
         * @return std::vector<double> 
         */
        std::vector<double> getNewX() const override;
           /**
         * @brief Get the New X object, sfml u coordinates
         * 
         * @return std::vector<double>
         */
        std::vector<double> getNewY() const override;


    private:
        /**
         * @brief makes new x
         * 
         */
        void matchX();
        /**
         * @brief makes new y
         * 
         */
        void matchY();
        /**
         * @brief pepares the lines and points for drawing
         * 
         */
        void prepareDraw(sf::Color dotColor);

        
        std::vector<double> _x{};
        std::vector<double> _y{};
        std::vector<double> _newX{};
        std::vector<double> _newY{};
        std::vector<sf::CircleShape*>  _plotPoints{};
        std::vector<sf::ConvexShape*>  _plotLines{};
        
};

#endif