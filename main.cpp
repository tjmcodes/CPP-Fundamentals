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
  // screen
  const int windowWidth{512};
  const int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dash");

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
  scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
  scarfyData.pos.y = windowHeight - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0/12.0;
  scarfyData.runningTime = 0.0;


  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width/6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
  scarfyPos.y = windowHeight - scarfyRec.height;
  
  // nebular variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // AnimData for nebula - initialization of AnimData members
  AnimData nebData{ 
    {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
    {windowWidth, windowHeight - nebula.height/8}, // Vector2 pos
    0, // int frame
    1.0/12.0, // float updateTime
    0 //float runningTime
  };

  // AnimData for nebula - initialization of AnimData members
  AnimData nebData2{ 
    {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
    {windowWidth + 300, windowHeight - nebula.height/8}, // Vector2 pos
    0, // int frame
    1.0/12.0, // float updateTime
    0 //float runningTime
  };

  Rectangle nebRec;
  nebRec.width = nebula.width/8;
  nebRec.height = nebula.height/8;
  nebRec.x = 0.0;
  nebRec.y = 0.0;
  Vector2 nebPos{windowWidth, windowHeight - nebRec.height}; // nebRec.height puts the nebula on the ground position
  
  Rectangle nebRec2;
  nebRec2.width = nebula.width/8;
  nebRec2.height = nebula.height/8;
  nebRec2.x = 0.0;
  nebRec2.y = 0.0;
  Vector2 nebPos2{windowWidth + 300, windowHeight - nebRec.height}; // nebRec.height puts the nebula on the ground position

  // nebula X velocity (pixels/second)
  int nebVel{-600};


  

  // animation frame
  int frame{};

  // nebula animation variables
  int nebFrame{};
  const float nebUpdateTime{1.0/16.0};
  float nebRunningTime{};

  int neb2Frame{};
  const float neb2UpdateTime{1.0/16.0};
  float neb2RunningTime{};

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
    
    // update nebula 2 position
    nebPos2.x += nebVel * dT;

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

    //update nebula 2 animation frame
    neb2RunningTime += dT;
    if (neb2RunningTime >= neb2UpdateTime)
    {
      neb2RunningTime = 0.0;
      nebRec2.x = neb2Frame * nebRec2.width; // frame of the nebula * nebula width
      neb2Frame++; // iterate by adding 1
      if (neb2Frame  > 7) // up to 7 elements
      {
        neb2Frame = 0;
      }

    }

    // Draw Nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);
    
    // Draw Nebula 2
    DrawTextureRec(nebula, nebRec2, nebPos2, RED);

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