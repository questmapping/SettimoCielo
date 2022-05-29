// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// myVector.X = myX;
	// myVector.Y = myY;
	// myVector.Z = myZ;

	// SetActorLocation(myVector);

	startLocation = GetActorLocation();

	// Displays the log for every actor that has this class as parent
	// https://unrealcommunity.wiki/logging-lgpidy6i
	// Log levels
	// https://docs.unrealengine.com/5.0/en-US/API/Runtime/Core/Logging/ELogVerbosity__Type/
	// Strings always needs * before variable name
	if (logEnable) UE_LOG(LogTemp, Display, TEXT("Platform %s has a Velocity vector %s"),*this->GetName(), *platformVelocity.ToString());
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (startMoving) MovePlatform(DeltaTime);
	if (startRotating) RotatePlatform(DeltaTime);

}

// Define the function in the namespace of the class
void AMovingPlatform::MovePlatform(float DeltaTime)
{
// FVector localVector = myVector;
	// localVector.Z += 100;
	// myVector.Y += 1;
	// // SetActorLocation(myVector);
	// SetActorLocation(localVector);

	// Move Platform Forward
		// Get current platform location and distance traveled
	FVector currentLocation = GetActorLocation();
	distanceTraveled = GetDistanceMoved();
		// Set platform location
	SetActorLocation(currentLocation + platformVelocity*DeltaTime);
	// Move Platform Back
		// Reverse direction if gone too far
	if (DidPlatformReachEnd()){
		// how much it moves past max Distance because of physics
		float overShoot = GetDistanceMoved() - maxDistance;
		if (logEnable) UE_LOG(LogTemp, Display, TEXT("Platform %s has overshoot it's max distance of %f by %f units"),*this->GetName(), maxDistance, overShoot);
		// If we want to move the platform from start point to end point
		FVector moveDirection = platformVelocity.GetSafeNormal();
		if(moveDontRock){
			startLocation += moveDirection * maxDistance;
			SetActorLocation(startLocation);
		}// Skip if we want to rock the platform between two end points
		else{
			SetActorLocation(startLocation + (moveDirection * maxDistance));
		}
		platformVelocity *= -1;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	if (logEnable) UE_LOG(LogTemp, Display, TEXT("Platform %s is rotating"),*this->GetName());
	FRotator currentRotation = GetActorRotation();
	currentRotation = currentRotation + platformRotationVelocity * DeltaTime;
	SetActorRotation(currentRotation);
}

bool AMovingPlatform::DidPlatformReachEnd() const
{
	// Can't put non const funcs in a const func. over the mouse
	return GetDistanceMoved() > maxDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	// Check how far we've moved
		// :: is like . but for accessing members that are not instantiated
	return UKismetMathLibrary::Abs(FVector::Dist(startLocation, GetActorLocation()));
}