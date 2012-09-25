#include "GameDrawing.h"

#include <BW/CImage.h>
#include <BW/CSprite.h>
#include <BW/CThingy.h>
#include <BW/Dialog.h>
#include <BW/Offsets.h>

/*
void BlitToBitmap(DWORD dwOffset, int height, BYTE *pbBuffer, BYTE *pbData)
{
  for ( int i = height; i; --i )
  {
    DWORD _dwDrawW = gdwDrawWdth;
    if ( gdwDrawWdth + dwOffset >= (480-32)*(640+32) )
    {
      if ( dwOffset < (480-32)*(640+32) )
      {
        _dwDrawW = gdwDrawWdth + dwOffset - (480-32)*(640+32);
        DWORD dwFixDrawCopySize = (gdwDrawWdth - _dwDrawW) & 0xFFFFFFFC;
        memcpy(pbBuffer, pbData, dwFixDrawCopySize);
        pbData   += dwFixDrawCopySize;
        pbBuffer += dwFixDrawCopySize;
      }
      pbData   -= (480-32)*(640+32);
      dwOffset -= (480-32)*(640+32);
    }
    DWORD dwDrawCopySize = _dwDrawW & 0xFFFFFFFC;
    memcpy(pbBuffer, pbData, dwDrawCopySize);
    dwOffset += 640 + 32;
    pbData   = &pbData  [dwDrawCopySize + 640 + 32] - gdwDrawWdth;
    pbBuffer = &pbBuffer[dwDrawCopySize + 640] - gdwDrawWdth;
  }
}*/

void updateImageDrawingData()
{
  for ( int y = 0; y < BW::BWDATA::MapSize->y; ++y )
  {
    for ( BW::CSprite *s = BW::BWDATA::spriteGroups[y]; s; s = s->next )
    {
      for ( BW::CImage *i = s->underlay; i; i = i->next )
        i->updateGraphicData();
    }
  }
}

void blitGameText(int line, int x, int y)
{
  if ( BW::BWDATA::Chat_GameText[line].txt[0] )
  {
    char szString[256];
    szString[0] = 0;
    if ( BW::BWDATA::Chat_ColorBytes[line] )
    {
      szString[0] = BW::BWDATA::Chat_ColorBytes[line];
      szString[1] = 0;
    }
    strncat(szString, BW::BWDATA::Chat_GameText[line].txt, sizeof(BW::_gametext));
    BW::BlitText(szString, BW::BWDATA::GameScreenBuffer, x, y, 1);
  }
}

void drawGameText()
{
  int l = *BW::BWDATA::Chat_NextLine;

  int y = 112;
  for ( int i = 11; i > 0; i-- )
  {
    blitGameText(l, 10, y);
    y += *BW::BWDATA::Chat_IncrementY;
    l = (l + 1) % 11;
  }
  blitGameText(12, 10, 295);
  blitGameText(11, 420, 24);
}

void drawThingys()
{
  if ( *BW::BWDATA::wantThingyUpdate )
  {
    BW::CThingy *pThingyFirst = (*BW::BWDATA::ThingyList_UsedFirst);
    for ( BW::CImage *p = pThingyFirst->sprite->underlay; p; p = p->next )
      p->updateGraphicData();

    pThingyFirst->sprite->draw();
    for ( BW::CImage *p = pThingyFirst->sprite->underlay; p; p = p->next )
      p->flags |= 1;
  }
}

void drawMapTiles()
{

}

void GameUpdate(BW::bitmap* /*pSurface*/, BW::bounds* /*pBounds*/)
{
  // if gameLayer.bits & 1 )
  {
    // maskSomething0();
    // memcpy(sgpMaskMapCopy, sgpCurrMaskMap, 408);
    updateImageDrawingData();   //BW::BWFXN_updateImageData();
    // maskSomething2();
    BW::BWFXN_drawMapTiles();
    BW::BWFXN_blitMapTiles();
  }
  // else
  //{
  //  maskSomething1();
  //  refreshImageRange(_top_y, _bot_y);
  //  maskSomething2();
  //  drawMapTiles();
  //  blitMapTiles2();
  //}

  //
  BW::BWFXN_drawAllSprites();// sprites
  // Space tileset stars/parallax thing goes here
  // updateAllFog(gameLayer.bits & 1);
  drawGameText();
  BW::BWFXN_drawDragSelBox();
  
  //BW::BWFXN_drawAllThingys(); // draw thingys
  drawThingys();
}
