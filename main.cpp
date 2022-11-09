#include "raylib.h"

int main()
{
  // screen
  const int windowWidth{512};
  const int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dash");

  // acceleration due to gravity (pixel/second)/s
  const int gravity{1'000};
  
  // nebular variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebRec;
  nebRec.width = nebula.width/8;
  nebRec.height = nebula.height/8;
  nebRec.x = 0.0;
  nebRec.y = 0.0;
  Vector2 nebPos{windowWidth, windowHeight - nebRec.height}; // nebRec.height puts the nebula on the ground position
  
  // nebula X velocity (pixels/second)
  int nebVel{-600};


  // scarfy variables
  // texture 2D, Rectangle and Vector2 (compound data types that comes with Raylib functions)
  Texture2D scarfy = LoadTexture("textures/scarfy.png"); // initialized - pointing to source file
  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width/6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  // animation frame
  int frame{};

  // nebula animation variables
  int nebFrame{};
  const float nebUpdateTime{1.0/12.0};
  float nebRunningTime{};

  // time before update animation frame
  const float updateTime{1.0/12.0};
  float runningTime{};
  



  // Rectangle dimensions
  // const int width{50};
  // const int height{80};

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
    if (scarfyPos.y >= windowHeight - scarfy.height) // if rectangle position is greater or equals to 380 - 80
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
    nebPos.x += nebVel * dT;

    // update position 
    scarfyPos.y += velocity * dT;

    
    // Rectangle shape to test before using sprites
    // DrawRectangle(windowWidth/2, posY, width, height, BLUE);

    // update scarfy animation time
    if (!isInAir)
    {
      // update running time
      runningTime += dT;
      if (runningTime >= updateTime)
      {
        runningTime = 0.0;
        // update animation frame
        scarfyRec.x += frame * scarfyRec.width;
        frame++;
        if (frame > 5)
        {
          frame = 0;
        }  
      }
    }

    //update nebula animation frame
    nebRunningTime += dT;
    if (nebRunningTime >= nebUpdateTime)
    {
      nebRunningTime = 0.0;
      nebRec.x = nebFrame * nebRec.width; // frame of the nebula * nebula width
      nebFrame++; // iterate by adding 1
      if (nebFrame  > 7) // up to 7 elements
      {
        nebFrame = 0;
      }

    }

    // Draw Nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);

    // Draw scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);


    // Stop drawing
    EndDrawing();
  }
  // teardown
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
  
}