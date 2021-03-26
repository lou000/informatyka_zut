#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using namespace std;

struct Particle{
    olc::vf2d pos;
    olc::vf2d vel;
    int size;
    int startS;
//    double vel;
    double lifeTime;
    double startLT;
    float transparency;
    float startT;
    olc::Pixel color;
};

#define PI 3.14159265
class Pendulum : public olc::PixelGameEngine
{
    double theta = PI/2;
    double vel = 0;
    double len = 2;
    double mass = 50;
    double drag = 10;
    double g = 9.81;
    double t = 0;
    float particleSpawnTime = 0;
    int scale = 1;
    float centerX = 0;
    std::vector<Particle> particles;

public:
    Pendulum()
    {
        sAppName = "Pendulum";
    }

    bool OnUserCreate() override
    {
        SetPixelMode(olc::Pixel::ALPHA);
        scale = GetDrawTargetWidth()/4;
        centerX = GetDrawTargetWidth()/2;

        return true;
    }

    bool OnUserUpdate(float dt) override
    {
        handleInput();
        simulateStep(dt);
        Clear(olc::VERY_DARK_GREY);
        updateAndDrawParticles(dt);
        drawPendulum();
        return true;
    }

private:
    void simulateStep(float dt)
    {
        //Runge-Kutta 4th order
        double k11 = dt*vel;
        double k12 = -dt*(drag/mass)*vel - dt*(g/len)*sin(theta);

        double k21 = dt*(vel + k11/2);
        double k22 = -dt*(drag/mass)*(vel + k12/2) - dt*(g/len)*sin(theta + k12/2);

        double k31 = dt*(vel + k21/2);
        double k32 = -dt*(drag/mass)*(vel + k22/2) -dt*(g/len)*sin(theta + k22/2);

        double k41 = dt*(vel + k31);
        double k42 =  -dt*(drag/mass)*(vel + k32) - dt*(g/len)*sin(theta + k32);

        theta = theta + (k11 + 2*k21 + 2*k31 + k41)/6;
        vel = vel + (k12 + 2*k22 + 2*k32 + k42)/6;
        t+=dt;

        double x = (double)GetDrawTargetWidth()/2 + sin(theta) * len * scale;
        double y = cos(theta) * len * scale;
        spawnParticles(x, y);
    }
    void drawPendulum()
    {
        auto midX = GetDrawTargetWidth()/2;
        double x = (double)GetDrawTargetWidth()/2 + sin(theta) * len * scale;
        double y = cos(theta) * len * scale;
        DrawLine(midX, 0, (int32_t)x, (int32_t)y);
        FillCircle((int32_t)x, (int32_t)y, scale/4, olc::Pixel(214, 173, 92));
    }
    void handleInput()
    {
        if (GetMouse(0).bHeld){
            auto mX = GetMouseX() - GetDrawTargetWidth()/2;
            auto mY = GetMouseY();
            theta = atan2(-(double)mY, (double)mX) + PI/2;
            vel = 0;
        }
    }
    void spawnParticles(int x, int y)
    {
        if(t - particleSpawnTime < 0.05) return;
        int randVel = (int)abs(vel*500000)+1;
        for(int i=0; i<(rand() % randVel)-1; i++)
        {
            Particle p;
            p.pos.x = x + rand() % scale/3 - scale/6;
            p.pos.y = y + rand() % scale/3 - scale/6;
            p.size = rand() % (scale/40 + 1) * abs(vel);
            p.vel = olc::vf2d(centerX - x, 0 - y).perp().norm()*10 * vel * len * ((double)rand()/RAND_MAX*2.0 + 0.5);
            p.startS = p.size;
            p.lifeTime = (double)rand()/RAND_MAX*100.0 + 1.0;
            p.startLT = p.lifeTime;
            p.transparency = (float)(rand() * abs(vel))/RAND_MAX*0.5 + 0.5;
            p.startT = p.transparency;
            auto colorMod = rand() % 50;
            p.color = olc::Pixel(255, 204+colorMod, 102+colorMod*3);
            particles.push_back(p);
        }
        particleSpawnTime = t;
    }

    void updateAndDrawParticles(float dt)
    {
        for(uint32_t i=0; i<particles.size(); i++)
        {
            auto &p = particles[i];
            if(p.lifeTime <= 0)
            {
                particles.erase(particles.begin()+i);
                i--;
            }
            else
            {
                auto lifePct = p.lifeTime/p.startLT;
                p.pos += p.vel * dt;
                p.size = p.startS * lifePct;
                p.transparency = p.startT * lifePct;
                p.vel -= p.vel * dt * 0.1;
                p.lifeTime -= dt;
            }
            SetPixelBlend(p.transparency);
            FillCircle(p.pos, p.size, p.color);
        }
        SetPixelBlend(1);
    }


};

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    Pendulum demo;
    if (demo.Construct(400, 300, 1, 1, false, true))
        demo.Start();
    return 0;
}
