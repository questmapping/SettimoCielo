// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	// naming conventions: A followed by name means it's an Actor
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// // Using a decorator to view and edit in blueprint
	// UPROPERTY(EditAnywhere)
	// // naming conventions: F followed by name means it's a Struct
	// FVector myVector = FVector(-13700.0, -2440.0, 4056.0);

	// Category creates a new categoy menu for the variable in UE Editor
	UPROPERTY(EditAnywhere, Category="Moving Platform")
	bool logEnable = false;

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FVector platformVelocity = FVector(0, 100, 0);

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	// degrees per second
	FRotator platformRotationVelocity = FRotator(0, 0, 0);

	FVector startLocation;

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	double maxDistance = 600.0;

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	bool moveDontRock = true;

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	bool startMoving = true;

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	bool startRotating = true;

	// Using a decorator to view in blueprint
	UPROPERTY(VisibleAnywhere, Category="Moving Platform")
	double distanceTraveled = 0.0;

	// Declaring some Member Functions that have to be Defined in
	// .cpp file
	void MovePlatform(float DeltaTime);

	void RotatePlatform(float DeltaTime);

	// const function is an Unreal Pure Function, as it
	// shouldn't be able to chage class state
	bool DidPlatformReachEnd() const;

	float GetDistanceMoved() const;

};
