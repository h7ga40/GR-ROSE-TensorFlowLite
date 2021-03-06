// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! 
 * @file JointTrajectory.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _JointTrajectory_H_
#define _JointTrajectory_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "JointTrajectoryPoint.h"
#include "Header.h"

/*!
 * @brief This struct represents the structure JointTrajectory defined by the user in the IDL file.
 * @ingroup JOINTTRAJECTORY
 */
typedef struct JointTrajectory
{
    Header header;
    uint32_t joint_names_size;
    char joint_names[100][64];

    uint32_t points_size;
    JointTrajectoryPoint points[100];

} JointTrajectory;

struct ucdrBuffer;

bool JointTrajectory_serialize_topic(struct ucdrBuffer* writer, const JointTrajectory* topic);
bool JointTrajectory_deserialize_topic(struct ucdrBuffer* reader, JointTrajectory* topic);
uint32_t JointTrajectory_size_of_topic(const JointTrajectory* topic, uint32_t size);


#ifdef __cplusplus
}
#endif

#endif // _JointTrajectory_H_