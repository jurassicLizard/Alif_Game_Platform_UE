// Fill out your copyright notice in the Description page of Project Settings.


#include "AlifHelpers.h"


FAlifHelpers::FAlifHelpers()
{
}

FAlifHelpers::~FAlifHelpers()
{
}

FVector FAlifHelpers::IntersectRayWithPlane(const FVector &RayOrigin, const FVector &RayDirection, const FPlane &Plane)
{
    //TODO Refresh on how planes (x,y,z,w) work Xx +Yy + Zz = w 
	const FVector PlaneNormal = FVector(Plane.X, Plane.Y, Plane.Z);
	const FVector PlaneOrigin = PlaneNormal * Plane.W;

	const float Distance = FVector::DotProduct((PlaneOrigin - RayOrigin), PlaneNormal) / FVector::DotProduct(RayDirection, PlaneNormal);
	return RayOrigin + RayDirection * Distance;
}
