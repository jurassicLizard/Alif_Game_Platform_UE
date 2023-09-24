// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInput/StdInputMappingContext.h"
#include "EnhancedInput/LookAction.h"
#include "EnhancedInput/ZoomAction.h"
#include "EnhancedInput/SelectAction.h"
#include "EnhancedInput/ReleaseAction.h"
#include "EnhancedInput/SwitchWeaponAction.h"





#include "InputCoreTypes.h" 

UStdInputMappingContext::UStdInputMappingContext()
{
    LookAction = GetDefault<ULookAction>();
    ZoomAction = GetDefault<UZoomAction>();
    SelectAction = GetDefault<USelectAction>();
    ReleaseAction = GetDefault<UReleaseAction>();
    SwitchWeaponAction = GetDefault<USwitchWeaponAction>();

    /**Or maybe use StaticClass() like ULookAction::StaticClass() 
     * 
     * ADDENDUM : NO you cannot use StaticClass() because it returns a UClass which is the type 
     * of object used in conjunction with the editor world usually
    */

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

    if(SwitchWeaponAction)
    {
        MapKey(SwitchWeaponAction,FKey(EKeys::SpaceBar));
    }

}



