// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MainCameraComponent.h"
#include "Pawns/MainSpectatorPawn.h"
#include "Pawns/MainSpectatorPawnMovement.h"
#include "AlifHelpers.h"



UMainCameraComponent::UMainCameraComponent()    
{   
    //we dont this to tick
    PrimaryComponentTick.bCanEverTick = false;
    
}


/**override from super class*/
void UMainCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
    APlayerController* PlayerController = GetPlayerController();

    if(PlayerController)
    {
        DesiredView.FOV = 30.f; //why is this FOV hardcoded ?
        const float CurrentOffset = MinCameraOffset + ZoomAlpha * (MaxCameraOffset - MinCameraOffset);
        FVector Pos2 = PlayerController->GetFocalLocation();
        DesiredView.Location = PlayerController->GetFocalLocation() - StandardCameraLookDownAngle.Vector() * CurrentOffset;
        DesiredView.Rotation = StandardCameraLookDownAngle;


    }
}



/**Zoom section*/

void UMainCameraComponent::SetZoomLevel(float NewLevel)
{
    ZoomAlpha = FMath::Clamp(NewLevel, MinZoomLevel, MaxZoomLevel);

}

void UMainCameraComponent::TriggerZoomIn()
{
    SetZoomLevel(ZoomAlpha - ZoomBaseIncrement);
}

void UMainCameraComponent::TriggerZoomOut()
{
    SetZoomLevel(ZoomAlpha + ZoomBaseIncrement);
}



/**Zoom section End*/

/**Begin Camera Location and Bounds Section*/

void UMainCameraComponent::UpdateCameraBounds(const APlayerController *InPlayerController)
{
    // we get the local human player

    ULocalPlayer* const LocalPlayer = InPlayerController->GetLocalPlayer();

    if(!LocalPlayer || !LocalPlayer->ViewportClient)
    {
        return;
    }

    //Get the current viewport size
    FVector2D CurrentViewportSize;
    LocalPlayer->ViewportClient->GetViewportSize(CurrentViewportSize);

    //calculate frustum edge direction from bottom left cotner

    if(CameraMovementBounds.GetSize() == FVector::ZeroVector || CurrentViewportSize != CameraMovementViewportSize)
    {
        //calc frustom edge direction , from bottom left corner (Left Hand DirectX with y axis pointing to your left and z to your face or upwards :D )
        const FVector FrustumRay2DDir = FVector(1,1,0).GetSafeNormal();
        const FVector FrustumRay2DRight = FVector::CrossProduct(FrustumRay2DDir, FVector::UpVector); // right hand rule rules
        const FQuat RotQuat(FrustumRay2DRight, FMath::DegreesToRadians(90.f - InPlayerController->PlayerCameraManager->GetFOVAngle()*0.5));
        const FVector FrustumRayDir = RotQuat.RotateVector(FrustumRay2DDir); // we rotate the frustumray2d projection onto our desired position

        // collect 3 world bounds points and matching frustum rays (bottom left , top left , bottom right)

        //TODO get game State from gamestate

        const bool TmpGameState = true;
        FBox TmpWorldBounds;

        if(TmpGameState)
        {
            //Our new bounds are the planar intersection of our box extent with our frustum rays
            FBox const& WorldBounds = TmpWorldBounds;

            if(WorldBounds.GetSize() != FVector::ZeroVector)
            {
                const FVector WorldBoundPoints[] = {
                    FVector(WorldBounds.Min.X, WorldBounds.Min.Y, WorldBounds.Max.Z),
                    FVector(WorldBounds.Min.X, WorldBounds.Max.Y, WorldBounds.Max.Z),
                    FVector(WorldBounds.Max.X, WorldBounds.Min.Y, WorldBounds.Max.Z)
                };

                const FVector FrustumRays[] = {
                    FVector( FrustumRayDir.X,  FrustumRayDir.Y, FrustumRayDir.Z),
					FVector( FrustumRayDir.X, -FrustumRayDir.Y, FrustumRayDir.Z),
					FVector(-FrustumRayDir.X,  FrustumRayDir.Y, FrustumRayDir.Z)
                };

                // Get camera plane for intersections
                const FPlane CameraPlane = FPlane(InPlayerController->GetFocalLocation(), FVector::UpVector);

                //Get matching points on camera plane

                const FVector CameraPlanePoints[] = {
                    FAlifHelpers::IntersectRayWithPlane(WorldBoundPoints[0], FrustumRays[0], CameraPlane)* MiniMapBoundsLimit,
                    FAlifHelpers::IntersectRayWithPlane(WorldBoundPoints[1], FrustumRays[1], CameraPlane)* MiniMapBoundsLimit,
                    FAlifHelpers::IntersectRayWithPlane(WorldBoundPoints[2], FrustumRays[2], CameraPlane)* MiniMapBoundsLimit
                };

                //create new bounds

                CameraMovementBounds = FBox(CameraPlanePoints, 3);
                CameraMovementViewportSize = CurrentViewportSize;

                
            }
        }



    }

}

