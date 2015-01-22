// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassController.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            void CompassController::OnViewCycled()
            {
                m_messageBus.Publish(CompassViewCycledMessage());
            }

            void CompassController::OnCompassModeChangedMessage(const CompassModeChangedMessage& message)
            {
                switch (message.GetMode())
                {
                case  GpsMode::GpsDisabled:
                    m_view.ShowGpsDisabledView();
                    break;
                case GpsMode::GpsFollow:
                    m_view.ShowGpsFollowView();
                    break;
                case GpsMode::GpsCompassMode:
                    m_view.ShowGpsCompassModeView();
                    break;
                case GpsMode::GpsMode_Max:
                    Eegeo_ASSERT("Invalid gps mode");
                    break;
                }
            }

            void CompassController::OnCompassHeadingChangedMessage(const CompassHeadingUpdateMessage& message)
            {
                m_view.SetHeadingRadians(message.GetHeadingRadians());
            }

            void CompassController::OnScreenStateChangedCallback(ScreenControl::View::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }

            CompassController::CompassController(  ICompassView& view,
                                                   ICompassViewModel& viewModel,
                                                   ExampleAppMessaging::TMessageBus& messageBus) : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_viewStateCallback(this, &CompassController::OnScreenStateChangedCallback)
                , m_modeChangedHandler(this, &CompassController::OnCompassModeChangedMessage)
                , m_headingChangedHandler(this, &CompassController::OnCompassHeadingChangedMessage)
                , m_viewCycledCallback(this, &CompassController::OnViewCycled)
            {
                m_messageBus.SubscribeUi(m_modeChangedHandler);
                m_messageBus.SubscribeUi(m_headingChangedHandler);
                m_view.InsertCycledCallback(m_viewCycledCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);

                m_view.SetOnScreenStateToIntermediateValue(m_viewModel.OnScreenState());
            }

            CompassController::~CompassController()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveCycledCallback(m_viewCycledCallback);
                m_messageBus.UnsubscribeUi(m_headingChangedHandler);
                m_messageBus.UnsubscribeUi(m_modeChangedHandler);
            }
        }
    }
}
