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
 * @file BatteryState.c
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#include "BatteryState.h"

#include <ucdr/microcdr.h>
#include <string.h>




bool BatteryState_serialize_topic(ucdrBuffer* writer, const BatteryState* topic)
{
    (void) Header_serialize_topic(writer, &topic->header);
    (void) ucdr_serialize_float(writer, topic->voltage);

    (void) ucdr_serialize_float(writer, topic->current);

    (void) ucdr_serialize_float(writer, topic->charge);

    (void) ucdr_serialize_float(writer, topic->capacity);

    (void) ucdr_serialize_float(writer, topic->design_capacity);

    (void) ucdr_serialize_float(writer, topic->percentage);

    (void) ucdr_serialize_uint8_t(writer, topic->power_supply_status);

    (void) ucdr_serialize_uint8_t(writer, topic->power_supply_health);

    (void) ucdr_serialize_uint8_t(writer, topic->power_supply_technology);

    (void) ucdr_serialize_bool(writer, topic->present);

    (void) ucdr_serialize_array_float(writer, topic->cell_voltage, sizeof(topic->cell_voltage) / sizeof(float));

    (void) ucdr_serialize_uint32_t(writer, topic->cell_voltage_size);

    (void) ucdr_serialize_array_uint8_t(writer, topic->location, sizeof(topic->location) / sizeof(uint8_t));

    (void) ucdr_serialize_array_uint8_t(writer, topic->serial_number, sizeof(topic->serial_number) / sizeof(uint8_t));

    return !writer->error;
}

bool BatteryState_deserialize_topic(ucdrBuffer* reader, BatteryState* topic)
{
    (void) Header_deserialize_topic(reader, &topic->header);
    (void) ucdr_deserialize_float(reader, &topic->voltage);

    (void) ucdr_deserialize_float(reader, &topic->current);

    (void) ucdr_deserialize_float(reader, &topic->charge);

    (void) ucdr_deserialize_float(reader, &topic->capacity);

    (void) ucdr_deserialize_float(reader, &topic->design_capacity);

    (void) ucdr_deserialize_float(reader, &topic->percentage);

    (void) ucdr_deserialize_uint8_t(reader, &topic->power_supply_status);

    (void) ucdr_deserialize_uint8_t(reader, &topic->power_supply_health);

    (void) ucdr_deserialize_uint8_t(reader, &topic->power_supply_technology);

    (void) ucdr_deserialize_bool(reader, &topic->present);

    (void) ucdr_deserialize_array_float(reader, topic->cell_voltage, sizeof(topic->cell_voltage) / sizeof(float));

    (void) ucdr_deserialize_uint32_t(reader, &topic->cell_voltage_size);

    (void) ucdr_deserialize_array_uint8_t(reader, topic->location, sizeof(topic->location) / sizeof(uint8_t));

    (void) ucdr_deserialize_array_uint8_t(reader, topic->serial_number, sizeof(topic->serial_number) / sizeof(uint8_t));

    return !reader->error;
}

uint32_t BatteryState_size_of_topic(const BatteryState* topic, uint32_t size)
{
    uint32_t previousSize = size;
    size += Header_size_of_topic(&topic->header, size);
    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 1) + 1;

    size += ucdr_alignment(size, 1) + 1;

    size += ucdr_alignment(size, 1) + 1;

    size += ucdr_alignment(size, 1) + 1;

    size += ucdr_alignment(size, 4) + sizeof(topic->cell_voltage);

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 1) + sizeof(topic->location);

    size += ucdr_alignment(size, 1) + sizeof(topic->serial_number);

    return size - previousSize;
}
