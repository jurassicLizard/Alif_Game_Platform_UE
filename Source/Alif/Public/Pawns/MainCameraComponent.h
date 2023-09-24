// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "MainCameraComponent.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class ALIF_API UMainCameraComponent : public UCameraComponent
{
	GENERATED_BODY()


public:	
	// Begin UCameraComponent interface

	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	// End UCameraComponent interface

	//Constructor
	UMainCameraComponent();

	/**Handle Zoom In*/

	void TriggerZoomIn();

	/**Handle Zoom Out*/
	void TriggerZoomOut();

	/*
	 * Update the mouse controlled camera movement.
	 * 
	 * @param	InPlayerController		The relevant player controller.
	 */
	void UpdateCameraMovement( const APlayerController* InPlayerController );

	/**Handle Camera movements*/
	void Move2D(FVector2D MoveOffset);
	void MoveForward(float val);
	void MoveRight(float val);



	/**Clamp the Camera Location.
	 * 
	 * @param InPlayerController The player controller relative to this component
	 * @param OutCameraLocation  Structure to receive the clamped coordinates 
	*/

	void ClampCameraLocation(const APlayerController* InPlayerController, FVector& OutCameraLocation );

	/**The minimum offset of the camera*/

	UPROPERTY(config)
	float MinCameraOffset;

	/**The maximum offset of the camera*/

	UPROPERTY(config)
	float MaxCameraOffset;

	
	/**Set the desired Camera position*/

	void SetCameraTarget(const FVector& CameraTarget);

	/** Sets the desired zoom level ; clamping if necessary*/
	void SetZoomLevel(float NewLevel);

		/*
	 * Exclude an area from the mouse scroll movement update. (This will be reset at the end of each update).
	 * 
	 * @param	InCoords
	 */
	void AddNoScrollZone( FBox InCoords );

	/*
	 * Check if clicked or swiped position is in no swipe zone
	 * @param	ClickPosition		Position to check
	 * @returns	true if given coordinates are withing a no-scroll zone
	 */
	bool AreCoordsInNoScrollZone(const FVector2D& ClickPosition);
	

protected:

	/**Returns the pawn that owns this component*/
	APawn* GetOwnerPawn();

	/** Return the player controller of the pawn that owns this component*/
	APlayerController* GetPlayerController();

	/** Update the movement bounds of this component*/
	void UpdateCameraBounds( const APlayerController* InPlayerController);




private:
	/** List of zones to exxclude from scrolling during the camera movement update*/
	TArray<FBox> NoScrollZones;
	/** How fast the camera moves around when the mouse is at the edge of the screen. */
	float CameraScrollSpeed = 4000.f;
	/**The standard angle to look down on the map*/
	FRotator StandardCameraLookDownAngle = FRotator(-45.f,45.f,0.f);
	/**The standard camera field of view*/
	float StandardFOV = 30.f;
	/**size of the area at teh edge of the screen that will trigget camera scrolling*/
	const uint32 CameraActiveBorder = 20;



	


	float MouseBorderScrollSpeed = 60.f;


	/** Current amount of camera zoom. */
	float ZoomAlpha = 1.0f;
	const float MaxZoomLevel = 1.0f;
	const float MinZoomLevel = 0.3f;
	/**Base Zoom Increment*/

	float ZoomBaseIncrement = .1f;


	/**Percentage of Minimap where center of camera can be placed*/
	float MiniMapBoundsLimit = 0.8f;

	/** Bounds for camera movement*/
	FBox CameraMovementBounds;

	/**Viewport size associated with camera bounds.*/
	FVector2D CameraMovementViewportSize;

	/** if set. camera position will be clamped to movement bounds.*/
	bool bShouldClampCamera : true;







	
	
	
};
