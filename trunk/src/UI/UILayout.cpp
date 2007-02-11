
#include <UILayout.h>
#include <Renderer/SDLRenderer.h>



UILayout::UILayout(void)
{

        // Code that will be taken out at some point
   // elements.push_back(
}

UILayout::~UILayout(void)
{
}



// OPERATIONS
void UILayout::RenderSelf(SDL_Surface* destination)
{
    // Needs to be overridden
    // Display background Image
}

/**
 * Upon loading (this layout becoming the current on screen), the elements of the layout are added to the render queue.
 *
 */
void UILayout::onLoad(void)
{
    // Iterate through elements in layout
    // and add them to renderer queue

    std::vector<UIElement*>::iterator iter;
    //int size = elements.size();

    for (iter = elements.begin();
            iter!=elements.end(); iter++)
    {
        SDLRenderer::GetInstance()->AddToRenderQueue( (*iter) );
    }

    // Layout must also ensure that all the elements it's using (because some are shared)
    // are in the correct position (or are they shared??)

}

void UILayout::onClose(void)
{
    // Iterate through elements in layout
    // and remove them from renderer

    // Iterate through elements in layout
    // and add them to renderer queue

    std::vector<UIElement*>::iterator iter;
    //int size = elements.size();

    for (iter = elements.begin();
            iter!=elements.end(); iter++)
    {
        SDLRenderer::GetInstance()->RemoveFromRenderQueue( (*iter) );
    }

}


