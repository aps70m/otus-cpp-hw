#include <iostream>
#include <sstream>
#include <string>
#include <clocale>
#include "World.hpp"
#include "Painter.hpp"
#include <fstream>
#include <cmath>

static constexpr double timePerTick = 0.001;

static Point readPoint(std::ifstream& stream) {
    double x, y;
    stream >> x >> y;
    return Point(x, y);
}

World::World(const std::string& worldFilePath) {
    // Устанавливаем локаль для правильного чтения чисел с точкой
    std::setlocale(LC_NUMERIC, "C");
    
    std::ifstream stream(worldFilePath);
    if (!stream.is_open()) {
        std::cerr << "ERROR: Cannot open file: " << worldFilePath << std::endl;
        return;
    }
    std::cout << "File opened successfully" << std::endl;
    
    topLeft = readPoint(stream);
    bottomRight = readPoint(stream);
    physics.setWorldBox(topLeft, bottomRight);
    
    std::cout << "World bounds: (" << topLeft.x << "," << topLeft.y 
              << ") to (" << bottomRight.x << "," << bottomRight.y << ")" << std::endl;
    
    std::string line;
    int ballCount = 0;
    
    // Пропускаем остатки строк после readPoint
    std::getline(stream, line);
    std::getline(stream, line);
    
    while (std::getline(stream, line)) {
        if (line.empty()) continue;
        
        std::cout << "Parsing: " << line << std::endl;
        
        // Замена возможных запятых на точки (на всякий случай)
        for (char& c : line) {
            if (c == ',') c = '.';
        }
        
        std::istringstream iss(line);
        double x, y, vx, vy, radius, red, green, blue;
        std::string collidableStr;
        
        if (iss >> x >> y >> vx >> vy >> red >> green >> blue >> radius >> collidableStr) {
            bool isCollidable = (collidableStr == "true" || collidableStr == "1");
            
            ballCount++;
            std::cout << "  -> Ball " << ballCount << " loaded at (" << x << "," << y << "), radius=" << radius << std::endl;
            
            Ball ball;
            ball.setCenter(Point(x, y));
            ball.setVelocity(Velocity(Point(vx, vy)));
            ball.setRadius(radius);
            ball.setColor(Color(red, green, blue));
            ball.setCollidable(isCollidable);
            balls.push_back(ball);
        } else {
            std::cout << "  -> FAILED to parse!" << std::endl;
        }
    }
    
    std::cout << "Total balls loaded: " << balls.size() << std::endl;
}

void World::show(Painter& painter) const {
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));
    
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

void World::update(double time) {
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;
    physics.update(balls, ticks);
}
