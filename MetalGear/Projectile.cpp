#include "Projectile.h"
#include "TileMap.h"



void Projectile::update(int deltatime)
{
    if (!active) return;

    elapsedTime += deltatime;

    int stepsToAdvance = speed;
    for (int i = 0; i < stepsToAdvance && currentStep < trajectoryPoints.size(); i++) {
        currentStep++;
        distanceTraveled += speed;

        if (currentStep < trajectoryPoints.size()) {
            position = trajectoryPoints[currentStep];
            sprite->setPosition(glm::vec2(position.x, position.y));

            if (currentStep >  4 && elapsedTime >= 100 && tileMap->checkTileCollision(position, size, false)) {
                active = false;
                return;
            }

			hitTarget();

        }
    }

    if (currentStep >= trajectoryPoints.size() || distanceTraveled >= maxDistance) {
        active = false;
    }
}

void Projectile::render()
{
    if (active) {
		sprite->render();
    }
}

void Projectile::calculateTrajectory() {
    trajectoryPoints.clear();
    glm::ivec2 startPos = position;
    glm::ivec2 endPos = startPos;

    if (direction == -1) {
        endPos = playerPosition;
    }
    else {
        switch (direction) {
        case DOWN:
            endPos.y += maxDistance;
            break;
        case UP:
            endPos.y -= maxDistance;
            break;
        case LEFT:
            endPos.x -= maxDistance;
            break;
        case RIGHT:
            endPos.x += maxDistance;
            break;
        }
    }

    int dx = endPos.x - startPos.x;
    int dy = endPos.y - startPos.y;
    int N = std::max(std::abs(dx), std::abs(dy)) * 6;

    if (N == 0) {
        trajectoryPoints.push_back(startPos);
        return;
    }

    for (int step = 0; step <= N; step++) {
        double t = static_cast<double>(step) / N;
        double x = startPos.x + t * (endPos.x - startPos.x);
        double y = startPos.y + t * (endPos.y - startPos.y);

        glm::ivec2 point(static_cast<int>(std::round(x)),
            static_cast<int>(std::round(y)));

        trajectoryPoints.push_back(point);

        if (tileMap->checkTileCollision(point, size, false)) {
            maxDistance = step * speed;
            break;
        }
    }
	cout << "Trajectory calculated with " << trajectoryPoints.size() << " points." << endl;
}