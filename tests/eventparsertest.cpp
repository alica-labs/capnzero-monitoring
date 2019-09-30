#include <gtest/gtest.h>
#include <event/addressevent.h>
#include <event/topicevent.h>
#include <event/receiveevent.h>
#include <event/sendevent.h>
#include <event/subscribeevent.h>
#include <event/yamleventparser.h>
#include <event/createevent.h>
#include <exception/unknowneventexception.h>

TEST(EventParserTest, parsingCreateEvent)
{
  const std::string serializedEvent {
    "type: create\n"
    "protocol: 0"
  };

  YamlEventParser parser;
  const Event* event = parser.parse(serializedEvent);

  dynamic_cast<const CreateEvent*>(event);

  delete event;
}

TEST(EventParserTest, parsingAddressEvent)
{
  const std::string serializedEvent {
    "type: address\n"
    "address: adr\n"
  };

  YamlEventParser parser;
  const Event* event = parser.parse(serializedEvent);

  dynamic_cast<const AddressEvent*>(event);

  delete event;
}

TEST(EventParserTest, parsingTopicEvent)
{
  const std::string serializedEvent {
    "type: topic\n"
    "topic: t"
  };

  YamlEventParser parser;
  const Event* event = parser.parse(serializedEvent);

  dynamic_cast<const TopicEvent*>(event);

  delete event;
}

TEST(EventParserTest, parsingReceiveEvent)
{
  const std::string serializedEvent {
    "type: receive\n"
    "message: msg"
  };

  YamlEventParser parser;
  const Event* event = parser.parse(serializedEvent);

  dynamic_cast<const ReceiveEvent*>(event);

  delete event;
}

TEST(EventParserTest, parsingSendEvent)
{
  const std::string serializedEvent {
    "type: send\n"
    "message: msg\n"
    "topic: group"
  };

  YamlEventParser parser;
  const Event* event = parser.parse(serializedEvent);

  dynamic_cast<const SendEvent*>(event);

  delete event;
}

TEST(EventParserTest, parsingSubscribeEvent)
{
  const std::string serializedEvent {
    "type: subscribe"
  };

  YamlEventParser parser;
  const Event* event = parser.parse(serializedEvent);

  dynamic_cast<const SubscribeEvent*>(event);

  delete event;
}

TEST(EventParserTest, notParsingInvalidEvent)
{
  const std::string serializedEvent {
    "type: invalid"
  };

  YamlEventParser parser;

  EXPECT_THROW(parser.parse(serializedEvent), UnknownEventException);
}
