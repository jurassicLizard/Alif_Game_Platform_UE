// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemIdentificationInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class ALIF_API ABaseItem : public AActor, public IItemIdentificationInterface
{
	GENERATED_BODY()

//BEGIN CLASS INTERFACE
public:	
	// Sets default values for this actor's properties
	ABaseItem();


protected:

	virtual bool IsWeapon() override {return false;}
//END CLASS INTERFACE
private:
	UPROPERTY(VisibleDefaultsOnly,Category="Base Item")
	USceneComponent* BaseItemRootComp;

protected:
	UPROPERTY(VisibleDefaultsOnly,Category="Base Item")
	USkeletalMeshComponent* BaseItemSkelMeshComp;
	
	UPROPERTY(VisibleDefaultsOnly,Category="Base Item")
	class UFloatingPickableComponent* FloatingPickableComponent;


protected:
	UFUNCTION()
	USkeletalMeshComponent* GetItemMesh() const {return BaseItemSkelMeshComp;}
	UFUNCTION()
	virtual USceneComponent* GetChildrenAttachmentComp() const {return BaseItemSkelMeshComp;} //Overridable helper function for getting the item we want to attach any further components to

public:
	UFUNCTION()
	bool HasPickableCapability() const {return (FloatingPickableComponent != nullptr);}




friend UFloatingPickableComponent;	//this class needs to access a protected member of this hence we define it as friend (notice the lack of the class keyword when we put this below instead of above)
	
	
};
