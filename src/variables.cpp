// <variables.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief variables
//
// Compiler: VC14.2
// Library:  OWL7
//

#include "variables.h"

//------------------------------------------------------------
//
// singleton class Variables
//

//static
Variables& Variables::Instance()
{
    static Variables theInstance;
    return theInstance;
}

//------------------------------------------------------------

// end of <variables.cpp>
