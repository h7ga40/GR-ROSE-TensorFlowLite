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
 * @file Char.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _Char_H_
#define _Char_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/*!
 * @brief This struct represents the structure Char defined by the user in the IDL file.
 * @ingroup CHAR
 */
typedef struct Char
{
    char data;
} Char;

struct ucdrBuffer;

bool Char_serialize_topic(struct ucdrBuffer* writer, const Char* topic);
bool Char_deserialize_topic(struct ucdrBuffer* reader, Char* topic);
uint32_t Char_size_of_topic(const Char* topic, uint32_t size);


#ifdef __cplusplus
}
#endif

#endif // _Char_H_