/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ALEXA_SMART_SCREEN_SDK_CAPABILITYAGENTS_ALEXAPRESENTATION_INCLUDE_ALEXAPRESENTATION_ALEXAPRESENTATIONOBSERVERINTERFACE_H_
#define ALEXA_SMART_SCREEN_SDK_CAPABILITYAGENTS_ALEXAPRESENTATION_INCLUDE_ALEXAPRESENTATION_ALEXAPRESENTATIONOBSERVERINTERFACE_H_

#include <chrono>
#include <string>

#include <AVSCommon/Utils/Metrics/MetricRecorderInterface.h>

namespace alexaSmartScreenSDK {
namespace smartScreenSDKInterfaces {

/**
 * This @c AlexaPresentationObserverInterface class is used to notify observers when a @c RenderDocument,
 * @c ExecuteCommands directive is received..
 */
class AlexaPresentationObserverInterface {
public:
    /**
     * Destructor
     */
    virtual ~AlexaPresentationObserverInterface() = default;

    /**
     * Used to notify the observer that Alexa.Presentation.APL.RenderDocument has been received. This is
     * typically intended for telemetry, and is invoked at the earliest possible time after receiving the
     * directive (i.e. before any processing or error checking has taken place).
     *
     * @param receiveTime The time at which the directive was received, for more accurate telemetry.
     */
    virtual void onRenderDirectiveReceived(const std::chrono::steady_clock::time_point &receiveTime) {
        // no-op by default
    }

    /**
     * Used to notify the observer when an APL document is ready to be rendered, typically in response
     * to a Alexa.Presentation.APL.RenderDocument directive being received. Once called, the
     * client should render the document based on the APL specification in the payload in structured JSON format.
     *
     * @note The payload may contain customer sensitive information and should be used with utmost care.
     * Failure to do so may result in exposing or mishandling of customer data.
     *
     * @param jsonPayload The payload of the Alexa.Presentation.APL.RenderDocument directive which follows the APL
     * specification.
     * @param token The APL presentation token associated with this payload.
     * @param windowId The target windowId.
     */
    virtual void renderDocument(
        const std::string& jsonPayload,
        const std::string& token,
        const std::string& windowId) = 0;

    /**
     * Used to notify the observer when the client should clear the APL display card.  Once the card is cleared,
     * the client should call clearDocument().
     */
    virtual void clearDocument() = 0;

    /**
     * Used to notify the observer that rendering has been aborted, e.g. because a check failed or an error
     * was encountered.
     */
    virtual void onRenderingAborted() {
        // no-op by default
    }

    /**
     * Used to notify observer when @c Alexa.Presentation.APL.ExecuteCommands directive has been received.
     *
     * @param jsonPayload The payload of the Alexa.Presentation.APL.ExecuteCommands directive in structured JSON format.
     * @param token Directive token used to bind result processing.
     */
    virtual void executeCommands(const std::string& jsonPayload, const std::string& token) = 0;

    /**
     * Used to notify observer when @c Alexa.Presentation.APL directives related to DataSource updates received.
     *
     * @param sourceType DataSource type.
     * @param jsonPayload The payload of the directive in structured JSON format.
     * @param token Directive token used to bind result processing.
     */
    virtual void dataSourceUpdate(
        const std::string& sourceType,
        const std::string& jsonPayload,
        const std::string& token) = 0;

    /**
     * Used to notify the observer when a command execution sequence should be interrupted
     */
    virtual void interruptCommandSequence() = 0;

    /**
     * Used to notify observer that the active @c PresentationSession has changed.
     */
    virtual void onPresentationSessionChanged() = 0;

    /**
     * Called when a metricRecorder is available for use.
     *
     * @param metricRecorder the metric recorder to use for telemetry.
     */
    virtual void onMetricRecorderAvailable(
            std::shared_ptr<alexaClientSDK::avsCommon::utils::metrics::MetricRecorderInterface> metricRecorder) {
        // no-op by default
    }
};

}  // namespace smartScreenSDKInterfaces
}  // namespace alexaSmartScreenSDK

#endif  // ALEXA_SMART_SCREEN_SDK_CAPABILITYAGENTS_ALEXAPRESENTATION_INCLUDE_ALEXAPRESENTATION_ALEXAPRESENTATIONOBSERVERINTERFACE_H_
