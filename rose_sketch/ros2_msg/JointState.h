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
 * @file JointState.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _JointState_H_
#define _JointState_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "Header.h"

/*!
 * @brief This struct represents the structure JointState defined by the user in the IDL file.
 * @ingroup JOINTSTATE
 */
typedef struct JointState
{
    Header header;
    uint32_t name_size;
    char name[10][32];

    uint32_t position_size;
    double position[10];

    uint32_t velocity_size;
    double velocity[10];

    uint32_t effort_size;
    double effort[10];

} JointState;

struct ucdrBuffer;

bool JointState_serialize_topic(struct ucdrBuffer* writer, const JointState* topic);
bool JointState_deserialize_topic(struct ucdrBuffer* reader, JointState* topic);
uint32_t JointState_size_of_topic(const JointState* topic, uint32_t size);


#ifdef __cplusplus
}
#endif

#endif // _JointState_H_