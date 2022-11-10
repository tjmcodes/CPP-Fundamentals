#include "raylib.h"

struct AnimData // own member variables in body
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};


int main()
{

  int windowDimensions[2];
  windowDimensions[0] = 512;
  windowDimensions[1] = 380;

  // screen
  InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dash");

  // acceleration due to gravity (pixel/second)/s
  const int gravity{1'000};
  
  // scarfy variables
  // texture 2D, Rectangle and Vector2 (compound data types that comes with Raylib functions)
  Texture2D scarfy = LoadTexture("textures/scarfy.png"); // initialized - pointing to source file
  AnimData scarfyData; // ititialized AnimData members with values:
  scarfyData.rec.width = scarfy.width/6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0/12.0;
  scarfyData.runningTime = 0.0;


  
  
  // nebular variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // AnimData for nebula - initialization of AnimData members
  AnimData nebData;
  nebData.rec.width = nebula.width/8;
  nebData.rec.height = nebula.height/8;
  nebData.rec.x = 0.0;
  nebData.rec.y = 0.0;
  nebData.pos.x = windowDimensions[0]; 
  nebData.pos.y = windowDimensions[1] - nebData.rec.height; // nebRec.height puts the nebula on the ground position
  nebData.frame = 0;
  nebData.updateTime = 1.0/16.0;
  nebData.runningTime = 0.0;


  // AnimData for nebula - initialization of AnimData members
  AnimData nebData2;
  nebData2.rec.width = nebula.width/8;
  nebData2.rec.height = nebula.height/8;
  nebData2.rec.x = 0.0;
  nebData2.rec.y = 0.0;
  nebData2.pos.x = windowDimensions[0] + 300; 
  nebData2.pos.y = windowDimensions[1] - nebData2.rec.height; // nebRec.height puts the nebula on the ground position
  nebData2.frame = 0;
  nebData2.updateTime = 1.0/16.0;
  nebData2.runningTime = 0.0; 
  // nebula X velocity (pixels/second)
  int nebVel{-600};

  // int posY{windowHeight - height};
  int velocity{};

  // is rectangle in air
  bool isInAir{false};
  // jump velocity (pixel/second)
  const int jumpVal{-600};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    // Delta Time (time since last frame) --> will be more consistent despite the CPU of computer which may cause problems with FPS changes
    const float dT{GetFrameTime()};
    

    // Start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // game logic

    // perform ground check
    if (scarfyData.pos.y >= windowDimensions[0] - scarfyData.rec.height) // if rectangle position is greater or equals to 380 - 80
    {
      // rectangle is on the ground
      velocity = 0;
      isInAir = false;
    }
    else 
    {
      // rectangle is in the air
      velocity += gravity * dT;
      isInAir = true;
    }

    // jump check
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVal; // previuously this was hard-coded 'velocity -= 10'
    }
    // update nebula position
    nebData.pos.x += nebVel * dT;
    
    // update nebula 2 position
    nebData2.pos.x += nebVel * dT;

    // update position 
    scarfyData.pos.y += velocity * dT;

    
    // Rectangle shape to test before using sprites
    // DrawRectangle(windowWidth/2, posY, width, height, BLUE);

    // update scarfy animation time
    if (!isInAir)
    {
      // update running time
      scarfyData.runningTime += dT;
      if (scarfyData.runningTime >= scarfyData.updateTime)
      {
        scarfyData.runningTime = 0.0;
        // update animation frame
        scarfyData.rec.x += scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;
        if (scarfyData.frame > 5)
        {
          scarfyData.frame = 0;
        }  
      }
    }

    //update nebula animation frame
    nebData.runningTime += dT;
    if (nebData.runningTime >= nebData.updateTime)
    {
      nebData.runningTime = 0.0;
      nebData.rec.x = nebData.frame * nebData.rec.width; // frame of the nebula * nebula width
      nebData.frame++; // iterate by adding 1
      if (nebData.frame  > 7) // up to 7 elements
      {
        nebData.frame = 0;
      }

    }

    //update nebula 2 animation frame
    nebData2.runningTime += dT;
    if (nebData2.runningTime >= nebData2.updateTime)
    {
      nebData2.runningTime = 0.0;
      nebData2.rec.x = nebData2.frame * nebData2.rec.width; // frame of the nebula * nebula width
      nebData2.frame++; // iterate by adding 1
      if (nebData2.frame  > 7) // up to 7 elements
      {
        nebData2.frame = 0;
      }

    }

    // Draw Nebula
    DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
    
    // Draw Nebula 2
    DrawTextureRec(nebula, nebData2.rec, nebData2.pos, RED);

    // Draw scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);


    // Stop drawing
    EndDrawing();
  }
  // teardown
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
  
}
