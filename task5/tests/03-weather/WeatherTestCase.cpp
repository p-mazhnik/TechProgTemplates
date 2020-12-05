//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::HasSubstr;

TEST(WeatherTestCase, GetTemperature) {
    cpr::Response city1_response1 = cpr::Response();
    city1_response1.status_code = 200;
    city1_response1.text = R"({"list": [{"main": {"temp": 0}}]})";

    cpr::Response city1_response2 = cpr::Response();
    city1_response2.status_code = 404;

    WeatherMock mock;
    EXPECT_CALL(mock, Get("city1"))
            .Times(AtLeast(1))
            .WillOnce(Return(city1_response2))
            .WillRepeatedly(Return(city1_response1));

    EXPECT_ANY_THROW(mock.GetTemperature("city1"));

    auto result1 = mock.GetTemperature("city1");
    EXPECT_FLOAT_EQ(result1, 0);
}

TEST(WeatherTestCase, GetDifferenceString) {
    cpr::Response city1_response1 = cpr::Response();
    city1_response1.status_code = 200;
    city1_response1.text = R"({"list": [{"main": {"temp": 0}}]})";

    cpr::Response city1_response2 = cpr::Response();
    city1_response2.status_code = 200;
    city1_response2.text = R"({"list": [{"main": {"temp": 3}}]})";

    cpr::Response city2_response = cpr::Response();
    city2_response.status_code = 200;
    city2_response.text = R"({"list": [{"main": {"temp": 1}}]})";

    WeatherMock mock;
    EXPECT_CALL(mock, Get("city1"))
            .WillOnce(Return(city1_response1))
            .WillOnce(Return(city1_response2));
    EXPECT_CALL(mock, Get("city2"))
            .WillRepeatedly(Return(city2_response));

    EXPECT_THAT(mock.GetDifferenceString("city1", "city2"), HasSubstr("colder than in city2 by 1 degrees"));
    EXPECT_THAT(mock.GetDifferenceString("city1", "city2"), HasSubstr("warmer than in city2 by 2 degrees"));
}

