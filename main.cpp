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

  AnimData nebulae[2]{ nebData, nebData2 }; // each element will be intializes each values to 0 (copies the data in to the array element)
  

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
    if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) // if rectangle position is greater or equals to 380 - 80
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
    nebulae[0].pos.x += nebVel * dT;
    
    // update nebula 2 position
    nebulae[1].pos.x += nebVel * dT;

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
    nebulae[0].runningTime += dT;
    if (nebulae[0].runningTime >= nebulae[0].updateTime)
    {
      nebulae[0].runningTime = 0.0;
      nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width; // frame of the nebula * nebula width
      nebulae[0].frame++; // iterate by adding 1
      if (nebulae[0].frame  > 7) // up to 7 elements
      {
        nebulae[0].frame = 0;
      }

    }

    //update nebula 2 animation frame
    nebulae[1].runningTime += dT;
    if (nebulae[1].runningTime >= nebulae[1].updateTime)
    {
      nebulae[1].runningTime = 0.0;
      nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width; // frame of the nebula * nebula width
      nebulae[1].frame++; // iterate by adding 1
      if (nebulae[1].frame  > 7) // up to 7 elements
      {
        nebulae[1].frame = 0;
      }

    }

    // Draw Nebula
    DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
    
    // Draw Nebula 2
    DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

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
