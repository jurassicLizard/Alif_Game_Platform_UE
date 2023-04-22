// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInput/StdInputMappingContext.h"
#include "EnhancedInput/LookAction.h"


#include "InputCoreTypes.h" 

UStdInputMappingContext::UStdInputMappingContext() 
{
    const ULookAction* const LookAction = GetDefault<ULookAction>(); 
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


}

void UStdInputMappingContext::AddInputActionToContext(UInputAction *InputAction)
{
    //Th is 


}