void UMainCameraComponent::ClampCameraLocation(const APlayerController *InPlayerController, FVector &OutCameraLocation)
{
    if (bShouldClampCamera)
    {
        UpdateCameraBounds(InPlayerController);

        //we make sure the outcameralocation is always inside our bounds
        if(CameraMovementBounds.GetSize() != FVector::ZeroVector)
        {
            OutCameraLocation = CameraMovementBounds.GetClosestPointTo(OutCameraLocation);
        }

    }

}

void UMainCameraComponent::UpdateCameraMovement( const APlayerController* InPlayerController )
{
    /**This function makes sure that we always remain within bounds of the border
     * TODO : add deltatime handling to MOveRight MoveLeft
    */
    if(InPlayerController == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Trying to pass a NULL Player controller to %s"),*GetName());
        return;
    }

    ULocalPlayer* const LocalPlayer = InPlayerController->GetLocalPlayer();

    if(LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->Viewport)
    {
        FVector2D MousePosition;
        if(LocalPlayer->ViewportClient->GetMousePosition(MousePosition) == false)
        {
            return;
        }

        FViewport* const Viewport = LocalPlayer->ViewportClient->Viewport;
        const FIntPoint ViewportSize = Viewport->GetSizeXY();
        const uint32 ViewLeft = FMath::TruncToInt(LocalPlayer->Origin.X * ViewportSize.X); 
        /**The Origin of localplayer is the upper left corner of the viewport
         * Size is between 0 and 1 and denotes how much of the splitscreen a local player would take
         * Origin is also between 0 and 1
        */
       const uint32 ViewRight = ViewLeft + FMath::TruncToInt(LocalPlayer->Size.X * ViewportSize.X);
       const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
       const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);
       
       const float MaxAllowedScrollSpeed = CameraScrollSpeed * FMath::Clamp(ZoomAlpha,MinZoomLevel,MaxZoomLevel);

       float SpectatorCameraSpeed = MaxAllowedScrollSpeed; // we might need to overwrite this later hence why we reassign it
       const uint32 MouseX = MousePosition.X;
       const uint32 MouseY = MousePosition.Y;

       bool bNoScrollZone = AreCoordsInNoScrollZone(MousePosition);

       ASpectatorPawn* SpectatorPawn = InPlayerController->GetSpectatorPawn();

       if(SpectatorPawn->GetMovementComponent() != nullptr)
       {
        //get the current maxspeed from the movement component
            const UMainSpectatorPawnMovement* const DefaultSpectatorPawnMovement = GetDefault<UMainSpectatorPawnMovement>(SpectatorPawn->GetMovementComponent()->GetClass());
            if(DefaultSpectatorPawnMovement)
            {
                SpectatorCameraSpeed = DefaultSpectatorPawnMovement->MaxSpeed;

            }
       }

       if (!bNoScrollZone)
       {
            FVector2D CameraOffset = FVector2D::ZeroVector; //X is our Forward Axis and Y is our Right left Axis
            //Border stoppage conditions horizontal
            if (MouseX >= ViewLeft && MouseX <= (ViewLeft + CameraActiveBorder))
            {
                const float delta = 1.0f - float(MouseX - ViewLeft) / CameraActiveBorder;
                SpectatorCameraSpeed = delta * MaxAllowedScrollSpeed;
                CameraOffset.Y = -MouseBorderScrollSpeed * delta; //move right

            }else if (MouseX >= (ViewRight - CameraActiveBorder) && MouseX <= ViewRight)
            {
                const float delta = float(MouseX - (ViewRight - CameraActiveBorder)) / CameraActiveBorder;
                SpectatorCameraSpeed = delta * MaxAllowedScrollSpeed;
                CameraOffset.Y =  MouseBorderScrollSpeed * delta; // move right
            }

            //Border stoppage conditions vertical
            if(MouseY >= ViewTop && MouseY <= (ViewTop + CameraActiveBorder))
            {
                const float delta = 1.0f - float(MouseY - ViewTop) / CameraActiveBorder;
                SpectatorCameraSpeed = delta * MaxAllowedScrollSpeed;
                CameraOffset.X = MouseBorderScrollSpeed * delta; //move forward
            }else if (MouseY >= (ViewBottom - CameraActiveBorder) && MouseY <= ViewBottom)
            {
                const float delta = float(MouseY - (ViewBottom - CameraActiveBorder)) / CameraActiveBorder;
                SpectatorCameraSpeed = MouseBorderScrollSpeed * delta;
                CameraOffset.X = -MouseBorderScrollSpeed * delta; // move forward

            }

            Move2D(CameraOffset);


            if(SpectatorPawn->GetMovementComponent() != nullptr)
            {
                //set the current maxspeed to the movement component
                 UFloatingPawnMovement*  DefaultSpectatorPawnMovement = Cast<UFloatingPawnMovement>(SpectatorPawn->GetMovementComponent());
                if(DefaultSpectatorPawnMovement)
                {
                   DefaultSpectatorPawnMovement->MaxSpeed = SpectatorCameraSpeed;

                }
            }           

       }

    }
    //we dont need this after updating movement
    NoScrollZones.Empty();


}

