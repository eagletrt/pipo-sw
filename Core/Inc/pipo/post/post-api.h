/*!
 * \file post-api.h
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief This module provides the APIs for the POST module
 */

#ifndef POST_API_H
#define POST_API_H

#include "post.h"

/*!
 * \brief Executes the system initialization and power-on self-test (POST).
 *
 * This function initializes all required modules and hardware-dependent
 * services using the provided configuration data. It should be called
 * once during system startup before entering the main application loop.
 *
 * \param[in] data Pointer to the initialization configuration structure.
 *
 * \retval POST_RC_OK on successful initialization.
 * \retval POST_RC_ERROR if one or more initialization steps fail.
 */
enum PostReturnCode post_run(const struct PostInitData *data);

#endif
