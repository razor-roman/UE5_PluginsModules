// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "InteractableObject.h"
#include "LocationMarker.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Interact;
}

void UInteractionObjective::ActivateObjective(AActor* Character)
{
	if (IInteractableObject * InteractableTarget = Cast<IInteractableObject>(Target))
	{
		InteractableTarget->OnInteractionFinished.AddLambda([this, Character](
		AActor* InteractableObject, AActor* ActorInteractedWithObject)
		{
			if (bCanBeCompleted && Character == ActorInteractedWithObject)
			{
			bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}	
	Super::ActivateObjective(Character);
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Location;
}

void ULocationObjective::ActivateObjective(AActor* Character)
{
	if (ILocationMarker * LocMarker = Cast<ILocationMarker>(Marker))
    {
    LocMarker->OnLocationReached.AddLambda([this, Character](
    AActor* LocationMarker, AActor* OverlappedActor)
    {
	    if (bCanBeCompleted && Character == OverlappedActor)
	    {
	    bIsCompleted = true;
		    if (OnObjectiveCompleted.IsBound())
		    {
		    OnObjectiveCompleted.Broadcast(this);
		    }
	    }
    });
    }
	Super::ActivateObjective(Character);
}
