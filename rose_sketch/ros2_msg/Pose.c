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
 * @file Pose.c
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#include "Pose.h"

#include <ucdr/microcdr.h>
#include <string.h>

bool Pose_serialize_topic(ucdrBuffer* writer, const Pose* topic)
{
    (void) Point_serialize_topic(writer, &topic->position);
    (void) Quaternion_serialize_topic(writer, &topic->orientation);
    return !writer->error;
}

bool Pose_deserialize_topic(ucdrBuffer* reader, Pose* topic)
{
    (void) Point_deserialize_topic(reader, &topic->position);
    (void) Quaternion_deserialize_topic(reader, &topic->orientation);
    return !reader->error;
}

uint32_t Pose_size_of_topic(const Pose* topic, uint32_t size)
{
    uint32_t previousSize = size;
    size += Point_size_of_topic(&topic->position, size);
    size += Quaternion_size_of_topic(&topic->orientation, size);
    return size - previousSize;
}
