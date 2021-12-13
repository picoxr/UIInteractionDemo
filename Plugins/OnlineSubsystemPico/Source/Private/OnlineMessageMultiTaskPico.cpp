// Copyright © 2015-2021 Pico Technology Co., Ltd. All Rights Reserved.

#include "OnlineMessageMultiTaskPico.h"

void FOnlineMessageMultiTaskPico::AddNewRequest(uint64 RequestId)
{
	InProgressRequests.Add(RequestId);
	PicoSubsystem.AddRequestDelegate(
        RequestId,
        FPicoMessageOnCompleteDelegate::CreateLambda([this, RequestId](FOnlineMessageHandle Message, bool bIsError)
    {
        InProgressRequests.Remove(RequestId);
        if (bIsError)
        {
            bDidAllRequestsFinishedSuccessfully = false;
        }

        if (InProgressRequests.Num() == 0)
        {
            Delegate.ExecuteIfBound();
        }
    }));
}
