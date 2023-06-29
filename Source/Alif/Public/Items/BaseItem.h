// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class ALIF_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();



private:
	UPROPERTY(VisibleDefaultsOnly,Category="Base Item")
	USceneComponent* BaseItemRootComp;

protected:
	UPROPERTY(VisibleDefaultsOnly,Category="Base Item")
	USkeletalMeshComponent* BaseItemSkelMeshComp;


	
	
};
