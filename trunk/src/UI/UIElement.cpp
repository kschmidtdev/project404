
#include <UIElement.h>

UIElement::UIElement(void)
{
    // Overridden initialization
    rend = SDLRenderer::GetInstance();  // This needs to be overridden to allow for modularization
    RSM = ResourceManager::GetInstance();


/*    pos.SetX(100);

    // This should REALLY be overridden
    elementImage = RSM->LoadTexture("nicePic.bmp");

    // NOw THIIIIIS is extrememly temperary
    rend->AddToRenderQueue(this);*/

}

UIElement::UIElement( const string filename)
: elementImage( ResourceManager::GetInstance()->LoadTexture(filename) )
{
}


UIElement::~UIElement(void)
{
}

void UIElement::RenderSelf(SDL_Surface* destination)
{
    rend->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, destination);
    //rend->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, elementImage);

}

void UIElement::setPos(Point nPos)
{
    pos = nPos;
}

Point UIElement::getPos(void)
{
    return pos;
}

void UIElement::setVisible(bool nVisible)
{
    visible = nVisible;
}


bool UIElement::getVisible(void)
{
    return visible;
}