void UMainCameraComponent::Move2D(FVector2D MoveOffset)
{
    APawn* OwnerPawn = GetOwnerPawn();

    if(OwnerPawn)
    {
        APlayerController* PlayerController = GetPlayerController();

        if(PlayerController && PlayerController->PlayerCameraManager)
        {
            const FRotationMatrix R(PlayerController->PlayerCameraManager->GetCameraRotation());
            const FVector WorldSpaceAccelRight = R.GetScaledAxis( EAxis::Y ) * 100.f;
            const FVector WorldSpaceAccelForward = R.GetScaledAxis( EAxis::X ) * 100.f;


            OwnerPawn->AddMovementInput(WorldSpaceAccelRight, MoveOffset.Y);
            OwnerPawn->AddMovementInput(WorldSpaceAccelForward, MoveOffset.X);

        }
    }

}

void UMainCameraComponent::SetCameraTarget(const FVector &CameraTarget)
{
    ASpectatorPawn* SpectatorPawn = GetPlayerController()->GetSpectatorPawn();
	if( SpectatorPawn != NULL )
	{
		SpectatorPawn->SetActorLocation(CameraTarget, false);
	}	
}

/**End Camera Location and Bounds Section*/

/**
 * Scroll Zone Section Begin
*/
void UMainCameraComponent::AddNoScrollZone(FBox InCoords)
{
    NoScrollZones.AddUnique(InCoords);

}

bool UMainCameraComponent::AreCoordsInNoScrollZone(const FVector2D& ClickPosition)
{

    FVector MouseCoords(ClickPosition,0.0f);
    for(int iZone = 0; iZone < NoScrollZones.Num(); iZone++)
    {
        FBox CurNoGoZone = NoScrollZones[iZone];
        if(CurNoGoZone.IsInsideXY(MouseCoords) == true)
        {
            return true;
        }
    }

    return false;
}


/**
 * Scroll Zone Section End
*/

APlayerController *UMainCameraComponent::GetPlayerController()
{
    APlayerController* PlayerController = nullptr;

    if(GetOwnerPawn())
    {
        PlayerController = Cast<APlayerController>(GetOwnerPawn()->GetController());
    }
    return PlayerController;
}



APawn *UMainCameraComponent::GetOwnerPawn()
{
    return Cast<APawn>(GetOwner());
}


