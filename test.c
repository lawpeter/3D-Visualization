#include <stdio.h>
#include <string.h>
#include <math.h>

void renderFrame();
float calculateX(float t, float s);
float calculateY(float t, float s);
float calculateZ(float t, float s);
float dotProduct(float u[], float v[]);
void crossProduct(float normalVector[], float u[], float v[]);

int main()
{
    printf("\x1b[2J");
    renderFrame();
    return 0;
}

void renderFrame()
{
    int screenWidth = 240;
    int screenHeight = 66;

    float tStep = 0.01;
    float sStep = 0.01;
    float t;
    float s;
    float distanceFromScreen = 5.0;
    float k1 = screenWidth * 5.0 * 2.0 / (2.0 * 10.0);

    int i;
    int j;

    char output[240 * 66];
    float zBuffer[240 * 66];

    float x;
    float y;
    float z;

    float ooz;

    int xp;
    int yp;

    int index;

    float lightVector[] = {1, 0, 1};
    float normalVector[3];

    float L;

    float u[3];
    float v[3];

    memset(output, ' ', sizeof(output));
    memset(zBuffer, 0, sizeof(zBuffer));

    for (t = 0.0; t < 10.0; t += tStep) {
        for (s = 0.0; s < 2 * 3.14159; s += sStep)
        {
            x = calculateX(t, s);
            y = calculateY(t, s) / 2.0;
            z = calculateZ(t, s) + distanceFromScreen;
            ooz = 1 / z;

            xp = (int) (screenWidth / 2 + k1 * ooz * x);
            yp = (int) (screenHeight / 2 - k1 * ooz * y);
            u[0] = calculateX((t - (tStep / 2)), (s - (sStep / 2))) - calculateX(t, s);
            u[1] = calculateY((t - (tStep / 2)), (s - (sStep / 2))) - calculateY(t, s);
            u[2] = calculateZ((t - (tStep / 2)), (s - (sStep / 2))) - calculateZ(t, s);
            v[0] = calculateX(t, s) - calculateX((t + (tStep / 2)), (s + (sStep / 2)));
            v[1] = calculateY(t, s) - calculateY((t + (tStep / 2)), (s + (sStep / 2)));
            v[2] = calculateZ(t, s) - calculateZ((t + (tStep / 2)), (s + (sStep / 2)));

            crossProduct(normalVector, u, v);

            L = dotProduct(normalVector, lightVector) / (sqrt(pow(normalVector[0], 2) + pow(normalVector[1], 2) + pow(normalVector[2], 2)) * sqrt(pow(lightVector[0], 2) + pow(lightVector[1], 2) + pow(lightVector[2], 2)));

            index = xp + yp * screenWidth;

            if (abs(index) < screenHeight * screenWidth - 1 && ooz > zBuffer[index])
            {
                if (L > 0)
                {
                    output[index] = ",:;!-~=*#$@"[(int) (L * 10)];
                }
                else
                {
                    output[index] = '.';
                }
                    zBuffer[index] = ooz;
            }
        }
    }   
    printf("\x1b[H");    
    for (j = 0; j < screenHeight - 1; j++)
    {
        for (i = 0; i < screenWidth; i++) 
        {
            putchar(output[i + screenWidth * j]);
        }
        putchar('\n');
    }
}

float calculateX(float t, float s)
{
    return (t * cos(s));
}

float calculateY(float t, float s) 
{
    return (t * t);
}

float calculateZ(float t, float s) 
{
    return (t * sin(s));
}

float dotProduct(float u[], float v[])
{
    return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);
}

void crossProduct(float normalVector[], float v[], float u[])
{
    normalVector[0] = u[1] * v[2] - u[2] * v[1];
    normalVector[1] = u[2] * v[0] - u[0] * v[2];
    normalVector[2] = u[0] * v[1] - u[1] * v[0];
}
