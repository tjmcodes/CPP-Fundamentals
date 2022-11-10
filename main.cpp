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

  float finishLine{ nebulae[sizeOfNebulae - 1].pos.x };

  // nebula X velocity (pixels/second)
  int nebVel{-600};


  // is rectangle in air
  bool isInAir{};
  // jump velocity (pixel/second)
  const int jumpVal{-600};
  // int posY{windowHeight - height};
  int velocity{0};

  Texture2D background = LoadTexture("textures/far-buildings.png");
  float bgX{};

  Texture2D midground = LoadTexture("textures/back-buildings.png");
  float mgX{};

  Texture2D foreground = LoadTexture("textures/foreground.png");
  float fgX{};

  bool collision{};


  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    // Delta Time (time since last frame) --> will be more consistent despite the CPU of computer which may cause problems with FPS changes
    const float dT{GetFrameTime()};
    

    // Start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // scroll background screen
    bgX -= 20 * dT;
    // checks if bgX is less than or equal to (negative) background width*2 - as soon as this is reached it resets to 0.0
    if (bgX <= -background.width*2)
    {
      bgX = 0.0;
    }
    
    // scroll midground screen
    mgX -= 40 * dT;
    // checks if bgX is less than or equal to (negative) background width*2 - as soon as this is reached it resets to 0.0
    if (mgX <= -midground.width*2)
    {
      mgX = 0.0;
    }

    // scroll foregroundground screen
    fgX -= 80 * dT;
    // checks if bgX is less than or equal to (negative) background width*2 - as soon as this is reached it resets to 0.0
    if (fgX <= -foreground.width*2)
    {
      bgX = 0.0;
    }

    // draw the background
    Vector2 bg1Pos{bgX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
    // duplicated the background screen position
    Vector2 bg2Pos{bgX + background.width*2, 0.0};
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

    // draw the midground
    Vector2 mg1Pos{mgX, 0.0};
    DrawTextureEx(midground, mg1Pos, 0.0, 2.0 , WHITE);
    // duplicated the midground screen position
    Vector2 mg2Pos{mgX = midground.width*2, 0.0};
    DrawTextureEx(midground, mg2Pos, 0.0, 2.0 , WHITE);

    // draw the foreground
    Vector2 fg1Pos{fgX, 0.0};
    DrawTextureEx(foreground, fg1Pos, 0.0, 2.0 , WHITE);
    // duplicated the foreground position
    Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
    DrawTextureEx(foreground, fg2Pos, 0.0, 2.0 , WHITE);


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

    // update finishLine
    finishLine += nebVel * dT;

    // update position 
    scarfyData.pos.y += velocity * dT;


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

    
    for (AnimData nebula : nebulae)
    {
      float pad{50}; // to make the rectangle smaller so that it does not include the white area of the frame
      Rectangle nebRec{
        nebula.pos.x + pad,
        nebula.pos.y + pad, 
        nebula.rec.width - 2*pad, 
        nebula.rec.height - 2*pad 
      };
      Rectangle scarfyRec{
        scarfyData.pos.x,
        scarfyData.pos.y,
        scarfyData.rec.width,
        scarfyData.rec.height
      };
      if (CheckCollisionRecs(nebRec, scarfyRec))
      {
        collision = true;
      }
      
    }

    if (collision)
    {
       // lose game
    }
    else
    {
      // Draw Nebulaes using for loop
      for (int i = 0; i < sizeOfNebulae; i++)
      {
        DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
      }
  
      // Draw scarfy
      DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
    }

    // Stop drawing
    EndDrawing();
  }
  // teardown
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);
  CloseWindow();
  
}
