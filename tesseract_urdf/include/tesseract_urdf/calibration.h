/**
 * @file calibration.h
 * @brief Parse calibration from xml string
 *
 * @author Levi Armstrong
 * @date September 1, 2019
 * @version TODO
 * @bug No known bugs
 *
 * @copyright Copyright (c) 2019, Southwest Research Institute
 *
 * @par License
 * Software License Agreement (Apache License)
 * @par
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * @par
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef TESSERACT_URDF_CALIBRATION_H
#define TESSERACT_URDF_CALIBRATION_H

#include <tesseract_common/macros.h>
TESSERACT_COMMON_IGNORE_WARNINGS_PUSH
#include <console_bridge/console.h>
#include <exception>
#include <tinyxml2.h>
TESSERACT_COMMON_IGNORE_WARNINGS_POP

#include <tesseract_scene_graph/joint.h>

namespace tesseract_urdf
{
inline tesseract_scene_graph::JointCalibration::Ptr parseCalibration(const tinyxml2::XMLElement* xml_element,
                                                                     const int /*version*/)
{
  if (xml_element->Attribute("rising") == nullptr && xml_element->Attribute("falling") == nullptr)
    std::throw_with_nested(std::runtime_error("Calibration: Missing both attribute 'rising' and 'falling', either "
                                              "remove tag add attributes and values!"));

  auto calibration = std::make_shared<tesseract_scene_graph::JointCalibration>();
  if (xml_element->Attribute("rising") == nullptr && xml_element->Attribute("falling") != nullptr)
    CONSOLE_BRIDGE_logDebug("Calibration: Missing attribute 'rising', using default value 0!");

  if (xml_element->Attribute("rising") != nullptr && xml_element->Attribute("falling") == nullptr)
    CONSOLE_BRIDGE_logDebug("Calibration: Missing attribute 'falling', using default value 0!");

  auto xml_status = xml_element->QueryDoubleAttribute("rising", &(calibration->rising));
  if (xml_status != tinyxml2::XML_NO_ATTRIBUTE && xml_status != tinyxml2::XML_SUCCESS)
    std::throw_with_nested(std::runtime_error("Calibration: Error parsing attribute 'rising'!"));

  xml_status = xml_element->QueryDoubleAttribute("falling", &(calibration->falling));
  if (xml_status != tinyxml2::XML_NO_ATTRIBUTE && xml_status != tinyxml2::XML_SUCCESS)
    std::throw_with_nested(std::runtime_error("Calibration: Error parsing attribute 'falling'!"));

  return calibration;
}

}  // namespace tesseract_urdf

#endif  // TESSERACT_URDF_CALIBRATION_H
