// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkController.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkController::DeepLinkController(DeepLinkModel& deepLinkModel,
                                                   ExampleAppMessaging::TMessageBus& messageBus)
            :m_deepLinkModel(deepLinkModel)
            ,m_messageBus(messageBus)
            {
            }
            
            DeepLinkController::~DeepLinkController()
            {
            }
            
            void DeepLinkController::HandleDeepLinkOpen(const AppInterface::UrlData& data)
            {
                IDeepLinkHandler* handler = m_deepLinkModel.Get(std::string(data.host));
                if(handler != NULL)
                {
                    m_messageBus.Publish(DeepLinkOpenedMessage());
                    handler->HandleDeepLink(data);
                }
                else
                {
                    Eegeo_TTY("Attempt to route unknown deeplink URL: %s",data.host);
                }
            }
        }
    }
}
