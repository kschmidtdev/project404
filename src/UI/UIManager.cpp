
#include <UIManager.h>
#include <../Logger.h>

//UILayout testLayout;


 UIManager::UIManager(void)
 {

     // Constructor stuff

     // Add title screen or profile menu
     //Logger::GetInstance()->LogMessage(Logger::INFO, "UIManager Initiated");


 }

    /**
     * Destructor.
	 */
UIManager::~UIManager(void)
{

     // Destructor stuff

     // Add title screen or profile menu
     //Logger::GetInstance()->LogMessage(Logger::INFO, "UIManager Initiated");


 }





// OPERATIONS
    /**
     * Initialize Manager.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
void UIManager::Initialize(void)
{

    // I don't know

    // Add all the layouts to the manager.

}

void UIManager::Shutdown(void)
{

    // Remove all the elements from the stack/list
    // Delete them too? - yes
    /*std::list<UILayout*>::iterator iter;
    //int size = elements.size();

    for (iter = elements.begin();
            iter!=elements.end(); iter++)
    {
        delete (*iter);
    }*/



}

void UIManager::Render(void)
{

    // or RenderSelf()
    //curLayout->RenderSelf();

}

// ACCESS (writing)

void UIManager::pushLayout(UILayout* newLayout)
{

    CurrentLayoutList.push_front(newLayout);
    curLayout = CurrentLayoutList.front();
    curLayout->onLoad();

}

void UIManager::popLayout(void)
{

    CurrentLayoutList.pop_front();
    curLayout->onClose();
    curLayout = CurrentLayoutList.front();

}

void UIManager::addLayout(UILayout* newLayout)
{
    LayoutMasterList.push_back(newLayout);

}

void UIManager::removeLayout(UILayout* removeLayout)
{

        // Do it later....
}


// INQUIRY (reading)
UILayout* UIManager::peekLayout(void)
{
    return curLayout;
}
