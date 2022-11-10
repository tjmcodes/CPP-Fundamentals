#include "raylib.h"

struct AnimData // own member variables in body
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
  return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
  data.runningTime += deltaTime;
  if (data.runningTime >= data.updateTime)
  {
    data.runningTime = 0.0;
    //update animation frame
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if (data.frame > maxFrame)
    {
      data.frame = 0;
    }
  }
  return data;
}

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
  const int sizeOfNebulae{6}; // how many in array
  AnimData nebulae[sizeOfNebulae]{}; // each element will be intializes each values to 0 (copies the data in to the array element)
  
  for (int i = 0; i < sizeOfNebulae; i++)
  {
    nebulae[i].rec.x = 0.0;
    nebulae[i].rec.y = 0.0;
    nebulae[i].rec.width = nebula.width/8;
    nebulae[i].rec.height = nebula.height/8;
    nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
    nebulae[i].frame = 0;
    nebulae[i].updateTime = 0.0;
    nebulae[i].runningTime = 0.0;  
    nebulae[i].pos.x = windowDimensions[0] + i * 300; // i times 300, it starts with 0 so therefore doesn't add 300 
  }

  //! manually initialized the these elements variables as they are different (this has been replaced by one line of code: 57)
  // nebulae[1].pos.x = windowDimensions[0] + 300;
  // nebulae[2].pos.x = windowDimensions[0] + 600;
  // nebulae[3].pos.x = windowDimensions[0] + 900;
  // nebulae[4].pos.x = windowDimensions[0] + 1200;
  // nebulae[5].pos.x = windowDimensions[0] + 1500;

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


    // perform ground check
    if (isOnGround(scarfyData, windowDimensions[1])) // if rectangle position is greater or equals to 380 - 80
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

    // update nebula position using for loop
    for (int i = 0; i < sizeOfNebulae; i++)
    {
      // updates the position of EACH nebula
      nebulae[i].pos.x += nebVel * dT;
    }

    // update position 
    scarfyData.pos.y += velocity * dT;

    
    // Rectangle shape to test before using sprites
    // DrawRectangle(windowWidth/2, posY, width, height, BLUE);

    // update scarfy animation time
    if (!isInAir)
    {
      // update running time
      scarfyData = updateAnimData(scarfyData, dT, 5);
    }

    //update nebula animation frame using for loop
    for (int i = 0; i < sizeOfNebulae; i++)
    {
      nebulae[i] = updateAnimData(nebulae[i], dT, 7);
    }

    // Draw Nebulaes using for loop
    for (int i = 0; i < sizeOfNebulae; i++)
    {
      DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
    }

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
