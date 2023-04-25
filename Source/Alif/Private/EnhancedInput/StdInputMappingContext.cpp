// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInput/StdInputMappingContext.h"
#include "EnhancedInput/LookAction.h"
#include "EnhancedInput/ZoomAction.h"
#include "EnhancedInput/SelectAction.h"
#include "EnhancedInput/ReleaseAction.h"





#include "InputCoreTypes.h" 
#include "EnhancedActionKeyMapping.h"

UStdInputMappingContext::UStdInputMappingContext()
{
    LookAction = GetDefault<ULookAction>();
    ZoomAction = GetDefault<UZoomAction>();
    SelectAction = GetDefault<USelectAction>();
    ReleaseAction = GetDefault<UReleaseAction>();

    /**Or maybe use StaticClass() like ULookAction::StaticClass() 
     * 
     * ADDENDUM : NO you cannot use StaticClass() because it returns a UClass which is the type 
     * of object used in conjunction with the editor world usually
    */

    // FKey LookKey(EKeys::NAME_KeyboardCategory);
    if(LookAction)
    {
        MapKey(LookAction,FKey(EKeys::Mouse2D));
    }

    if(ZoomAction)
    {
        MapKey(ZoomAction,FKey(EKeys::MouseWheelAxis));
    }

    if(SelectAction)
    {
        MapKey(SelectAction,FKey(EKeys::LeftMouseButton));
    }

    if(ReleaseAction)
    {
        MapKey(ReleaseAction,FKey(EKeys::RightMouseButton));
    }

}



