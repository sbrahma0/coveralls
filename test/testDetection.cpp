/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2018, Ashwin Goyal
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * @file testDetection.cpp
 * 
 * @brief It defines rostest and gtest for Detection class.
 *
 * Copyright [2018] Ashwin Goyal
 */

#include <gtest/gtest.h>
#include "KukaKinematics.hpp"
#include "Detection.hpp"

// This is the google test for the first method of the class.
TEST(DetectionTest, testColorThresholder) {
    // Initialize the Detection and KukaKinematics object
    KukaKinematics robot;
    Detection test(robot, false);

    // Initialize node handle
    ros::NodeHandle n;

    // Initialize image subscriber
    image_transport::ImageTransport imgT(n);
    auto imageSubscriber_ = imgT.subscribe("/camera/image_raw", 1,
                                                &Detection::readImg, &test);
    ros::Duration(1).sleep();
    ros::spinOnce();
    ros::Duration(1).sleep();

    // Check if the left disc is red colored
    auto color = test.colorThresholder(robot.LEFT_DISK);
    EXPECT_FALSE(color.compare("red"));

    // Check if the right disc is blue colored
    color = test.colorThresholder(robot.RIGHT_DISK);
    EXPECT_FALSE(color.compare("blue"));

    // Check if the any other disc is read
    color = test.colorThresholder(robot.HOME);
    EXPECT_TRUE(color.empty());
}
