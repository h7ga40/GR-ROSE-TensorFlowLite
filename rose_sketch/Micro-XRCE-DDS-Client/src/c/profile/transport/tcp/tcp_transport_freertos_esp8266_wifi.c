// Copyright 2018 eSOL Co.,Ltd.
// Copyright 2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <uxr/client/profile/transport/tcp/tcp_transport_freertos.h>
#include "tcp_transport_internal.h"
#include "WiFiEspServerClientWrapper.h"

#include "Arduino.h"

#include <unistd.h>
#include <string.h>
#include <errno.h>


bool uxr_init_tcp_platform(struct uxrTCPPlatform* platform, const char* ip, uint16_t port)
{
    if(!platform->use_ethernet)
    {
        bool rv = false;

        /* Wifi connect initialization */
        rv = esp_connect_tcp(ip, port);
        return rv;
    }
    else
    {
        bool rv = false;

        /* Socket initialization. */
        platform->fd = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP);
        if (FREERTOS_INVALID_SOCKET != platform->fd)
        {
            /* Remote IP setup. */
            platform->remote_addr.sin_family = FREERTOS_AF_INET;
            platform->remote_addr.sin_port = FreeRTOS_htons(port);
            platform->remote_addr.sin_addr = FreeRTOS_inet_addr(ip);

            /* Poll setup. */
            platform->poll_fd = FreeRTOS_CreateSocketSet();
            if (NULL != platform->poll_fd)
            {
                /* FreeRTOS_FD_SET() is a void function. */
                FreeRTOS_FD_SET(platform->fd, platform->poll_fd, eSELECT_READ);
                rv = true;
            }

            /* Server connection. */
            if (rv)
            {
                BaseType_t connected = FreeRTOS_connect(platform->fd,
                                                        &platform->remote_addr,
                                                        sizeof(platform->remote_addr));
                rv = (0 == connected);
            }
            else
            {
                rv = false;
            }
        }

        return rv;
    }
}

bool uxr_close_tcp_platform(struct uxrTCPPlatform* platform)
{
    if(!platform->use_ethernet)
    {
        esp_stop_tcp();
        return true;
    }
    else
    {
        (void) FreeRTOS_shutdown(platform->fd, FREERTOS_SHUT_RDWR);

        /* FreeRTOS_closesocket() must be called even if FreeRTOS_shutdown() returns error.
         * FreeRTOS_closesocket() always returns 0. */
        (void) FreeRTOS_closesocket(platform->fd);

        return true;
    }
}

size_t uxr_write_tcp_data_platform(struct uxrTCPPlatform* platform,
                                   const uint8_t* buf,
                                   size_t len,
                                   uint8_t* errcode)
{
    if(!platform->use_ethernet)
    {
        size_t rv = 0;

        size_t bytes_sent = esp_write_tcp(buf, len);

        /* esp_write_tcp() returns 0 if an error or timeout occurred. */
        if (0 < bytes_sent)
        {
            rv = bytes_sent;
            *errcode = 0;
        }
        else
        {
            *errcode = 1;
        }

        return rv;
    }
    else
    {
        size_t rv = 0;

        BaseType_t bytes_sent = FreeRTOS_send(platform->fd, (void*)buf, len, 0);

        /* FreeRTOS_send() returns the number of bytes queued for sending.
         * If an error or timeout occurred, FreeRTOS_send() returns a negative value. */
        if (0 <= bytes_sent)
        {
            rv = (size_t)bytes_sent;
            *errcode = 0;
        }
        else
        {
            *errcode = 1;
        }

        return rv;
    }
}

size_t uxr_read_tcp_data_platform(struct uxrTCPPlatform* platform,
                                  uint8_t* buf,
                                  size_t len,
                                  int timeout,
                                  uint8_t* errcode)
{
    if(!platform->use_ethernet)
    {
        size_t rv = 0;

        int bytes_received = esp_read_tcp(buf, len, timeout);

        if (0 <= bytes_received)
        {
            rv = (size_t)bytes_received;
            *errcode = 0;
        }
        else
        {
            *errcode = 1;
        }

        return rv;
    }
    else
    {
        size_t rv = 0;

        BaseType_t poll_rv = FreeRTOS_select(platform->poll_fd, pdMS_TO_TICKS(timeout));
        if (0 < poll_rv)
        {
            BaseType_t bytes_received = FreeRTOS_recv(platform->fd, (void*)buf, len, 0);
            if (0 <= bytes_received)
            {
                rv = (size_t)bytes_received;
                *errcode = 0;
            }
            else
            {
                *errcode = 1;
            }
        }
        else
        {
            *errcode = (0 == poll_rv) ? 0 : 1;
        }

        return rv;
    }
}

void uxr_disconnect_tcp_platform(struct uxrTCPPlatform* platform)
{
    if(!platform->use_ethernet)
    {
        esp_stop_tcp();
    }
    else
    {
        (void) FreeRTOS_shutdown(platform->fd, FREERTOS_SHUT_RDWR);

        /* FreeRTOS_closesocket() must be called even if FreeRTOS_shutdown() returns error.
         * FreeRTOS_closesocket() always returns 0. */
        (void) FreeRTOS_closesocket(platform->fd);
        platform->fd = FREERTOS_INVALID_SOCKET;
        platform->poll_fd = NULL;
    }
}
