#include <gtest/gtest.h>
#include <event/BindEvent.h>
#include <event/ConnectEvent.h>
#include <event/GroupJoinEvent.h>
#include <event/ReceiveEvent.h>
#include <event/SendEvent.h>
#include <event/SubscribeEvent.h>
#include <event/yamleventparser.h>
#include <exception/unknowneventexception.h>

TEST(EventParserTest, parsingBindEvent)
{
  const std::string serializedEvent {
    "type: bind\n"
    "address: adr\n"
    "communication_type: 0"
  };

  Event* event = YamlEventParser::parse(serializedEvent);

  dynamic_cast<BindEvent*>(event);
}

TEST(EventParserTest, parsingConnectEvent)
{
  const std::string serializedEvent {
    "type: connect\n"
    "address: adr\n"
    "communication_type: 0"
  };

  Event* event = YamlEventParser::parse(serializedEvent);

  dynamic_cast<ConnectEvent*>(event);
}

TEST(EventParserTest, parsingGroupJoinEvent)
{
  const std::string serializedEvent {
    "type: join\n"
    "group: group"
  };

  Event* event = YamlEventParser::parse(serializedEvent);

  dynamic_cast<GroupJoinEvent*>(event);
}

TEST(EventParserTest, parsingReceiveEvent)
{
  const std::string serializedEvent {
    "type: receive\n"
    "message: msg"
  };

  Event* event = YamlEventParser::parse(serializedEvent);

  dynamic_cast<ReceiveEvent*>(event);
}

TEST(EventParserTest, parsingSendEvent)
{
  const std::string serializedEvent {
    "type: send\n"
    "message: msg\n"
    "group: group"
  };

  Event* event = YamlEventParser::parse(serializedEvent);

  dynamic_cast<SendEvent*>(event);
}

TEST(EventParserTest, parsingSubscribeEvent)
{
  const std::string serializedEvent {
    "type: subscribe"
  };

  Event* event = YamlEventParser::parse(serializedEvent);

  dynamic_cast<SubscribeEvent*>(event);
}

TEST(EventParserTest, notParsingInvalidEvent)
{
  const std::string serializedEvent {
    "type: invalid"
  };

  EXPECT_THROW(YamlEventParser::parse(serializedEvent), UnknownEventException);
}
